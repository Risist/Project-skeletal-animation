/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#pragma once
#include <Re\Graphics\Gui\GuiButton.h>

namespace Gui
{

	class ScrollBar : public Base
	{
		SERIALISATION_NAME(ScrollBar)
	public:
		ScrollBar();

		////// events

		virtual void onUpdate(sf::RenderTarget& target, sf::RenderStates states) override;


		/// in which axis the scroll can be moved
		enum EAxis : int8
		{
			horizontal,
			vertical
		};


		////// setters
		
		ScrollBar* setProgress(float32 s)
		{
			progress = s;
			updateButton();
			return this;
		}
		ScrollBar* setEventUpdateProgress(function<void(float32&)> s)
		{
			eventUpdateProgress = s;
			return this;
		}

		ScrollBar* setStateBackground(sf::Color cl = Color::White, ResId tsId = 0)
		{
			stateBackground = State(cl, tsId);
			return this;
		}
		ScrollBar* setStateButtonPressed(sf::Color cl = Color::White, ResId tsId = 0)
		{
			bScroll.setStatePressed( cl, tsId );
			return this;
		}
		ScrollBar* setStateButtonMouseOn(sf::Color cl = Color::White, ResId tsId = 0)
		{
			bScroll.setStateMouseOn(cl, tsId);
			return this;
		}
		ScrollBar* setStateButtonMouseOut(sf::Color cl = Color::White, ResId tsId = 0)
		{
			bScroll.setStateMouseOut(cl, tsId);
			return this;
		}
		ScrollBar* setStateButtonMouse(sf::Color cl = Color::White, ResId tsId = 0)
		{
			bScroll.setStateMouse(cl, tsId);
			return this;
		}
		ScrollBar* setStateButton(sf::Color cl = Color::White, ResId tsId = 0)
		{
			bScroll.setGlobalState(cl, tsId);
			return this;
		}

		ScrollBar* setWh( const Vector2f& v, float32 buttonLenght)
		{
			Super::setWh(v);
			if (axis == horizontal)
				bScroll.setWh({ buttonLenght, v.y });
			else
				bScroll.setWh({ v.x, buttonLenght});
			return this;
		}
		ScrollBar* setAxis(EAxis s)
		{
			if (axis != s)
			{
				axis = s;
			
				if (axis == horizontal)
					bScroll.setWh({ bScroll.getWh().y, getWh().y });
				else
					bScroll.setWh({ getWh().x, bScroll.getWh().x });
			}
			return this;
		}

		REDEFINE_SETTER_1(ScrollBar, setPosition, const Vector2f&);
		REDEFINE_SETTER_1(ScrollBar, setActivated, bool);

		
		////// getters
		float32 getProgres() const { return progress; }
		const Button& getButton() const { return bScroll; }
		State getStateBackground() const { return stateBackground; }
		State getStateButtonPressed() const { return bScroll.getStatePressed(); }
		State getStateButtonMouseOn() const { return bScroll.getStateMouseOn(); }
		State getStateButtonMouseOut() const { return bScroll.getStateMouseOut(); }
		EAxis getAxis() const { return axis; }
		float32 getButtonLenght() const
		{
			if (axis == horizontal)
				return bScroll.getWh().y;
			else
				return bScroll.getWh().x;
		}


		void runEvent() { eventUpdateProgress(progress); }

	protected:

		/// event called when the progress is changed (by buttons)
		function<void(float32&)> eventUpdateProgress{ [](float32&) {} };

		State stateBackground;

		/// movable part of the scrollbar
		Button bScroll;

	public:
		/// to avoid grabbing multiplay scrolls at once 
		int8 *bPressedAny = nullptr;
	
	protected:
		/// progress of the bar
		/// in range of [0,1] inclusive
		float32 progress;

		EAxis axis{horizontal};
		int8 bPressed : 1;
		
		void updateProgress();
		void updateButton();


	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};



}