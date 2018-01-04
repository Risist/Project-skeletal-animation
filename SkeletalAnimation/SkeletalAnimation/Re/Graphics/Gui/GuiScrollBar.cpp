/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include <Re\Graphics\Gui\GuiScrollBar.h>
#include <Re\Graphics\ResourceManager.h>

extern RenderWindow wnd;

namespace Gui
{
	ScrollBar::ScrollBar()
		:bPressed(false)
	{
		setProgress(0);
		bScroll.setPressMode(Control::Key::EPressState::hold);
		
		/// change position of scroll button
		bScroll.setPressEvent([this]() 
		{
			if(!bPressedAny || !*bPressedAny)
				bPressed = true;
		});
	}

	void ScrollBar::onUpdate(sf::RenderTarget & target, sf::RenderStates states)
	{
		{
			RectangleShape background;
			background.setPosition(getActualPosition());
			
			background.setFillColor(stateBackground.cl);
			stateBackground.ts.set(background);
			
			background.setSize(getWh());
			background.setOrigin(halfWh);

			target.draw(background);
		}

		if (bPressed && (!bPressedAny || *bPressedAny == false))
		{
			updateProgress();
			updateButton();

			if (sf::Mouse::isButtonPressed(bScroll.getMouseKey()) == false)
				bPressed = false;
			else if(bPressedAny)
				(*bPressedAny) = true;
		}

		bScroll.updateActualPosition(getActualPosition());
		bScroll.onUpdate(target, states);
	}
	void ScrollBar::updateProgress()
	{
		eventUpdateProgress(progress);
		Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(wnd);
		
		if (axis == horizontal)
		{
			float32 minimalPosition = getActualPosition().x - halfWh.x;
			progress = (mousePosition.x - minimalPosition) / (2 * halfWh.x);
		}
		else
		{
			float32 minimalPosition = getActualPosition().y - halfWh.y;
			progress = (mousePosition.y - minimalPosition) / (2 * halfWh.y);
		}

		progress = clamp(progress, 0.f, 1.f);
	}
	void ScrollBar::updateButton()
	{
		if (axis == horizontal)
		{
			bScroll.setPosition({ -halfWh.x + bScroll.getWh().x *0.5F
				+ (getWh().x - bScroll.getWh().x) * progress
				, 0
			});
		}
		else
		{

			bScroll.setPosition({ 0,
				-halfWh.y + bScroll.getWh().y *0.5F
				+ (getWh().y - bScroll.getWh().y) * progress
			});
		}
	}
	void ScrollBar::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		/*
		TODO
		*/
	}
	void ScrollBar::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		string dir = loader.load<string>("axis", "horizontal");
		if (dir == "horizontal" || dir == "x")
			axis = EAxis::horizontal;
		else if (dir == "vertical" || dir == "y")
			axis = EAxis::vertical;
		else
			cerr << "wrong axis of ScrollBar: \"" << dir <<"\"\n";
		Base::deserialiseF(file, loader);
		
		progress = loader.load("progress", 1.f);
		
		stateBackground.deserialise_Index("background", file, loader);

		///On
		State stateOn;
		stateOn.deserialise_Index("buttonOn", file, loader);
		
		///Out
		State stateOut;
		stateOut.deserialise_Index("buttonOut", file, loader);

		///On
		State statePress;
		statePress.deserialise_Index("buttonPress", file, loader);

		setWh(getWh(), loader.load("buttonLEnght", 20.f));
		bScroll.setStateMouseOn(stateOn.cl, stateOn.tsId);
		bScroll.setStateMouseOut(stateOut.cl, stateOut.tsId);
		bScroll.setStatePressed(statePress.cl, statePress.tsId);

		updateButton();
	}
}