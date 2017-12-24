#include "EditorState.h"

namespace Editor
{
	void StateModel::onStart()
	{
		loadResources();

		////
		model.setParent(&view);
		model.deserialise("Resource\\model.txt");
		model.createOrder();

		animation.attachToModel(model.partsUpdate);
		animation.deserialise("Resource\\animation.txt");

		/////
		float distY = 30.f;
		float y = 100.f;
		float x = 120.f;

		auto increaseOne = []()
		{
			float increase = 1.f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				increase *= 10.f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				increase /= 10.f;
			return increase;
		};
		auto increaseBig = []()
		{
			float increase = 10.f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				increase *= 10.f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				increase /= 10.f;
			return increase;
		};
		auto increaseSmall = []()
		{
			float increase = 0.01f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				increase *= 10.f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				increase /= 10.f;
			return increase;
		};

		guiModel = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("model: ")
			->setValueRange(0, model.partsUpdate.size()-1 )
		; y += distY;
		guiTexture = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("texture: ")
			->setValueRange(0, tsInst.size()-1 )
		; y += distY;
		auto guiPosX = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("posX: ")
			->setIncreaseValue(increaseBig)
		; y += distY;
		auto guiPosY = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("posY: ")
			->setIncreaseValue(increaseBig)
		; y += distY;
		auto guiScaleX = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("scaleX: ")->setInitialValue(1.f)
			->setIncreaseValue(increaseSmall)
		; y += distY;
		auto guiScaleY = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("scaleY: ")->setInitialValue(1.f)
			->setIncreaseValue(increaseSmall)
		; y += distY;
		auto guiRotation = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("Rotation: ")
			->setIncreaseValue(increaseBig)
		; y += distY;
		auto guiMineRotation = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("MineRotation: ")
			->setIncreaseValue(increaseBig)
			; y += distY;
		auto guiOriginX = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("OriginX: ")
			->setIncreaseValue(increaseBig)
		; y += distY;
		auto guiOriginY = Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("OriginY: ")
			->setIncreaseValue(increaseBig)
		; y += distY;

		/// view
		y = 450; x = 870;
		Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("PosX: ")
			->setIncreaseValue(increaseBig)
			->setUpdateProgressEvent([&](float& v) { view.setPosition({ v, view.getPosition().y });  })
		; y += distY;
		Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("PosY: ")
			->setIncreaseValue(increaseBig)
			->setUpdateProgressEvent([&](float& v) { view.setPosition({ view.getPosition().x, v });  })
		; y += distY;
		Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("scale: ")->setValueRange(0.1f, 10.f)->setInitialValue(1.f)->setProgress(1.f)
			->setIncreaseValue(increaseSmall)->setInitialValue(1.f)
			->setUpdateProgressEvent([&](float& v) { view.setScale({ v, v });  })
		; y += distY;
		Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("Rotation: ")
			->setIncreaseValue(increaseBig)
			->setUpdateProgressEvent([&](float& v) { view.setRotation(Degree(v));  })
		; y += distY;


		
		////
		auto modelChangeEvent = [=](float& v) {
			guiTexture->setProgress(mapPartTsId(getActualPart()->getTextureId()));
			guiPosX->setProgress(getActualPart()->baseDef.position.x);
			guiPosY->setProgress(getActualPart()->baseDef.position.y);
			guiScaleX->setProgress(getActualPart()->baseDef.scale.x);
			guiScaleY->setProgress(getActualPart()->baseDef.scale.y);
			guiRotation->setProgress(getActualPart()->baseDef.rotation.asDegree());
			guiMineRotation->setProgress(getActualPart()->baseDef.mineRotation.asDegree());
			guiOriginX->setProgress(getActualPart()->getOrigin().x - getActualPart()->getTextureWh().x);
			guiOriginY->setProgress(getActualPart()->getOrigin().y - getActualPart()->getTextureWh().y);
		}; modelChangeEvent(y);
		guiModel->setUpdateProgressEvent(modelChangeEvent);

		guiTexture		->setUpdateProgressEvent([&](float& v) { getActualPart()->setTexture(getActualPartTsId()); } );
		guiPosX			->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.position.x	= v; });
		guiPosY			->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.position.y	= v; });
		guiScaleX		->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.scale.x		= v; });
		guiScaleY		->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.scale.y		= v; });
		guiRotation		->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.rotation		= Degree(v); });
		guiMineRotation	->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.mineRotation	= Degree(v); });
		guiOriginX		->setUpdateProgressEvent([&](float& v) 
			{ getActualPart()->setOrigin({v - getActualPart()->getTextureWh().x, getActualPart()->getOrigin().y } ); });
		guiOriginY->setUpdateProgressEvent([&](float& v)
			{ getActualPart()->setOrigin({ getActualPart()->getOrigin().y, v - getActualPart()->getTextureWh().x }); });


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