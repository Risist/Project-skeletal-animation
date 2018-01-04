#include "EditorState.h"
#include <Re\Graphics\Gui\GuiSpecial.h>

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


		guiEditorModel = Gui::gui.add<Gui::Menu>();
		guiEditorAnimation = Gui::gui.add<Gui::Menu>()->setActivated(false);

		createEditorAnimation();
		createEditorModel();
	}

	Game::State * StateModel::onUpdate(sf::Time dt)
	{
		//animation.updateReturn();
		cam.display(wnd);
		//animation.update();
		model.draw(cam);

		getActualPart()->drawBoundingBox(cam);

		Gui::gui.onUpdate(wnd, RenderStates::Default);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			return new StateModel;

		return nullptr;
	}

	void StateModel::onExit()
	{
		Gui::gui.clear();
	}


	void StateModel::loadResources()
	{
		res.clear();
		res.deserialise("Resource\\Resources.txt");

	}

	void Editor::StateModel::createEditorAnimation()
	{
		/////
		float distY = 30.f;
		float distX = 105.f;
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


		y = 20.f;
		x = 120.f;

		guiEditorAnimation->add<Gui::Button>("Resource\\GuiTemplates\\Background.txt")->setPosition({ 0, 0 })->setWh({ 3000, 100 });
		
		auto buttonAddKeystone = guiEditorAnimation->add<Gui::NamedButton>("Resource\\GuiTemplates\\Button.txt")->setPosition({ x, y })
			->setName("Add Keystone")
			;x += distX*2;
		auto buttonDelKeystone = guiEditorAnimation->add<Gui::NamedButton>("Resource\\GuiTemplates\\Button.txt")->setPosition({ x, y })
			->setName("Delete Keystone")
			; x += distX*2;

		///////////////
		auto buttonLoadAnimation = guiEditorAnimation->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonHalf.txt")->setPosition({ x, y })
			->setName("load")
			; x += distX;

		auto buttonSaveAnimation = guiEditorAnimation->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonHalf.txt")->setPosition({ x, y })
			->setName("save")
			; x += distX * 2;


		auto buttonModel = guiEditorAnimation->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonHalf.txt")->setPosition({ x, y })
			->setName("Model")
			->setPressEvent([this]() 
		{
			guiEditorModel->setActivated(!guiEditorModel->isActivated());
			guiEditorAnimation->setActivated(!guiEditorAnimation->isActivated());
			
			guiModel->setProgress(guiModelA->getProgres());
			guiModel->runEvent();
		}); x += distX;

		y = 70.f;
		x = 120.f;

		guiModelA = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("model: ")
			->setValueRange(0, model.partsUpdate.size() - 1)
			->setShortKeyPlus(sf::Keyboard::E)
			->setShortKeyMinus(sf::Keyboard::Q)
			; y += distY;

		auto guiKeystone = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("Keystone: ")
			->setValueRange(0, animation.getPart(guiModelA->getProgres()).getKeystoneCount() )
			->setShortKeyPlus(sf::Keyboard::T)
			->setShortKeyMinus(sf::Keyboard::R)
			; y += distY;

		auto guiPosX = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("posX: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::D)
			->setShortKeyMinus(sf::Keyboard::A)
			; y += distY;
		auto guiPosY = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("posY: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::S)
			->setShortKeyMinus(sf::Keyboard::W)
			; y += distY;
		auto guiScaleX = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("scaleX: ")->setInitialValue(1.f)
			->setIncreaseValue(increaseSmall)
			->setShortKeyPlus(sf::Keyboard::L)
			->setShortKeyMinus(sf::Keyboard::J)
			; y += distY;
		auto guiScaleY = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("scaleY: ")->setInitialValue(1.f)
			->setIncreaseValue(increaseSmall)
			->setShortKeyPlus(sf::Keyboard::I)
			->setShortKeyMinus(sf::Keyboard::K)
			; y += distY;
		auto guiRotation = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("Rotation: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::G)
			->setShortKeyMinus(sf::Keyboard::F)
			; y += distY;
		auto guiMineRotation = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("MineRotation: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::B)
			->setShortKeyMinus(sf::Keyboard::V)
			; y += distY;

		guiEditorAnimation->add<Gui::NamedButton>()->setWh({ 110,30 })->setPosition({ x - distY * 2, y })->setGlobalState(Color(100, 100, 100, 150), 0)
			->setName("Play Return")->setTextSize(18);
		guiEditorAnimation->add<Gui::NamedButton>()->setWh({ 110,30 })->setPosition({ x + distY * 2, y })->setGlobalState(Color(100, 100, 100, 150), 0)
			->setName("Play Restart")->setTextSize(18);
		y += distY;
		guiEditorAnimation->add<Gui::CheckBox>("Resource\\GuiTemplates\\CheckBox.txt")->setPosition({ x - distY * 2, y });
		guiEditorAnimation->add<Gui::CheckBox>("Resource\\GuiTemplates\\CheckBox.txt")->setPosition({ x + distY * 2, y });
		y += distY;

		auto guiColorSwitch = guiEditorAnimation->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonBack.txt")->setPosition({ x, y })->setName("Color");
		y += distY;
		auto guiColorRed = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\SetBar.txt")->setActivated(false)->setPosition({ x, y })
			->setBarName("Red: ")->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Num2)
			->setShortKeyMinus(sf::Keyboard::Num1)
			->setValueRange(0, 255)
			->setInitialValue(255)
			; y += distY;

		auto guiColor = guiEditorAnimation->add<Gui::ColorBar>("Resource\\GuiTemplates\\ColorBar.txt")->setPosition({ x, y });

		auto guiColorGreen = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\SetBar.txt")->setActivated(false)->setPosition({ x, y })
			->setBarName("Green: ")->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Num4)
			->setShortKeyMinus(sf::Keyboard::Num3)
			->setValueRange(0, 255)
			->setInitialValue(255)
			; y += distY;
		auto guiColorBlue = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\SetBar.txt")->setActivated(false)->setPosition({ x, y })
			->setBarName("Blue: ")->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Num6)
			->setShortKeyMinus(sf::Keyboard::Num5)
			->setValueRange(0, 255)
			->setInitialValue(255)
			; y += distY;
		auto guiColorAlpha = guiEditorAnimation->add<Gui::SetBar>("Resource\\GuiTemplates\\SetBar.txt")->setActivated(false)->setPosition({ x, y })
			->setBarName("Alpha: ")->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Num8)
			->setShortKeyMinus(sf::Keyboard::Num7)
			->setValueRange(0, 255)
			->setInitialValue(255)
			; y += distY;



	}
	void Editor::StateModel::createEditorModel()
	{
		/////
		float distY = 30.f;
		float distX = 105.f;
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


		y = 20.f;
		x = 120.f;

		guiEditorModel->add<Gui::Button>("Resource\\GuiTemplates\\Background.txt")->setPosition({ 0, 0 })->setWh({ 3000, 100 });

		auto buttonAddUp = guiEditorModel->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonHalf.txt")->setPosition({ x, y })
			->setName("Add Up")
			; x += distX;

		auto buttonAddDown = guiEditorModel->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonHalf.txt")->setPosition({ x, y })
			->setName("Add Down")
			; x += distX;

		auto buttonDel = guiEditorModel->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonHalf.txt")->setPosition({ x, y })
			->setName("Del")
			; x += distX * 2;

		///////////////
		auto buttonLoadModel = guiEditorModel->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonHalf.txt")->setPosition({ x, y })
			->setName("load")
			; x += distX;

		auto buttonSaveModel = guiEditorModel->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonHalf.txt")->setPosition({ x, y })
			->setName("save")
			; x += distX*2;


		auto buttonAnimation = guiEditorModel->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonHalf.txt")->setPosition({ x, y })
			->setName("Animation")
			->setPressEvent([this]() {
				guiEditorModel->setActivated(!guiEditorModel->isActivated());
				guiEditorAnimation->setActivated(!guiEditorAnimation->isActivated());

				guiModelA->setProgress(guiModel->getProgres());
				guiModelA->setValueRange(0, model.partsUpdate.size() - 1);
		}); x += distX;
		////////////////

		y = 70.f;
		x = 120.f;

		guiModel = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("model: ")
			->setValueRange(0, model.partsUpdate.size() - 1)
			->setShortKeyPlus(sf::Keyboard::E)
			->setShortKeyMinus(sf::Keyboard::Q)
			; y += distY;
		guiTexture = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("texture: ")
			->setValueRange(0, tsInst.size() - 1)
			->setShortKeyPlus(sf::Keyboard::T)
			->setShortKeyMinus(sf::Keyboard::R)
			; y += distY;
		auto guiPosX = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("posX: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::D)
			->setShortKeyMinus(sf::Keyboard::A)
			; y += distY;
		auto guiPosY = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("posY: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::S)
			->setShortKeyMinus(sf::Keyboard::W)
			; y += distY;
		auto guiScaleX = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("scaleX: ")->setInitialValue(1.f)
			->setIncreaseValue(increaseSmall)
			->setShortKeyPlus(sf::Keyboard::L)
			->setShortKeyMinus(sf::Keyboard::J)
			; y += distY;
		auto guiScaleY = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("scaleY: ")->setInitialValue(1.f)
			->setIncreaseValue(increaseSmall)
			->setShortKeyPlus(sf::Keyboard::I)
			->setShortKeyMinus(sf::Keyboard::K)
			; y += distY;
		auto guiRotation = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("Rotation: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::G)
			->setShortKeyMinus(sf::Keyboard::F)
			; y += distY;
		auto guiMineRotation = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("MineRotation: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::B)
			->setShortKeyMinus(sf::Keyboard::V)
			; y += distY;
		auto guiOriginX = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("OriginX: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Numpad4)
			->setShortKeyMinus(sf::Keyboard::Numpad6)
			; y += distY;
		auto guiOriginY = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("OriginY: ")
			->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Numpad8)
			->setShortKeyMinus(sf::Keyboard::Numpad5)
			; y += distY;

		auto guiColorSwitch = guiEditorModel->add<Gui::NamedButton>("Resource\\GuiTemplates\\ButtonBack.txt")->setPosition({ x, y })->setName("Color");
		y += distY;
		auto guiColorRed = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\SetBar.txt")->setActivated(false)->setPosition({ x, y })
			->setBarName("Red: ")->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Num2)
			->setShortKeyMinus(sf::Keyboard::Num1)
			->setValueRange(0, 255)
			->setInitialValue(255)
			; y += distY;

		auto guiColor = guiEditorModel->add<Gui::ColorBar>("Resource\\GuiTemplates\\ColorBar.txt")->setPosition({ x, y });

		auto guiColorGreen = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\SetBar.txt")->setActivated(false)->setPosition({ x, y })
			->setBarName("Green: ")->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Num4)
			->setShortKeyMinus(sf::Keyboard::Num3)
			->setValueRange(0, 255)
			->setInitialValue(255)
			; y += distY;
		auto guiColorBlue = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\SetBar.txt")->setActivated(false)->setPosition({ x, y })
			->setBarName("Blue: ")->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Num6)
			->setShortKeyMinus(sf::Keyboard::Num5)
			->setValueRange(0, 255)
			->setInitialValue(255)
			; y += distY;
		auto guiColorAlpha = guiEditorModel->add<Gui::SetBar>("Resource\\GuiTemplates\\SetBar.txt")->setActivated(false)->setPosition({ x, y })
			->setBarName("Alpha: ")->setIncreaseValue(increaseBig)
			->setShortKeyPlus(sf::Keyboard::Num8)
			->setShortKeyMinus(sf::Keyboard::Num7)
			->setValueRange(0, 255)
			->setInitialValue(255)
			; y += distY;


		/// view
		y = 450; x = 870;
		Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("PosX: ")
			->setIncreaseValue(increaseBig)
			->setRepetitionRate(sf::seconds(0.1))
			->setUpdateProgressEvent([&](float& v) { view.setPosition({ v, view.getPosition().y });  })
			; y += distY;
		Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("PosY: ")
			->setIncreaseValue(increaseBig)
			->setRepetitionRate(sf::seconds(0.1))
			->setUpdateProgressEvent([&](float& v) { view.setPosition({ view.getPosition().x, v });  })
			; y += distY;
		Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("scale: ")->setValueRange(0.1f, 10.f)->setInitialValue(1.f)->setProgress(1.f)
			->setIncreaseValue(increaseSmall)->setInitialValue(1.f)
			->setUpdateProgressEvent([&](float& v) { view.setScale({ v, v });  })
			->setRepetitionRate(sf::seconds(0.1))
			; y += distY;
		Gui::gui.add<Gui::SetBar>("Resource\\GuiTemplates\\Setbar.txt")->setPosition({ x, y })
			->setBarName("Rotation: ")
			->setIncreaseValue(increaseBig)
			->setUpdateProgressEvent([&](float& v) { view.setRotation(Degree(v));  })
			->setRepetitionRate(sf::seconds(0.1))
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
			guiOriginX->setProgress(getActualPart()->getOrigin().x);
			guiOriginY->setProgress(getActualPart()->getOrigin().y);

			guiColor->setColorValue(Color(
				getActualPart()->baseDef.color.r,
				getActualPart()->baseDef.color.g,
				getActualPart()->baseDef.color.b,
				getActualPart()->baseDef.color.a
			));

			guiColorRed->setProgress(getActualPart()->baseDef.color.r);
			guiColorGreen->setProgress(getActualPart()->baseDef.color.g);
			guiColorBlue->setProgress(getActualPart()->baseDef.color.b);
			guiColorAlpha->setProgress(getActualPart()->baseDef.color.a);
		};
		guiModel->setUpdateProgressEvent(modelChangeEvent);

		guiTexture->setUpdateProgressEvent([&](float& v) { getActualPart()->setTexture(getActualPartTsId()); });
		guiPosX->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.position.x = v; });
		guiPosY->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.position.y = v; });
		guiScaleX->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.scale.x = v; });
		guiScaleY->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.scale.y = v; });
		guiRotation->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.rotation = Degree(v); });
		guiMineRotation->setUpdateProgressEvent([&](float& v) { getActualPart()->baseDef.mineRotation = Degree(v); });
		guiOriginX->setUpdateProgressEvent([&](float& v)
		{ getActualPart()->setOrigin({ v, getActualPart()->getOrigin().y }); });
		guiOriginY->setUpdateProgressEvent([&](float& v)
		{ getActualPart()->setOrigin({ getActualPart()->getOrigin().x, v }); });
		guiColor->setEvent([&](sf::Color cl) {
			getActualPart()->baseDef.color = Color_f(cl.r, cl.g, cl.b, cl.a);
		});
		guiColorRed->setUpdateProgressEvent([=](float&v) {getActualPart()->baseDef.color = Color_f(
			guiColorRed->getProgres(),
			guiColorGreen->getProgres(),
			guiColorBlue->getProgres(),
			guiColorAlpha->getProgres()
		); });
		guiColorGreen->setUpdateProgressEvent([=](float&v) {getActualPart()->baseDef.color = Color_f(
			guiColorRed->getProgres(),
			guiColorGreen->getProgres(),
			guiColorBlue->getProgres(),
			guiColorAlpha->getProgres()
		); });
		guiColorBlue->setUpdateProgressEvent([=](float&v) {getActualPart()->baseDef.color = Color_f(
			guiColorRed->getProgres(),
			guiColorGreen->getProgres(),
			guiColorBlue->getProgres(),
			guiColorAlpha->getProgres()
		); });
		guiColorAlpha->setUpdateProgressEvent([=](float&v) {getActualPart()->baseDef.color = Color_f(
			guiColorRed->getProgres(),
			guiColorGreen->getProgres(),
			guiColorBlue->getProgres(),
			guiColorAlpha->getProgres()
		); });

		buttonAddDown->setPressEvent([&, modelChangeEvent]()
		{
			auto part = new Graphics::ModelPart(0, Graphics::ModelDef::default);
			getActualPart()->addChildDown(part);
			model.createOrder();
			guiModel->setValueRange(0, model.partsUpdate.size() - 1);
			guiModel->setProgress(findIdOf(part));
			modelChangeEvent(y);
		});
		buttonAddUp->setPressEvent([&, modelChangeEvent]()
		{
			auto part = new Graphics::ModelPart(0, Graphics::ModelDef::default);
			getActualPart()->addChildUp(part);
			model.createOrder();
			guiModel->setValueRange(0, model.partsUpdate.size() - 1);
			guiModel->setProgress(findIdOf(part));
			modelChangeEvent(y);
		});
		buttonDel->setPressEvent([&, modelChangeEvent]()
		{
			Graphics::ModelPart* acP = getActualPart();
			Graphics::ModelPart* parent = (Graphics::ModelPart*)acP->getParent();
			if (parent != &view)
			{
				if (parent->getChildUp() == acP)
					parent->removeBranchChildUp();
				else if (parent->getChildDown() == acP)
					parent->removeBranchChildDown();

				model.createOrder();
				guiModel->setValueRange(0, model.partsUpdate.size() - 1);
				guiModel->setProgress(findIdOf(parent));
				modelChangeEvent(y);
			}
		});

		buttonLoadModel->setPressEvent([&, modelChangeEvent]() {
			model.deserialise("Resource\\model.txt");
			model.createOrder();
			guiModel->setProgress(0);
			guiModel->setValueRange(0, model.partsUpdate.size() - 1);
			modelChangeEvent(y);
		});
		buttonSaveModel->setPressEvent([&]() {
			model.serialise("Resource\\model.txt");
		});

		guiColorSwitch->setPressEvent([=]() {
			guiColor->setActivated(!(guiColor->isActivated()));
			guiColorRed->setActivated(!(guiColorRed->isActivated()));
			guiColorGreen->setActivated(!(guiColorGreen->isActivated()));
			guiColorBlue->setActivated(!(guiColorBlue->isActivated()));
			guiColorAlpha->setActivated(!(guiColorAlpha->isActivated()));

			guiColor->setColorValue(Color(
				getActualPart()->baseDef.color.r,
				getActualPart()->baseDef.color.g,
				getActualPart()->baseDef.color.b,
				getActualPart()->baseDef.color.a
			));

			guiColorRed->setProgress(getActualPart()->baseDef.color.r);
			guiColorGreen->setProgress(getActualPart()->baseDef.color.g);
			guiColorBlue->setProgress(getActualPart()->baseDef.color.b);
			guiColorAlpha->setProgress(getActualPart()->baseDef.color.a);

		});

		modelChangeEvent(y);
	}
}