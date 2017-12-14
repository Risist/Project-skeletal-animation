#pragma once
#include <Re\Graphics\ResourceManager.h>
#include <Re\Graphics\Model\GraphicsModelDef.h>

// #define RE_EDITOR

namespace Graphics
{
	
	/*
	Models are divaded into parts. Each individual part is a single image/Sprite/another being

	Model is responsible of provide correct ModelDef to every image, then they can interpret the data on its own.
	Transformable part of ModelPart holds data after transformation (static/animation)
	*/
	class ModelPart : 
		/// tree structure of Models
		/// childs can be placed above or under this one
		/// Parent is treated as any Transormable so eg. Actor can be used as one
		public BinaryTree<ModelPart, sf::Transformable>,
		/// data about current model part placement in the world
		public sf::Transformable,
		/// the class is serialisable
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
	};
}	