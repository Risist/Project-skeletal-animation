/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include <Re\Graphics\Gui\GuiColorBar.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	ColorBar::ColorBar()
	{
		auto ev = [this](float& v)
		{
			if (eventUpdate)
				eventUpdate(getColorValue());

		};
		_barRed = add<Gui::ScrollBar>()->setEventUpdateProgress(ev);
		_barGreen = add<Gui::ScrollBar>()->setEventUpdateProgress(ev);
		_barBlue = add<Gui::ScrollBar>()->setEventUpdateProgress(ev);
		_barAlpha = add<Gui::ScrollBar>()->setEventUpdateProgress(ev);

		/*_barRed->bPressedAny = 
		_barGreen->bPressedAny = 
		_barBlue->bPressedAny = 
		_barAlpha->bPressedAny = &bPressed;
		*/

		barColorMin = Color(0, 0, 0, 0); 
		barColorMax = Color(255, 255, 255, 255);
	}
	void ColorBar::onUpdate(RenderTarget & wnd, RenderStates states)
	{
		bPressed = false;
		Menu::onUpdate(wnd, states);

		Color clBack = Color(
			clamp((float32)barColorMin.r + (float32)(barColorMax.r - barColorMin.r) * _barRed->getProgres(), 0.f, 255.f),
			clamp((float32)barColorMin.g + (float32)(barColorMax.g - barColorMin.g) * _barGreen->getProgres(), 0.f, 255.f),
			clamp((float32)barColorMin.b + (float32)(barColorMax.b - barColorMin.b) * _barBlue->getProgres(), 0.f, 255.f),
			clamp((float32)barColorMin.a + (float32)(barColorMax.a - barColorMin.a) * _barAlpha ->getProgres(), 0.f, 255.f)
		);
		_barRed->setStateBackground(clBack);
		_barGreen->setStateBackground(clBack);
		_barBlue->setStateBackground(clBack);
		_barAlpha->setStateBackground(clBack);
	}
	ColorBar * ColorBar::setColorValue(Color cl)
	{
		_barRed->setProgress(	clamp( (float32)(cl.r) / 255.f, 0.f, 1.f) );
		_barGreen->setProgress(	clamp( (float32)(cl.g) / 255.f, 0.f, 1.f) );
		_barBlue->setProgress(	clamp( (float32)(cl.b) / 255.f, 0.f, 1.f) );
		_barAlpha->setProgress(	clamp( (float32)(cl.a) / 255.f, 0.f, 1.f) );

		Color clBack = Color(
			clamp( (float32)barColorMin.r + (float32)(barColorMax.r - barColorMin.r) * (float32)(cl.r), 0.f, 255.f),
			clamp( (float32)barColorMin.g + (float32)(barColorMax.g - barColorMin.g) * (float32)(cl.g), 0.f, 255.f),
			clamp( (float32)barColorMin.b + (float32)(barColorMax.b - barColorMin.b) * (float32)(cl.b), 0.f, 255.f),
			clamp( (float32)barColorMin.a + (float32)(barColorMax.a - barColorMin.a) * (float32)(cl.a), 0.f, 255.f)
		);
		_barRed->setStateBackground(clBack);
		_barGreen->setStateBackground(clBack);
		_barBlue->setStateBackground(clBack);
		_barAlpha->setStateBackground(clBack);

		return this;
	}
	Color ColorBar::getColorValue() const
	{
		return Color(
			(sf::Uint32)clamp<float>((_barRed	->getProgres() * 255.f), 0.f, 255.f),
			(sf::Uint32)clamp<float>((_barGreen	->getProgres() * 255.f), 0.f, 255.f),
			(sf::Uint32)clamp<float>((_barBlue	->getProgres() * 255.f), 0.f, 255.f),
			(sf::Uint32)clamp<float>((_barAlpha	->getProgres() * 255.f), 0.f, 255.f)
		);
	}
	void ColorBar::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		/// TODO
	}
	void ColorBar::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{	
		Base::deserialiseF(file, loader);

		setColorValue(sf::Color::White);
		setWh(Vector2D(halfWh.x*2, halfWh.y * 2), loader.load("barHole", 10.f), loader.load("butonSize", 10.f));

		barColorMin = Color(
			loader.load("backMinClR", 0),
			loader.load("backMinClG", 0),
			loader.load("backMinClB", 0),
			loader.load("backMinClA", 0)
		);
		barColorMax = Color(
			loader.load("backMaxClR", 255),
			loader.load("backMaxClG", 255),
			loader.load("backMaxClB", 255),
			loader.load("backMaxClA", 255)
		);

		State buttonMouseOn; buttonMouseOn.deserialise_Index("buttonOn", file, loader);
		State buttonMouseOut; buttonMouseOut.deserialise_Index("buttonOut", file, loader);
		State buttonPressed; buttonPressed.deserialise_Index("buttonPressed", file, loader);
		
		setStateButtonMouseOn(buttonMouseOn.cl, buttonMouseOn.tsId);
		setStateButtonMouseOut(buttonMouseOut.cl, buttonMouseOut.tsId);
		setStateButtonPressed(buttonPressed.cl, buttonPressed.tsId);
	}
	ColorBar * ColorBar::setWh(const Vector2D & wh, float32 barHole, float32 buttonSize)
	{
		Base::setWh(wh);

		float32 barOffset = wh.y * 0.25;
		_barRed->setPosition(sf::Vector2f(0, -1.5f*barOffset));
		_barGreen->setPosition(sf::Vector2f(0, -0.5f*barOffset));
		_barBlue->setPosition(sf::Vector2f(0, 0.5f*barOffset));
		_barAlpha->setPosition(sf::Vector2f(0, 1.5f*barOffset));

		_barRed		->setWh(Vector2D(wh.x,	barOffset - barHole),	buttonSize);
		_barGreen	->setWh(Vector2D(wh.x,	barOffset - barHole),	buttonSize);
		_barBlue	->setWh(Vector2D(wh.x,	barOffset - barHole),	buttonSize);
		_barAlpha	->setWh(Vector2D(wh.x,	barOffset - barHole),	buttonSize);

		return this;
	}
	ColorBar * ColorBar::setStateButtonMouseOn(const sf::Color & _cl, ResId tsId)
	{
		_barRed		->setStateButtonMouseOn(_cl, tsId);
		_barGreen	->setStateButtonMouseOn(_cl, tsId);
		_barBlue	->setStateButtonMouseOn(_cl, tsId);
		_barAlpha	->setStateButtonMouseOn(_cl, tsId);
		return this;
	}
	ColorBar * ColorBar::setStateButtonMouseOut(const sf::Color & _cl, ResId tsId)
	{
		_barRed->setStateButtonMouseOut(_cl, tsId);
		_barGreen->setStateButtonMouseOut(_cl, tsId);
		_barBlue->setStateButtonMouseOut(_cl, tsId);
		_barAlpha->setStateButtonMouseOut(_cl, tsId);
		return this;
	}
	ColorBar * ColorBar::setStateButtonPressed(const sf::Color & _cl, ResId tsId)
	{
		_barRed->setStateButtonPressed(_cl, tsId);
		_barGreen->setStateButtonPressed(_cl, tsId);
		_barBlue->setStateButtonPressed(_cl, tsId);
		_barAlpha->setStateButtonPressed(_cl, tsId);
		return this;
	}
	ColorBar * ColorBar::setStateButton(const sf::Color & _cl, ResId tsId)
	{
		_barRed->setStateButton(_cl, tsId);
		_barGreen->setStateButton(_cl, tsId);
		_barBlue->setStateButton(_cl, tsId);
		_barAlpha->setStateButton(_cl, tsId);
		return this;
	}
	ColorBar * ColorBar::setStateButtonMouse(const sf::Color & _cl, ResId tsId)
	{
		_barRed->setStateButtonMouse(_cl, tsId);
		_barGreen->setStateButtonMouse(_cl, tsId);
		_barBlue->setStateButtonMouse(_cl, tsId);
		_barAlpha->setStateButtonMouse(_cl, tsId);
		return this;
	}
}

/**
namespace Gui
{
	ColorBar::ColorBar(const char * path)
		:_barRed(new ScrollBar()),
		_barGreen(new ScrollBar()),
		_barBlue(new ScrollBar()),
		_barAlpha(new ScrollBar())
	{
		add(_barRed);
		add(_barGreen);
		add(_barBlue);
		add(_barAlpha);

		auto ev = [&](float32&)
		{
			if (eventUpdate)
				eventUpdate(getColor());
		};
		_barRed->setEvent(ev);
		_barGreen->setEvent(ev);
		_barBlue->setEvent(ev);
		_barAlpha->setEvent(ev);

		deserialise(path);
	}
	ColorBar::ColorBar(const Vector2f& _halfWh, float32 buttonSize, float32 barOffset)
		:_barRed(new ScrollBar() ),
		_barGreen(new ScrollBar()),
		_barBlue(new ScrollBar()),
		_barAlpha(new ScrollBar())
	{
		add(_barRed);
		add(_barGreen);
		add(_barBlue);
		add(_barAlpha);
		
		auto ev = [&](float32&)
		{
			if(eventUpdate)
				eventUpdate(getColor());
		};
		_barRed->setEvent(ev);
		_barGreen->setEvent(ev);
		_barBlue->setEvent(ev);
		_barAlpha->setEvent(ev);


		halfWh = _halfWh;
		float32 barSizeX = halfWh.x;
		float32 barSizeY = halfWh.y;

		halfWh.y = (barSizeY + barOffset) *1.5f;

		_barRed->bBackground->halfWh = Vector2D(barSizeX, barSizeY);
		_barGreen->bBackground->halfWh = Vector2D(barSizeX, barSizeY);
		_barBlue->bBackground->halfWh = Vector2D(barSizeX, barSizeY);
		_barAlpha->bBackground->halfWh = Vector2D(barSizeX, barSizeY);

		_barRed->setPos(sf::Vector2f(0, -1.5f*barOffset));
		_barGreen->setPos(sf::Vector2f(0, -0.5f*barOffset));
		_barBlue->setPos(sf::Vector2f(0, 0.5f*barOffset));
		_barAlpha->setPos(sf::Vector2f(0, 1.5f*barOffset));

		_barRed->bScroll->halfWh = Vector2D(buttonSize, barSizeY);
		_barGreen->bScroll->halfWh = Vector2D(buttonSize, barSizeY);
		_barBlue->bScroll->halfWh = Vector2D(buttonSize, barSizeY);
		_barAlpha->bScroll->halfWh = Vector2D(buttonSize, barSizeY);
	}
	void ColorBar::update(RenderTarget & wnd, RenderStates states)
	{

		Color cl = getColor();
		Color clReturn = barBaseColor;
		clReturn.r = (sf::Uint8)((float64)cl.r * (float64)barBaseColor.r/255.f);
		clReturn.g = (sf::Uint8)((float64)cl.g * (float64)barBaseColor.g / 255.f);
		clReturn.b = (sf::Uint8)((float64)cl.b * (float64)barBaseColor.b / 255.f);
		clReturn.a = (sf::Uint8)((float64)cl.a * (float64)barBaseColor.a / 255.f);


		setColorBar(clReturn);
		Menu::update(wnd,states);
	}

	sf::Color ColorBar::getColor() const
	{
		return sf::Color(
			(sf::Uint8)(_barRed->getProgres()*255.f),
			(sf::Uint8)(_barGreen->getProgres()*255.f),
			(sf::Uint8)(_barBlue->getProgres()*255.f),
			(sf::Uint8)(_barAlpha->getProgres()*255.f)
		);
	}
	ColorBar* ColorBar::setColor(const sf::Color & cl)
	{
		_barRed->setProgress((float32)cl.r/255.f);
		_barGreen->setProgress((float32)cl.g / 255.f);
		_barBlue->setProgress((float32)cl.b / 255.f);
		_barAlpha->setProgress((float32)cl.a / 255.f);

		return this;
	}
	void ColorBar::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
	}
	void ColorBar::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);

		setColor(sf::Color::White);

		float32 buttonSize = loader.load("butonSize", 10.f);
		float32 barOffset = loader.load("barOffset", 10.f);
		float32 barSizeX = halfWh.x;
		float32 barSizeY = halfWh.y;

		halfWh.y = (barSizeY + barOffset) *1.5f;

		_barRed->bBackground->halfWh = Vector2D(barSizeX, barSizeY);
		_barGreen->bBackground->halfWh = Vector2D(barSizeX, barSizeY);
		_barBlue->bBackground->halfWh = Vector2D(barSizeX, barSizeY);
		_barAlpha->bBackground->halfWh = Vector2D(barSizeX, barSizeY);

		_barRed->setPos(sf::Vector2f(0,		-1.5f*barOffset));
		_barGreen->setPos( sf::Vector2f(0, -0.5f*barOffset) );
		_barBlue->setPos( sf::Vector2f(0, 0.5f*barOffset) );
		_barAlpha->setPos( sf::Vector2f(0, 1.5f*barOffset) );
		
		_barRed->bScroll->halfWh = Vector2D(buttonSize, barSizeY);
		_barGreen->bScroll->halfWh = Vector2D(buttonSize, barSizeY);
		_barBlue->bScroll->halfWh = Vector2D(buttonSize, barSizeY);
		_barAlpha->bScroll->halfWh = Vector2D(buttonSize, barSizeY);

		Color clButtonOn(
			loader.load("onClR",255u),
			loader.load("onClG", 255u),
			loader.load("onClB", 255u),
			loader.load("onClA", 255u)
			);
		Color clButtonOut(
			loader.load("outClR", 255u),
			loader.load("outClG", 255u),
			loader.load("outClB", 255u),
			loader.load("outClA", 255u)
		);
		Color clButtonPress(
			loader.load("pressClR", 255u),
			loader.load("pressClG", 255u),
			loader.load("pressClB", 255u),
			loader.load("pressClA", 255u)
		);
		Color clBar(
			loader.load("barClR", 255u),
			loader.load("barClG", 255u),
			loader.load("barClB", 255u),
			loader.load("barClA", 255u)
		);
		barBaseColor = clBar;

		setColorBar(clBar);
		setColorButton(clButtonOn, clButtonOut, clButtonPress);

		int ts = loader.load("onTs", (size_t)-1);
		if (ts != -1)
			_barRed->bScroll->stateMouseOn.ts =
			_barGreen->bScroll->stateMouseOn.ts =
			_barBlue->bScroll->stateMouseOn.ts =
			_barAlpha->bScroll->stateMouseOn.ts = tsInst[ts];


		ts = loader.load("outTs", (size_t)-1);
		if (ts != -1) 
			_barRed->bScroll->stateMouseOut.ts =
			_barGreen->bScroll->stateMouseOut.ts =
			_barBlue->bScroll->stateMouseOut.ts =
			_barAlpha->bScroll->stateMouseOut.ts = tsInst[ts];

		ts = loader.load("pressTs", (size_t)-1);
		if (ts != -1)
			_barRed->bScroll->statePressed.ts =
			_barGreen->bScroll->statePressed.ts =
			_barBlue->bScroll->statePressed.ts =
			_barAlpha->bScroll->statePressed.ts = tsInst[ts];

		ts = loader.load("barTs", (size_t)-1);
		if (ts != -1)
			_barRed->bBackground->stateMouseOn.ts =
			_barRed->bBackground->stateMouseOut.ts =
			_barRed->bBackground->statePressed.ts =
			
			_barGreen->bBackground->stateMouseOn.ts =
			_barGreen->bBackground->stateMouseOut.ts =
			_barGreen->bBackground->statePressed.ts =
			
			_barBlue->bBackground->stateMouseOn.ts =
			_barBlue->bBackground->stateMouseOut.ts =
			_barBlue->bBackground->statePressed.ts =

			_barAlpha->bBackground->stateMouseOn.ts =
			_barAlpha->bBackground->stateMouseOut.ts =
			_barAlpha->bBackground->statePressed.ts = tsInst[ts];

	}

	ColorBar* ColorBar::setColorBar(const Color& clBar)
	{
		_barRed->bBackground->stateMouseOn.cl = clBar;
		_barRed->bBackground->stateMouseOut.cl = clBar;
		_barRed->bBackground->statePressed.cl = clBar;

		_barGreen->bBackground->stateMouseOn.cl = clBar;
		_barGreen->bBackground->stateMouseOut.cl = clBar;
		_barGreen->bBackground->statePressed.cl = clBar;

		_barBlue->bBackground->stateMouseOn.cl = clBar;
		_barBlue->bBackground->stateMouseOut.cl = clBar;
		_barBlue->bBackground->statePressed.cl = clBar;

		_barAlpha->bBackground->stateMouseOn.cl = clBar;
		_barAlpha->bBackground->stateMouseOut.cl = clBar;
		_barAlpha->bBackground->statePressed.cl = clBar;

		return this;
	}
	ColorBar* ColorBar::setColorButton(const Color& clButtonOn, const Color& clButtonOut, const Color& clButtonPress)
	{
		_barRed->bScroll->stateMouseOn.cl = clButtonOn;
		_barRed->bScroll->stateMouseOut.cl = clButtonOut;
		_barRed->bScroll->statePressed.cl = clButtonPress;

		_barGreen->bScroll->stateMouseOn.cl = clButtonOn;
		_barGreen->bScroll->stateMouseOut.cl = clButtonOut;
		_barGreen->bScroll->statePressed.cl = clButtonPress;

		_barBlue->bScroll->stateMouseOn.cl = clButtonOn;
		_barBlue->bScroll->stateMouseOut.cl = clButtonOut;
		_barBlue->bScroll->statePressed.cl = clButtonPress;

		_barAlpha->bScroll->stateMouseOn.cl = clButtonOn;
		_barAlpha->bScroll->stateMouseOut.cl = clButtonOut;
		_barAlpha->bScroll->statePressed.cl = clButtonPress;

		return this;
	}
}*/