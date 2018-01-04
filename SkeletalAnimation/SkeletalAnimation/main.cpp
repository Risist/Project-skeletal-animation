#include <Re\ReEngine.h>
#include "Editor\EditorState.h"

Clock performanceClock;
RenderWindow wnd;

void init()
{
	srand((unsigned int)time(nullptr));
	wnd.create(VideoMode(1000, 600), "ReEngine");
	wnd.setVerticalSyncEnabled(true);

	cam.create(Vector2D((float32)wnd.getSize().x, (float32)wnd.getSize().y));
	cam.setBackgroundColor(Color(0, 0, 0));
	cam.setDarkness(1);
	cam.setBackgroundColor(Color(200, 200, 200));

	
	Game::stateManager.setState(new Editor::StateModel);

	performanceClock.restart();
}

#undef RE_DEBUG

void update()
{

	performanceClock.restart();


	Game::stateManager.onUpdate();

	/// performance checks
#ifdef RE_DEBUG
	sf::Text txt;

	if (performanceClock.getElapsedTime().asMilliseconds() < 100)
	{
		static float32 average = 0.f;
		int32 actualTime = performanceClock.getElapsedTime().asMilliseconds();
		average = (average * 99.f + (float)actualTime) / 100.f;

		txt.setPosition(0, 0);
		txt.setFont(fontInst[1]);
		txt.setCharacterSize(35);
		txt.setFillColor(Color::White);
		txt.setStyle(sf::Text::Bold);
		std::stringstream ss;
		ss << "ms: " << average;
		txt.setString(ss.str());
	}

	wnd.draw(txt);
#endif

}
void out()
{

}


int main()
{
	init();

	while (wnd.isOpen())
	{
		Event ev;
		while (wnd.pollEvent(ev))
		{
			if (ev.type == Event::Closed
				|| (ev.type == Event::KeyPressed && ev.key.code == sf::Keyboard::Escape))
				wnd.close();
		}
		update();

		wnd.display();
	}
	out();
}