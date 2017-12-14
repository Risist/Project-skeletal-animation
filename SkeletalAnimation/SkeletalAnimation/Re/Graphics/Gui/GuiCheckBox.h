/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#pragma once
#include <Re\Graphics\Gui\GuiButton.h>

namespace Gui
{

	/// checkbox class to hold boolean value
	/// works like normal button but holds state
	/// statePressed is used if b == true and no matter whether or not mouse is on button
	/// stateMouseOut is used when b == false
	/// stateMouseOn is used like in window
	/// lambda function is called when the object is pressed
	class CheckBox : public Button
	{
		SERIALISATION_NAME(CheckBox)
	public:
		CheckBox();
		
		////// events

		virtual void onUpdate(RenderTarget& wnd, RenderStates states) override;

		////// setters
		
		
		CheckBox* setStateOn(const sf::Color& _cl, ResId id = 0)
		{
			setStateMouseOn(_cl, id);
			return this;
		}
		CheckBox* setStateOff(const sf::Color& _cl, ResId id = 0)
		{
			setStateMouseOut(_cl, id);
			return this;
		}
		
		REDEFINE_SETTER_1(CheckBox, setPressEvent, function<void()>);
		REDEFINE_SETTER_1(CheckBox, setWh, const Vector2D& );
		REDEFINE_SETTER_1(CheckBox, setPosition, const Vector2f&);
		REDEFINE_SETTER_1(CheckBox, setActivated, bool);

		REDEFINE_SETTER_1(CheckBox, setMouseKey, sf::Mouse::Button);
		REDEFINE_SETTER_1(CheckBox, setShortKey, sf::Mouse::Button);
		REDEFINE_SETTER_1(CheckBox, setShortKey, sf::Keyboard::Key);
		REDEFINE_SETTER_1(CheckBox, setPressMode, Control::Key::EPressState);
		CheckBox* setValue(bool s)
		{
			value = s;
			return this;
		}

		/// getters

		/// returns actual state of checkbox
		bool getValue() const
		{
			return value;
		}
		State getStateOn() const { return Button::getStateMouseOn();  }
		State getStateOff() const { return Button::getStateMouseOut(); }

	private:
		/// value of field
		bool value;
	
		/// not used in the case
		REDEFINE_SETTER_2(CheckBox, setGlobalState, const sf::Color&, ResId);
		REDEFINE_SETTER_2(CheckBox, setStateMouse, const sf::Color&, ResId);
		REDEFINE_SETTER_2(CheckBox, setStateMouseOn, const sf::Color&, ResId);
		REDEFINE_SETTER_2(CheckBox, setStateMouseOut, const sf::Color&, ResId);
		REDEFINE_SETTER_2(CheckBox, setStatePressed, const sf::Color&, ResId);

		using Button::getStateMouseOn;
		using Button::getStateMouseOut;
		using Button::getStatePressed;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}