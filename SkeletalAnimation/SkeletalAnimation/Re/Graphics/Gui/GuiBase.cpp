/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include <Re\Graphics\Gui\GuiBase.h>

namespace Gui
{
	Base::Base(const sf::Vector2f& _pos) : position(_pos) {}
	
	void Base::serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const
	{
		saver.save("posX", position.x, 0.f);
		saver.save("posY", position.y, 0.f);
		saver.save("activated", activated, true);
		saver.save("whX", halfWh.x*2, 0.f);
		saver.save("whY", halfWh.y*2, 0.f);

	}
	void Base::deserialiseF(std::istream& file, Res::DataScriptLoader& loader)
	{
		position.x = loader.load("posX", 0.f);
		position.y = loader.load("posY", 0.f);
		halfWh.x = loader.load("whX", 0.f)*0.5f;
		halfWh.y = loader.load("whY", 0.f)*0.5f;

		setActivated( loader.load("activated", true) );
	}


}