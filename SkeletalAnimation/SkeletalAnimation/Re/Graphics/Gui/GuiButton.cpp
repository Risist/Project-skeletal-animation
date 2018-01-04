/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include <Re\Graphics\Gui\GuiButton.h>
#include <Re\Graphics\ResourceManager.h>

extern RenderWindow wnd;

namespace Gui
{
	State::State(const sf::Color& _cl, ResId _tsId)
		:  cl(_cl),  tsId(_tsId), ts(tsInst[_tsId])
	{
		
	}

	State::State(ResId _tsId, const sf::Color & _cl)
		: cl(_cl), tsId(_tsId), ts(tsInst[_tsId])
	{
	}

	void State::serialise_Index(const std::string & preName, std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save<ResId>(preName + "Ts", tsId, (ResId)0);

		saver.save<int>(preName + "ClR", cl.r, 255u);
		saver.save<int>(preName + "ClG", cl.g, 255u);
		saver.save<int>(preName + "ClB", cl.b, 255u);
		saver.save<int>(preName + "ClA", cl.a, 255u);
	}

	void State::deserialise_Index(const std::string & preName, std::istream & file, Res::DataScriptLoader & loader)
	{
		tsId = loader.load<ResId>( preName + "Ts", (ResId)0);
		if (tsId) ts = tsInst[tsId];

		cl.r = loader.load(preName + "ClR", 255);
		cl.g = loader.load(preName + "ClG", 255);
		cl.b = loader.load(preName + "ClB", 255);
		cl.a = loader.load(preName + "ClA", 255);
	}


	Button::Button()
	{
		setShortKey(sf::Keyboard::Unknown);
	}
	void Button::onUpdate(sf::RenderTarget & target, sf::RenderStates states)
	{
		shortKey.reset(); mouseKey.reset();

		sh.setPosition(getActualPosition());

		bool mouseOn = isMouseOnWindow();
		bool mousePress = mouseKey.isReady();
		bool shortPress = shortKey.isReady();

		if ((mouseKey.isReadySimple() && mouseOn) || shortKey.isReadySimple())
		{
			if (shortPress || mousePress)
			{
				assert(eventOnPress);
				eventOnPress();
			}

			sh.setFillColor(statePressed.cl);
			statePressed.ts.set(sh);
		}
		else if (mouseOn)
		{
			sh.setFillColor(stateMouseOn.cl);
			stateMouseOn.ts.set(sh);
		}
		else
		{
			sh.setFillColor(stateMouseOut.cl);
			stateMouseOut.ts.set(sh);
		}

		target.draw(sh, states);
	}

	bool Button::isMouseOnWindow() const
	{
		Vector2D mousePos = sf::Mouse::getPosition(wnd);
		return mousePos.x > getActualPosition().x - halfWh.x &&
			mousePos.x < getActualPosition().x + halfWh.x	&&
			mousePos.y > getActualPosition().y - halfWh.y	&&
			mousePos.y < getActualPosition().y + halfWh.y;
	}

	void Button::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Base::serialiseF(file, saver);

		stateMouseOn.serialise_Index("on", file, saver);
		stateMouseOut.serialise_Index("out", file, saver);
		statePressed.serialise_Index("press", file, saver);
	}

	void Button::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);
		setWh(halfWh*2.f);
		stateMouseOn.deserialise_Index("on", file, loader);
		stateMouseOut.deserialise_Index("out", file, loader);
		statePressed.deserialise_Index("press", file, loader);
	}
}