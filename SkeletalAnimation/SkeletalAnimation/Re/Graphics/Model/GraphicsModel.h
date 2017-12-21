#pragma once
#include <Re\Graphics\ResourceManager.h>
#include <Re\Graphics\Model\GraphicsModelDef.h>

// #define RE_EDITOR

namespace Graphics
{
	
	/*
	Models are divaded into parts. Each individual part is a single Sprite.
	Sprites are displayed according to its parent which has to be set up before drawing process

	Models can be loaded from Res files:
	< ts = 0; posX = 0; posY = 0; scaleX = 0; scaleY = 0; 
		originX = 0; originY = 0; rot = 0; mineRot = 0; 
		clR = 255; clG = 255; clB = 255; clA = 255; >
		
		<another model def><\>
		...
	<\>

	clR, clG, clB, clA - clolor filter in rgba canals
	posX, posY - position relative to parent
	scaleX, scaleY - scale applied to childs and sprite
	originX, originY - origin around which is applied mineRot
	rot - rotation around parent
	mineRot - rotation of sprite only (doesnt affect childs)

	*/
	class ModelPart :
		public Math::Transform,
		public Res::ISerialisable
	{
	public:
		ModelPart();
		ModelPart(ResId tsId, ModelDef def = ModelDef::default, const Vector2D& origin = Vector2D());
		ModelPart(const std::string& path);

		/// displays model part onto given target
		/// make sure the parent is set up otherwise the function will assert
		void draw(sf::RenderTarget& target, sf::RenderStates states = RenderStates::Default);
		/// displays last state of sprite. Modification of baseDef or animationDef are not taken into consideration
		void drawOnly(sf::RenderTarget& target, sf::RenderStates states = RenderStates::Default);
		/// prepares sprite to be drawn with stored animation influence
		void preUpdateOnly();
		/// cleans up animation influence
		void postUpdateOnly();

		/// adds display offset to model
		void applayAnimation(const ModelDef& def);
		/// permanently modifies baseDef
		void applyPose(const ModelDef& def) { baseDef = def; };

		////// setters
		void setOrigin(const Vector2D& s) { sp.setOrigin(s + Vector2D(sp.getTextureRect().width*0.5f, sp.getTextureRect().height*0.5f)); }
		void setTexture(ResId _tsId) { tsId = _tsId; tsInst[tsId].set(sp); }
		/// parent transform
		void setParent(Math::Transform* s, vector<unique_ptr<ModelPart>>* _parts = nullptr) { parent = s; parts = _parts; }


		////// getters
		Vector2D getOrigin() const { return sp.getOrigin(); }
		Color getColor() const { return sp.getColor(); }


		/// default display data of the model (soo called T-pose in case of humanoids)
		ModelDef baseDef;
	private:
		/// storage of all applied animaion offsets
		ModelDef animationDef;
		sf::Sprite sp;
		void updateSpriteFromDef();

		Math::Transform* parent = nullptr;

		using Math::Transform::setPosition;
		using Math::Transform::setRotation;
		using Math::Transform::setScale;

	private:
		/// texture id for serialisation
		ResId tsId = 0;

	protected:
		/// holded ptr to allocated vector
		vector<unique_ptr<ModelPart>> *parts = nullptr;
	public:
		/// add child above
		void addChildUp(ModelPart *s)
		{
			if (childUp == nullptr)
			{
				if (parts)
				{
					parts->push_back(unique_ptr<ModelPart>(s));
					s->parts = parts;
				}
				s->parent = this;
				childUp = s;
			}
			else
				childUp->addSibling(s);
		}
		/// add child under
		void addChildDown(ModelPart *s)
		{
			if (childDown == nullptr)
			{
				if (parts)
				{
					parts->push_back(unique_ptr<ModelPart>(s));
					s->parts = parts;
				}
				s->parent = this;
				childDown = s;
			}
			else
				childDown->addSibling(s);
		}
		////// getters

		ModelPart* getChildUp() const { return childUp; }
		ModelPart* getChildDown() const { return childUp; }
		ModelPart* getSibling() const { return childUp; }


		////// utility

		/// puts ptrs to each child in specific order

		/// me -> child down -> child up -> sibling
		void rewriteTo_Dfs(std::vector<ModelPart*>& v);
		/// me -> sibling -> child down -> child up
		void rewriteTo_Bfs(std::vector<ModelPart*>& v);
		/// child down -> me -> sibling -> child up
		void rewriteTo_Rendering(std::vector<ModelPart*>& v);

	private:
		/// child can be placed either above or under
		/// which child ptr is used determine rendering order
		ModelPart* childUp = nullptr, *childDown = nullptr,
			/// sibling to this model
			/// shows all models on the same layer
			/// Rendering order: first this one then siblings
			*sibling = nullptr;

		/// adds a sibling to the model
		/// for internal purposes
		/// use addUp or addDown instead
		void addSibling(ModelPart *s)
		{
			if (sibling == nullptr)
			{
				if (parts)
				{
					parts->push_back(unique_ptr<ModelPart>(s));
					s->parts = parts;
				}
				sibling = s;
				s->parent = parent;
			}
			else
				sibling->addSibling(s);
		}

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

	class Model : public ModelPart
	{
	public: 
		Model();
		Model(ResId tsId, ModelDef def = ModelDef::default, const Vector2D& origin = Vector2D());
		Model(const std::string& path);

		void draw(sf::RenderTarget& target, sf::RenderStates states = RenderStates::Default);


		
		void allocateChild(ModelPart* s)
		{
			parts.push_back( unique_ptr<ModelPart>(s) );
		}
		void createOrder()
		{
			partsRendering.clear();
			partsUpdate.clear();
			rewriteTo_Rendering(partsRendering);
			rewriteTo_Bfs(partsUpdate);
		}

	
		/// vectors of right order
		vector<ModelPart*> partsRendering;
		vector<ModelPart*> partsUpdate;
	private:
		vector<unique_ptr<ModelPart> > parts;
	};



	
	/*class ModelPart : 
		/// tree structure of Models
		/// childs can be placed above or under this one
		/// Parent is treated as any Transormable so eg. Actor can be used as one
		public BinaryTree<ModelPart, sf::Transformable>,
		/// data about current model part placement in the world
		public sf::Transformable,
		public Res::ISerialisable
	{
	public:
		ModelPart();

		void onUpdate(); 
		void onDraw(sf::RenderTarget& target, sf::RenderStates states);

		void applayAnimation(const ModelDef& def);

		/// permanently edits model statistics
		void applayPose(const ModelDef& def)
		{
			baseDef += def;
		}

		////// setters
		void setOrigin(const Vector2D& s) { sp.setOrigin(s + Vector2D(sp.getTextureRect().width*0.5f, sp.getTextureRect().height*0.5f)); }
		void setTexture(ResId tsId) { tsInst[tsId].set(sp); }

		////// getters
		Vector2D getOrigin() const { return sp.getOrigin(); }
		Color getColor() const { return sp.getColor(); }
		
		Vector2D getPosition() const { return Transformable::getPosition(); }
		Angle getRotation() const { return Degree(Transformable::getRotation()); }

		ModelDef getBaseDef()
		{
			return baseDef;
		}

	private:
		sf::Sprite sp;

		using sf::Transformable::move;
		using sf::Transformable::scale;

	private:
		ModelDef baseDef;
		/// animation influences
		ModelDef animationDef;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};*/
}	