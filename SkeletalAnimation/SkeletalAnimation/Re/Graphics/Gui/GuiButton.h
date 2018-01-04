/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#pragma once
#include <Re\Graphics\Gui\GuiBase.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	/// Data depended on button state packed in struct
	struct State
	{
		State(const sf::Color& _cl = Color::White, ResId tsId = 0);
		State(ResId tsId, const sf::Color& _cl);
		void setTexture(ResId id)
		{
			tsId = id;
			ts = tsInst[id];
		}
		sf::Color cl;
		ResId tsId;
		ResourceManager::TextureInstance ts;

		void serialise_Index(const std::string& preName, std::ostream& file, Res::DataScriptSaver& saver) const;
		void deserialise_Index(const std::string& preName, std::istream& file, Res::DataScriptLoader& loader);
	};
	class Button : public Base
	{
		SERIALISATION_NAME(Button)
	public:
		Button();


	public: ////// events
		virtual void onUpdate(sf::RenderTarget& target, sf::RenderStates states) override;


	public: ////// setters
		Button* setGlobalState(const sf::Color& _cl = Color::White, ResId tsId = 0)
		{
			stateMouseOn = stateMouseOut = statePressed = State(_cl, tsId);
			return this;
		}
		Button* setStateMouse(const sf::Color& _cl = Color::White, ResId tsId = 0)
		{
			stateMouseOn = stateMouseOut = State(_cl,tsId);
			return this;
		}
		Button* setStateMouseOn(const sf::Color& _cl = Color::White, ResId tsId = 0)
		{
			stateMouseOn = State(_cl, tsId);
			return this;
		}
		Button* setStateMouseOut(const sf::Color& _cl = Color::White, ResId tsId = 0)
		{
			stateMouseOut = State(_cl, tsId);
			return this;
		}
		Button* setStatePressed(const sf::Color& _cl = Color::White, ResId tsId = 0)
		{
			statePressed = State(_cl, tsId);
			return this;
		}
		Button* setPressEvent(function<void()> ev)
		{
			eventOnPress = ev;
			return this;
		}
		Button* setWh(const Vector2f& wh)
		{
			Super::setWh(wh);
			sh.setSize(wh);
			sh.setOrigin(halfWh);
			return this;
		}
		REDEFINE_SETTER_1(Button, setPosition, const Vector2f&);
		REDEFINE_SETTER_1(Button, setActivated, bool);

		Button* setMouseKey(sf::Mouse::Button key)
		{
			mouseKey.setKeyCode(key);
			mouseKey.desiredState = Control::Key::EPressState::pressedOnce;
			return this;
		}
		Button* setShortKey(sf::Mouse::Button key)
		{
			shortKey.setKeyCode(key);
			shortKey.desiredState = Control::Key::EPressState::pressedOnce;
			return this;
		}
		Button* setShortKey(sf::Keyboard::Key key)
		{
			shortKey.setKeyCode(key);
			shortKey.desiredState = Control::Key::EPressState::pressedOnce;
			return this;
		}
		Button* setPressMode(Control::Key::EPressState s)
		{
			mouseKey.desiredState = s;
			shortKey.desiredState = s;
			return this;
		}

		////// getter
		State getStatePressed() const
		{
			return statePressed;
		}
		State getStateMouseOn() const
		{
			return statePressed;
		}
		State getStateMouseOut() const
		{
			return statePressed;
		}

		sf::Mouse::Button getMouseKey() const { return mouseKey.getAsMouseButton(); }
		sf::Mouse::Button getMouseShortKey() const { return shortKey.getAsMouseButton(); }
		sf::Keyboard::Key getKeyboardShortKey() const { return shortKey.getAsKeyboardKey(); }

		void runEvent() { eventOnPress(); }
	protected:
		/// mouse key activates the button only if mouse is at button
		bool isMouseOnWindow() const;
		Control::Key mouseKey{Control::Key(sf::Mouse::Left, Control::Key::EPressState::pressedOnce)};

		/// short key, activates button anytime
		Control::Key shortKey;
	
		/// Color & texture for each state:
		State stateMouseOn; ///<	mouse is on the button
		State statePressed; ///<	button is pressed
		State stateMouseOut;///<	mouse is not on the button

		/// what happeneds when button is pressed?
		function<void()> eventOnPress{ []() {} };

		/// rendering shape
		sf::RectangleShape sh;
	
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}