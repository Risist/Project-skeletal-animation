/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include <Re\Graphics\Gui\GuiCheckBox.h>

namespace Gui
{

	CheckBox::CheckBox()
		: value(false)
	{
	}


	void Gui::CheckBox::onUpdate(RenderTarget & target, RenderStates states)
	{
		shortKey.reset(); mouseKey.reset();

		sh.setPosition(getActualPosition());

		bool mouseOn = isMouseOnWindow();

		if ((mouseKey.isReady() && mouseOn) || shortKey.isReady())
		{
			assert(eventOnPress);
			eventOnPress();

			value = !value;

			sh.setFillColor(statePressed.cl);
			statePressed.ts.set(sh);
		}

		if (value)
		{
			sh.setFillColor(statePressed.cl);
			statePressed.ts.set(sh);
		}
		else
		{
			sh.setFillColor(stateMouseOut.cl);
			stateMouseOut.ts.set(sh);
		}

		target.draw(sh, states);
	}


	void Gui::CheckBox::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Base::serialiseF(file, saver);
		saver.save("value", value, false);

		stateMouseOn.serialise_Index("on", file, saver);
		stateMouseOut.serialise_Index("off", file, saver);
	}
	void Gui::CheckBox::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);
		value = loader.load("value", false);

		setWh(halfWh*2.f);
		statePressed.deserialise_Index("on", file, loader);
		stateMouseOut.deserialise_Index("off", file, loader);
	}



}