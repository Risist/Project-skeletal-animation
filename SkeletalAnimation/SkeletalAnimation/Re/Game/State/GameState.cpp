/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include <Re\Game\State\GameState.h>
#include <Re\Graphics\Gui\Gui.h>
//#include <Re\Game\GameWorld.h>

namespace Game
{
	State::State()
	{
	}

	void State::onStart()
	{
	}

	void State::onExit()
	{
		Gui::gui.clear();
		//Game::world.clear();
	}

}
