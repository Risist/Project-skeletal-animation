#include "EditorState.h"

namespace Editor
{
	void StateModel::onStart()
	{
		loadResources();
		/*Gui::gui.add<Gui::NamedButton>("Resource\\GuiTemplates\\Button.txt")
			->setPosition({ 500.f, 500.f } )
			->setName("button")
			;*/


		static Math::Transform t;
		
		model.setParent(&t);
		model.deserialise("Resource\\model.txt");
		model.createOrder();

		animation.attachToModel(model.partsUpdate);
		animation.deserialise("Resource\\animation.txt");

	}

	Game::State * StateModel::onUpdate(sf::Time dt)
	{
		animation.updateReturn();
		cam.display(wnd);
		animation.update();
		model.draw(cam);

		Gui::gui.onUpdate(wnd, RenderStates::Default);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			return new StateModel;

		return nullptr;
	}

	void StateModel::onExit()
	{
	}


	void StateModel::loadResources()
	{
		res.clear();
		res.deserialise("Resource\\Resources.txt");

	}
}