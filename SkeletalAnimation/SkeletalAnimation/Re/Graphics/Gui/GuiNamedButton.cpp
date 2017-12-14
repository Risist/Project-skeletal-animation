/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include <Re\Graphics\Gui\GuiNamedButton.h>

namespace Gui
{
	NamedButton::NamedButton()
	{

	}
	
	void NamedButton::onUpdate(sf::RenderTarget & target, sf::RenderStates states)
	{
		Button::onUpdate(target, states);
		text.updateActualPosition(getActualPosition());
		text.onUpdate(target, states);
	}

	void NamedButton::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Button::serialiseF(file, saver);
		////// TODO
	}

	void NamedButton::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Button::deserialiseF(file, loader);
		setName(loader.loadRaw("name", "").c_str() );
		setTextColor(Color(
			loader.load("textClR", 255u),
			loader.load("textClG", 255u),
			loader.load("textClB", 255u),
			loader.load("textClA", 255u)
		));
		setTextOutlineColor(Color(
			loader.load("textOutlineClR", 255u),
			loader.load("textOutlineClG", 255u),
			loader.load("textOutlineClB", 255u),
			loader.load("textOutlineClA", 255u)
		));
		setTextOutlineThickness(loader.load("textThickness", 0.f));
		setTextSize(loader.load("textSize", 20u));

		setTextOffset(Vector2f(loader.load("textOffsetX", 0.f), loader.load("textOffsetY", 0.f)));
	}

}