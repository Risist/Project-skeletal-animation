/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#pragma once
#include <Re\Graphics\Gui\GuiButton.h>
#include <Re\Graphics\Gui\GuiText.h>

namespace Gui
{
	class NamedButton : public Button
	{
		SERIALISATION_NAME(NamedButton)
	public:
		NamedButton();
		
		////// events

		virtual void onUpdate(sf::RenderTarget& target, sf::RenderStates states) override;


		////// getters

		REDEFINE_SETTER_2(NamedButton, setGlobalState, const sf::Color&, ResId);
		REDEFINE_SETTER_2(NamedButton, setStateMouse, const sf::Color&, ResId);
		
		//REDEFINE_SETTER_2(NamedButton, setStateMouseOn, const sf::Color&, ResId);
		//REDEFINE_SETTER_2(NamedButton, setStateMouseOut, const sf::Color&, ResId);
		//REDEFINE_SETTER_2(NamedButton, setStatePressed, const sf::Color&, ResId);
		NamedButton* setStateMouseOn(const sf::Color& cl = sf::Color::White, ResId tsId = 0)
		{
			Super::setStateMouseOn(cl, tsId);
			return this;
		}
		NamedButton* setStateMouseOut(const sf::Color& cl = sf::Color::White, ResId tsId = 0)
		{
			Super::setStateMouseOut(cl, tsId);
			return this;
		}
		NamedButton* setStatePressed(const sf::Color& cl = sf::Color::White, ResId tsId = 0)
		{
			Super::setStatePressed(cl, tsId);
			return this;
		}

		REDEFINE_SETTER_1(NamedButton, setPressEvent, function<void()>);
		REDEFINE_SETTER_1(NamedButton, setWh, const Vector2D&);
		REDEFINE_SETTER_1(NamedButton, setPosition, const Vector2f&);
		REDEFINE_SETTER_1(NamedButton, setActivated, bool);

		REDEFINE_SETTER_1(NamedButton, setMouseKey, sf::Mouse::Button);
		REDEFINE_SETTER_1(NamedButton, setShortKey, sf::Mouse::Button);
		REDEFINE_SETTER_1(NamedButton, setShortKey, sf::Keyboard::Key);
		REDEFINE_SETTER_1(NamedButton, setPressMode, Control::Key::EPressState);
		NamedButton* setName(const char* s)
		{
			text.setStr(s);
			return this;
		}
		NamedButton* setTextColor(Color color)
		{
			text.setColor(color);
			return this;
		}
		NamedButton* setTextSize(unsigned int s)
		{
			text.setSize(s);
			return this;
		}
		NamedButton* setTextOutlineColor(Color color)
		{
			text.setOutlineColor(color);
			return this;
		}
		NamedButton* setTextOutlineThickness(float s)
		{
			text.setOutlineThickness(s);
			return this;
		}
		NamedButton* setTextStyle(sf::Uint32 style)
		{
			text.setStyle(style);
			return this;
		}
		NamedButton* setTextOffset(const Vector2f& s)
		{
			text.setPosition(s);
			return this;
		}


		////// getters

		Text& getText() { return text; }

	private:
		Text text;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};
}