/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include <Re\Graphics\Gui\GuiText.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	Text::Text()
	{
		txt.setFont(res.fonts[1]);
		txt.setFillColor(Color::White);
		txt.setCharacterSize(25u);
	}

	void Text::onUpdate(RenderTarget & target, RenderStates states)
	{
		txt.setString(str);
		txt.setPosition(getActualPosition());
		
		/// multiplaying in X axes by 0.25 seems to work
		/// Probably because of twice multiplaying by 0.5 ( from size and character size)
		/// Take care over that
		txt.setOrigin(
			static_cast<float>(str.size()* txt.getCharacterSize()) *0.25f,
			static_cast<float>(txt.getCharacterSize())*0.5f);

		target.draw(txt, states);
	}



	void Text::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		/// TODO
	}

	void Text::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file,loader);
		
		str = loader.loadRaw("str", "");

		Color cl;
		cl.r = loader.load("clR", 255);
		cl.g = loader.load("clG", 255);
		cl.b = loader.load("clB", 255);
		cl.a = loader.load("clA", 255);
		txt.setFillColor(cl);

		cl.r = loader.load("outClR", 255);
		cl.g = loader.load("outClG", 255);
		cl.b = loader.load("outClB", 255);
		cl.a = loader.load("outClA", 255);
		txt.setOutlineColor(cl);

		txt.setOutlineThickness(loader.load("outThickness", 0.f));

		txt.setCharacterSize(loader.load("size", 25));
		txt.setFont(fontInst[loader.load("font", (ResId)1)]);
	}

}