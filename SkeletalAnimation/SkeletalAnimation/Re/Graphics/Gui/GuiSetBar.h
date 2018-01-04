/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#pragma once
#include <Re\Graphics\Gui\GuiMenu.h>
#include <Re\Graphics\Gui\GuiButton.h>
#include <Re\Graphics\Gui\GuiText.h>

/*


---------------------------------
|		|				|		|
|	-	|				|	+	|
|		|				|		|
---------------------------------
*/

namespace Gui
{
	class SetBar : public Base
	{
		SERIALISATION_NAME(SetBar)
	public:
		SetBar();
		
		////// events

		virtual void onUpdate(RenderTarget& wnd, RenderStates states) override;

		/// in which way the bar is oriented
		enum EAxis : int8
		{
			horizontal,
			vertical
		};

		////// setters

		SetBar* setMinimalValue(float32 v)
		{
			minimalValue = v;
			return this;
		}
		SetBar* setMaximalValue(float32 v)
		{
			maximalValue = v;
			return this;
		}
		SetBar* setValueRange(float32 min, float32 max)
		{
			minimalValue = min;
			maximalValue = max;
			return this;
		}
		SetBar* setProgress(float32 s)
		{
			progress = s;
			updateProgress();
			return this;
		}
		SetBar* setRepetitionRate(sf::Time s)
		{
			repetitionTimer.cd = s;
			return this;
		}
		SetBar* setInitialValue(float32 s)
		{
			initialValue = s;
			return this;
		}
		SetBar* setBounds(float32 _minimalValue, float32 _maximalValue)
		{
			minimalValue = _minimalValue;
			maximalValue = _maximalValue;
			return this;
		}
		SetBar* setUpdateProgressEvent(function<void(float32&)> s)
		{
			eventUpdateProgress = s;
			return this;
		}
		SetBar* setIncreaseValue(float32 s)
		{
			increaseValue = [=]() {return s; };
			return this;
		}
		SetBar* setIncreaseValue(function<float32()> s)
		{
			increaseValue = s;
			return this;
		}
		SetBar* setBarName(const string& s)
		{
			name = s;
			updateProgress();
			return this;
		}
		SetBar* setAxis(EAxis s)
		{
			if (axis != s)
			{
				axis = s;

				if (axis == horizontal)
				{
					float buttonLenght = bPlus.getWh().x;
					bPlus.setWh({ bPlus.getWh().y, getWh().y })
						->setPosition({ (getWh().x - buttonLenght)*0.5f,0 });
					bMinus.setWh({ bMinus.getWh().y, getWh().y })
						->setPosition({ -(getWh().x - buttonLenght)*0.5f,0 });

					txt.setRotation(Degree(0));
				}
				else
				{
					float buttonLenght = bPlus.getWh().y;
					bPlus.setWh({  getWh().x, bPlus.getWh().x })
						->setPosition({ 0.f, (getWh().y - buttonLenght)*0.5f });
					bMinus.setWh({ getWh().x, bMinus.getWh().x})
						->setPosition({ 0.f, -(getWh().y - buttonLenght)*0.5f });

					txt.setRotation(Degree(-90));
				}
			}
			return this;
		}
		SetBar* setWh(const Vector2f& wh, float32 buttonLenght)
		{
			Super::setWh(wh);

			if (axis == horizontal)
			{
				bBar.setWh({ wh.x - 2 * buttonLenght, wh.y });
				bPlus.setWh({ buttonLenght, wh.y })
					->setPosition({(wh.x - buttonLenght)*0.5f,0});
				bMinus.setWh({ buttonLenght, wh.y })
					->setPosition({ -(wh.x - buttonLenght)*0.5f,0 });
			}
			else
			{
				bBar.setWh({ wh.x, wh.y - 2 * buttonLenght });
				bPlus.setWh({ wh.x, buttonLenght })
					->setPosition({ 0.f, (wh.y - buttonLenght)*0.5f });
				bMinus.setWh({ wh.x, buttonLenght })
					->setPosition({ 0.f, -(wh.y - buttonLenght)*0.5f });
			}
			return this;
		}
		
		SetBar* setFont(ResId id)
		{
			txt.setFont(id);
			return this;
		}
		SetBar* setTextStyle(sf::Uint32 s)
		{
			txt.setStyle(s);
			return this;
		}
		SetBar* setTextColor(sf::Color cl)
		{
			txt.setColor(cl);
			return this;
		}
		SetBar* setTextSize( size_t size)
		{
			txt.setSize( size);
			return this;
		}

		SetBar* setStateBar(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bBar.setGlobalState(cl, tsId);
			return this;
		}
		SetBar* setStateBarMouse(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bBar.setStateMouse(cl, tsId);
			return this;
		}
		SetBar* setStateBarMouseOn(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bBar.setStateMouseOn(cl, tsId);
			return this;
		}
		SetBar* setStateBarMouseOut(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bBar.setStateMouseOut(cl, tsId);
			return this;
		}
		SetBar* setStateBarPressed(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bBar.setStatePressed(cl, tsId);
			return this;
		}


		SetBar* setStateButton(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bPlus.setGlobalState(cl, tsId);
			bMinus.setGlobalState(cl, tsId);
			return this;
		}
		SetBar* setStateButtonMouse(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bPlus.setStateMouse(cl, tsId);
			bMinus.setStateMouse(cl, tsId);
			return this;
		}
		SetBar* setStateButtonMouseOn(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bPlus.setStateMouseOn(cl, tsId);
			bMinus.setStateMouseOn(cl, tsId);
			return this;
		}
		SetBar* setStateButtonMouseOut(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bPlus.setStateMouseOut(cl, tsId);
			bMinus.setStateMouseOut(cl, tsId);
			return this;
		}
		SetBar* setStateButtonPressed(sf::Color cl = sf::Color::White, ResId tsId = 0)
		{
			bPlus.setStatePressed(cl, tsId);
			bMinus.setStatePressed(cl, tsId);
			return this;
		}

		SetBar* setShortKeyPlus(sf::Keyboard::Key  key)
		{
			bPlus.setShortKey(key);
			return this;
		}
		SetBar* setShortKeyPlus(sf::Mouse::Button  key)
		{
			bPlus.setShortKey(key);
			return this;
		}

		SetBar* setShortKeyMinus(sf::Keyboard::Key  key)
		{
			bMinus.setShortKey(key);
			return this;
		}
		SetBar* setShortKeyMinus(sf::Mouse::Button  key)
		{
			bMinus.setShortKey(key);
			return this;
		}

		SetBar* setShortKeyBar(sf::Keyboard::Key  key)
		{
			bBar.setShortKey(key);
			return this;
		}
		SetBar* setShortKeyBar(sf::Mouse::Button key)
		{
			bBar.setShortKey(key);
			return this;
		}

		REDEFINE_SETTER_1(SetBar, setPosition, const Vector2f&);
		REDEFINE_SETTER_1(SetBar, setActivated, bool);


		////// getters
		
		float32 getProgres() const { return progress; }
		sf::Time getRepetitionRate() const { return repetitionTimer.cd; }
		float32 getInitialValue() const { return initialValue; }
		float32 getMinimalValue() const { return minimalValue; }
		float32 getMaximalValue() const { return maximalValue; }
		float32 getIncreaseValue() const { return increaseValue(); }
		const string& getBarName() const { return name; }
		EAxis getAxis() const { return axis; }

		State getStateBarPressed() const { return bBar.getStatePressed(); }
		State getStateBarMouseOn() const { return bBar.getStateMouseOn(); }
		State getStateBarMouseOut() const { return bBar.getStateMouseOut(); }

		State getStateButtonPressed() const { return bPlus.getStatePressed(); }
		State getStateButtonMouseOn() const { return bPlus.getStateMouseOn(); }
		State getStateButtonMouseOut() const { return bPlus.getStateMouseOut(); }

		const sf::Font* getFont() const { return txt.getText().getFont(); }
		sf::Uint32 getStyle() const { return txt.getText().getStyle();  }
		sf::Color getTextColor() const { return txt.getText().getFillColor();  }
		size_t getTextSize() const { return txt.getText().getCharacterSize();  }



		void runEvent() { eventUpdateProgress(progress); }

	private:
		float32 progress{ 0 };
		/// every what time to accept button press event
		Control::Timer repetitionTimer;

		/// initial progress of setbar. Clicking on the middle part sets bar to the value
		float32 initialValue{ 0 };
		/// clamp value range
		float32 minimalValue{ -std::numeric_limits<float32>::max() };
		float32 maximalValue{ std::numeric_limits<float32>::max() };
	
		/// event called when the progress is changed by buttons
		/// argument is actual progress
		function<void(float32&)> eventUpdateProgress{ [](float32&) {} };
		function<float32()> increaseValue { [](){ return 1.f; } };
		
		/// title of setbar 
		string name;

		/// orientation of setbar
		EAxis axis{horizontal};

		Button bPlus, bMinus, bBar;
		Text txt;

		void updateProgress();

	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}