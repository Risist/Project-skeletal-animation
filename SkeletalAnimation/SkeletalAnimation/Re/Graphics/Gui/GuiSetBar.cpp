/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include <Re\Graphics\Gui\GuiSetBar.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	SetBar::SetBar()
	{
		setRepetitionRate(sf::seconds(0.15f));

		bPlus.setPressMode(Control::Key::EPressState::hold);
		bMinus.setPressMode(Control::Key::EPressState::hold);
		bBar.setPressMode(Control::Key::EPressState::hold);

		bPlus.setPressEvent( [this]() { 
				if (repetitionTimer.isReadyRestart() == false) return; 
				progress += increaseValue();
				eventUpdateProgress(progress); 
				updateProgress();
		});
		bMinus.setPressEvent( [this]() { 
			if (repetitionTimer.isReadyRestart() == false) return;
			progress -= increaseValue(); eventUpdateProgress(progress);
			updateProgress();
		});
		bBar.setPressEvent( [this]() { 
			if (repetitionTimer.isReadyRestart() == false) return;
			progress = initialValue; eventUpdateProgress(progress); 
			updateProgress();
		});

		updateProgress();
	}

	void SetBar::onUpdate(RenderTarget & wnd, RenderStates states)
	{
		bBar.updateActualPosition(getActualPosition());
		bBar.onUpdate(wnd, states);
				
		bPlus.updateActualPosition(getActualPosition());
		bPlus.onUpdate(wnd, states);
		
		bMinus.updateActualPosition(getActualPosition());
		bMinus.onUpdate(wnd, states);

		txt.updateActualPosition(getActualPosition());
		txt.onUpdate(wnd, states);
	}

	void SetBar::updateProgress()
	{
		progress = clamp(progress, minimalValue, maximalValue);
		txt.clear() << name << progress;
	}

	void SetBar::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Base::serialiseF(file, saver);

		/// TODO
	}

	void SetBar::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);

		State stateBarOn; stateBarOn.deserialise_Index("barOn", file, loader); 
		State stateBarOut; stateBarOut.deserialise_Index("barOut", file, loader);
		State stateBarPress; stateBarPress.deserialise_Index("barPress", file, loader);
	
		bBar.setStateMouseOn(stateBarOn.cl, stateBarOn.tsId);
		bBar.setStateMouseOut(stateBarOut.cl, stateBarOut.tsId);
		bBar.setStatePressed(stateBarPress.cl, stateBarPress.tsId);
		

		State stateButtonOn; stateButtonOn.deserialise_Index("buttonOn", file, loader);
		State stateButtonOut; stateButtonOut.deserialise_Index("buttonOut", file, loader);
		State stateButtonPress; stateButtonPress.deserialise_Index("buttonPress", file, loader);

		setStateButtonMouseOn(stateButtonOn.cl, stateButtonOn.tsId);
		setStateButtonMouseOut(stateButtonOut.cl, stateButtonOut.tsId);
		setStateButtonPressed(stateButtonPress.cl, stateButtonPress.tsId);



		setAxis( loader.load<string>("axis", "horizontal") == "horizontal" ? horizontal : vertical);
		setWh(getWh(), loader.load("buttonLenght", 40.f));
		
		setProgress(loader.load("progress", 0.f));
		setInitialValue(loader.load("initialValue", getProgres()));
		setRepetitionRate(sf::seconds(loader.load("repetitionRate", 0.15f)));
		setIncreaseValue(loader.load("increaseValue", 1.f));
		setBarName(loader.load<string>("barName",""));
		setFont(loader.load("fontId", 1));
		setTextColor(
			Color(
				loader.load("textClR", 255u),
				loader.load("textClG", 255u),
				loader.load("textClB", 255u),
				loader.load("textClA", 255u)
			)
		);
		setTextSize(loader.load("textSize", 25u));

	}

}