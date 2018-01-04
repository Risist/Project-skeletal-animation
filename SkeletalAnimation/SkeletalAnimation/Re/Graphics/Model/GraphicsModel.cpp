#include <Re\Graphics\Model\GraphicsModel.h>
#include <Re\Graphics\Model\GraphicsAnimationPart.h>

namespace Graphics
{
	ModelPart::ModelPart()
	{
	}

	ModelPart::ModelPart(ResId tsId, ModelDef def, const Vector2D & origin)
	{
		setTexture(tsId);
		setOrigin(origin);
		baseDef = def;
	}

	ModelPart::ModelPart(const std::string & path)
	{
		deserialise(path);
	}

	void ModelPart::draw(sf::RenderTarget & target, sf::RenderStates states)
	{
		assert(parent);
		updateSpriteFromDef();
		target.draw(sp, states);
		animationDef = ModelDef::zero;
	}

	void ModelPart::drawOnly(sf::RenderTarget & target, sf::RenderStates states)
	{
		target.draw(sp, states);
	}

	void ModelPart::preUpdateOnly()
	{
		assert(parent);
		updateSpriteFromDef();
	}

	void ModelPart::postUpdateOnly()
	{
		animationDef = ModelDef::zero;
	}

	void ModelPart::drawBoundingBox(sf::RenderTarget & target, sf::RenderStates states)
	{
		sf::RectangleShape rect;
		rect.setSize({sp.getGlobalBounds().width, sp.getGlobalBounds().height});
		rect.setPosition(sp.getGlobalBounds().left, sp.getGlobalBounds().top);
		rect.setOrigin({0,0});
		rect.setFillColor(Color::Transparent);
		rect.setOutlineThickness(3.f);
		rect.setOutlineColor(Color::Green);
		target.draw(rect, states);
	}

	void ModelPart::applayAnimation(const ModelDef & def)
	{
		animationDef += def;
	}

	void ModelPart::updateSpriteFromDef()
	{
		ModelDef def = baseDef + animationDef;

		Vector2D pos = def.position.getRotated(def.rotation + parent->getRotation());
		setPosition( Vector2D(pos.x * parent->getScale().x, pos.y * parent->getScale().y) + parent->getPosition());
		setRotation(def.rotation + parent->getRotation());
		setScale(def.scale * parent->getScale());

		sp.setPosition(getPosition() );
		sp.setRotation(getRotation().asDegree() + def.mineRotation.asDegree() );
		sp.setScale(def.scale * parent->getScale() );
		sp.setColor(
			Color(
			(sf::Uint8)clamp(def.color.r, 0.f, 255.f),
				(sf::Uint8)clamp(def.color.g, 0.f, 255.f),
				(sf::Uint8)clamp(def.color.b, 0.f, 255.f),
				(sf::Uint8)clamp(def.color.a, 0.f, 255.f)
			)
		);
	}

	void ModelPart::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		std::string myUd = saver.getLine();

		saver.save("ts", tsId, (ResId)0);
		baseDef.serialise(file, saver);
		saver.save("originX", sp.getOrigin().x - sp.getTextureRect().width  * 0.5f, 0.f);
		saver.save("originY", sp.getOrigin().y - sp.getTextureRect().height * 0.5f, 0.f);

		saver.nextLine(file);

		auto it = childUp;
		while(it != nullptr)
		{
			saver.save("ud", "up");
			it->serialise(file, saver);	
			it = it->sibling;
			saver.nextLine(file);
		}
		it = childDown;
		while (it != nullptr)
		{
			//saver.save("ud", "down"); /// default value
			it->serialise(file, saver);
			it = it->sibling; 
			saver.nextLine(file);
		}
		saver.setEndLine();
		
		if (it = sibling)
		{
			saver.nextLine(file);
			saver.save<string>("ud", myUd.data(), "down");
			it->serialise(file, saver);
			it = it->sibling;
		}

	}

	void ModelPart::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		baseDef.deserialise(file, loader);

		/// set texture
		ResId tsId = loader.load("ts", 0);
		if (tsId != 0)
			setTexture(tsId);
		else
			sp.setTextureRect(sf::IntRect());

		setOrigin({
			loader.load<float32>("originX", 0.f),
			loader.load<float32>("originY", 0.f)
		});

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string b = loader.load<string>("ud", "down");
			ModelPart *m = new ModelPart();

			if (b == "up")
				addChildUp(m);
			else // if( b == "down")
				addChildDown(m);

			m->deserialise(file, loader);
		}
	}

	void ModelPart::removeBranchChildUp()
	{
		if (childUp)
		{
			childUp->removeBranchChildDown();
			childUp->removeBranchChildUp();
			childUp->removeBranchSibling();

			if (parts)
				for (auto it = parts->begin(); it != parts->end(); ++it)
					if (it->get() == childUp)
					{
						parts->erase(it);
						break;
					}

			childUp = nullptr;
		}
	}

	void ModelPart::removeBranchChildDown()
	{
		if (childDown)
		{
			childDown->removeBranchChildDown();
			childDown->removeBranchChildUp();
			childDown->removeBranchSibling();

			if (parts)
				for (auto it = parts->begin(); it != parts->end(); ++it)
					if (it->get() == childDown)
					{
						parts->erase(it);
						break;
					}


			childDown = nullptr;
		}
	}

	void ModelPart::removeBranchSibling()
	{
		if (sibling)
		{
			sibling->removeBranchChildDown();
			sibling->removeBranchChildUp();
			sibling->removeBranchSibling();

			if (parts)
				for (auto it = parts->begin()	; it != parts->end(); ++it)
					if (it->get() == sibling)
					{
						parts->erase(it);
						break;
					}

			sibling = nullptr;
		}
	}

	void ModelPart::removehChildUp()
	{
		// TODO
	}

	void ModelPart::removeChildDown()
	{
		// TODO
	}

	void ModelPart::removeSibling()
	{
		// TODO
	}

	void Graphics::ModelPart::prepareToRemove()
	{

	}

	void ModelPart::rewriteTo_Dfs(std::vector<ModelPart*>& v)
	{
		v.push_back(this);

		if (childDown)
			childDown->rewriteTo_Dfs(v);

		if (childUp)
			childUp->rewriteTo_Dfs(v);

		if (sibling)
			sibling->rewriteTo_Dfs(v);
	}

	void ModelPart::rewriteTo_Bfs(std::vector<ModelPart*>& v)
	{
		v.push_back(this);

		if (sibling)
			sibling->rewriteTo_Bfs(v);

		if (childDown)
			childDown->rewriteTo_Bfs(v);

		if (childUp)
			childUp->rewriteTo_Bfs(v);
	}

	void ModelPart::rewriteTo_Rendering(std::vector<ModelPart*>& v)
	{
		if (childDown)
			childDown->rewriteTo_Rendering(v);

		v.push_back(this);

		if (sibling)
			sibling->rewriteTo_Rendering(v);

		if (childUp)
			childUp->rewriteTo_Rendering(v);
	}


	//////////////////////////////////////////////////////////////////////////////////

	Model::Model()
	{
		ModelPart::parts = &parts;
	}

	Model::Model(ResId tsId, ModelDef def, const Vector2D & origin)
		: ModelPart(tsId, def, origin)
	{
		ModelPart::parts = &parts;
	}
	
	Model::Model(const std::string & path)
	{
		ModelPart::parts = &parts;
		deserialise(path);
	}

	void Model::draw(sf::RenderTarget & target, sf::RenderStates states)
	{
		for (auto it : partsUpdate)
			it->preUpdateOnly();
		
		for (auto it : partsRendering)
			it->drawOnly(target, states);
		
		for (auto it : partsUpdate)
			it->postUpdateOnly();

	}

	/*ModelPart::ModelPart()
		: baseDef(ModelDef::default), animationDef(ModelDef::zero)
	{
		setThis((sf::Transformable*)this);
	}

	void ModelPart::applayAnimation(const ModelDef& def)
	{
		animationDef += def;
	}

	void ModelPart::onUpdate()
	{
		assert(getParent());
		
		ModelDef actualDef = baseDef + animationDef;

		setScale(actualDef.scale * getParent()->getScale());
		
		setPosition(
			actualDef.position.getRotated(Degree(getParent()->getRotation()) + actualDef.rotation)
			+ getParent()->getPosition()
		);
		
		setRotation(getParent()->getRotation() + actualDef.rotation.asDegree());

		/// reset animation Count
		animationDef = actualDef;
	}
	
	void ModelPart::onDraw(RenderTarget & target, RenderStates states)
	{
		/// update from Transformable state
		sp.setPosition(getPosition());
		sp.setRotation(getRotation().asDegree() + animationDef.mineRotation.asDegree());
		sp.setScale(getScale());
		sp.setColor(
			Color(
				(sf::Uint8)clamp(animationDef.color.r , 0.f, 255.f),
				(sf::Uint8)clamp(animationDef.color.g , 0.f, 255.f),
				(sf::Uint8)clamp(animationDef.color.b , 0.f, 255.f),
				(sf::Uint8)clamp(animationDef.color.a , 0.f, 255.f)
			)
		);

		/// draw
		target.draw(sp, states);

		/// reset state
		animationDef = ModelDef::zero;
	}

	void ModelPart::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{

		baseDef.serialise(file, saver);
		saver.nextLine(file);

		do
		{

		}
		DATA_SCRIPT_MULTILINE_SAVE(file, saver, )
	}

	void ModelPart::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		baseDef.deserialise(file, loader);

		/// set texture
		ResId tsId = loader.load("ts", 0);
		if (tsId != 0)
			setTexture(tsId);
		else
			sp.setTextureRect(sf::IntRect() );

		setOrigin({
			loader.load<float32>("originX", 0.f),
			loader.load<float32>("originY", 0.f)
		});

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string b = loader.load<string>("ud", "down");
			ModelPart *m = new ModelPart();

			if (b == "up")
				addUp(m);
			else // if( b == "down")
				addDown(m);

			m->deserialise(file, loader);
		}

		animationDef = baseDef;
	}*/
}