/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#pragma once
#include <Re\Graphics\Gui\GuiMenu.h>
#include <Re\Graphics\Gui\GuiScrollBar.h>

namespace Gui
{

	class ColorBar : public Menu
	{
		SERIALISATION_NAME(ColorBar);
	public:
		ColorBar();

	public: /////// events
		virtual void onUpdate(RenderTarget& wnd, RenderStates states) override;

	public: ////// setters

		/// set color represented by color bar
		ColorBar* setColorValue(Color cl);
		ColorBar* setColorMin(Color cl)
		{
			barColorMin = cl;
			return this;
		}
		ColorBar* setColorMax(Color cl)
		{
			barColorMax = cl;
			return this;
		}
		ColorBar* setEvent(function<void(Color cl)> ev)
		{
			eventUpdate = ev;
			return this;
		}
		ColorBar* setWh(const Vector2D& wh, float32 barHole, float32 buttonSize);
		REDEFINE_SETTER_1(ColorBar, setPosition, const Vector2f&);
		REDEFINE_SETTER_1(ColorBar, setActivated, bool);
		ColorBar* setStateButtonMouseOn(const sf::Color& _cl = Color::White, ResId tsId = 0);
		ColorBar* setStateButtonMouseOut(const sf::Color& _cl = Color::White, ResId tsId = 0);
		ColorBar* setStateButtonPressed(const sf::Color& _cl = Color::White, ResId tsId = 0);
		ColorBar* setStateButton(const sf::Color& _cl = Color::White, ResId tsId = 0);
		ColorBar* setStateButtonMouse(const sf::Color& _cl = Color::White, ResId tsId = 0);
		
		/// getters

		Color getColorMin() { return barColorMin; }
		Color getColorMax() { return barColorMax; }

		/// returns color holded by ColorBar
		Color getColorValue() const;


		void runEvent() { eventUpdate(getColorValue()); }

	protected:
		ScrollBar* _barRed;
		ScrollBar* _barGreen;
		ScrollBar* _barBlue;
		ScrollBar* _barAlpha;
		function<void(Color cl)> eventUpdate;
		
		/// color blend
		Color barColorMin;
		Color barColorMax;
		int8 bPressed = false;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

	/*class ColorBar : public Menu
	{
		SERIALISATION_NAME(ColorBar)
	public:
		ColorBar(const char* path);
		ColorBar(const Vector2f& halfWh = Vector2f(), float32 buttonSize = 10.f, float32 barOffset = 10.f);

		virtual void update(RenderTarget& wnd, RenderStates states) override;

		/// setters
		ColorBar* setColor(const sf::Color& cl);
		ColorBar* setPos(const sf::Vector2f& s)
		{
			pos = s;
			return this;
		}
		ColorBar* setColorBar(const Color& newColor);
		ColorBar* setColorButton(const Color& clOn, const Color& clOut, const Color& clPress);
		ColorBar* setBaseColor(Color cl)
		{
			barBaseColor = cl;
			return this;
		}
		ColorBar* setEvent(function<void(Color)> ev)
		{
			eventUpdate = ev;
			return this;
		}


		sf::Color getColor() const;
		

		shared_ptr<ScrollBar> _barRed;
		shared_ptr<ScrollBar> _barGreen;
		shared_ptr<ScrollBar> _barBlue;
		shared_ptr<ScrollBar> _barAlpha;
	
		Color barBaseColor;
		function<void(Color cl)> eventUpdate;
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};*/


}
