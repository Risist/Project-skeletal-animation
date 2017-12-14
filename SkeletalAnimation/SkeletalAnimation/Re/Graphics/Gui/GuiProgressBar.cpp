/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include <Re\Graphics\Gui\GuiProgressBar.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	ProgressBar::ProgressBar()
	{
	}


	void ProgressBar::onUpdate(RenderTarget & wnd, RenderStates states)
	{
		/// background
		{
			sf::RectangleShape sh;
			sh.setPosition(getActualPosition());

			sh.setSize(Vector2f(halfWh.x * 2, halfWh.y * 2));
			sh.setOrigin(halfWh);

			sh.setFillColor(background.cl);
			background.ts.set(sh);
			wnd.draw(sh, states);
		}

		{
			sf::ConvexShape sh(4);
			sh.setPosition(getActualPosition());

			sh.setFillColor(foreground.cl);
			foreground.ts.set(sh);
			
			directionMode(sh, this);

			wnd.draw(sh, states);
		}
	}

	void ProgressBar::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
	}
	void ProgressBar::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);
		progress = loader.load("progress", 1.f);

		background.deserialise_Index("back", file, loader);
		foreground.deserialise_Index("fore", file, loader);
	
		string dir = loader.load<string>("direction", "left");
		if (dir == "leftt")
			directionMode = ProgressBar::directionXLeft;
		else if (dir == "xMiddle")
			directionMode = ProgressBar::directionXMiddle;
		else if (dir == "right")
			directionMode = ProgressBar::directionXRight;
		else if (dir == "up")
			directionMode = ProgressBar::directionYUp;
		else if (dir == "yMiddle")
			directionMode = ProgressBar::directionYMiddle;
		else if (dir == "down")
			directionMode = ProgressBar::directionYDown;
	}
	void ProgressBar::directionXLeft(sf::ConvexShape & sh, Gui::ProgressBar * pb)
	{
		sh.setPoint(0, Vector2D(pb->halfWh.x - pb->halfWh.x * 2 * pb->progress, -pb->halfWh.y));
		sh.setPoint(1, Vector2D(pb->halfWh.x, -pb->halfWh.y));
		sh.setPoint(2, Vector2D(pb->halfWh.x, pb->halfWh.y));
		sh.setPoint(3, Vector2D(pb->halfWh.x - pb->halfWh.x * 2 * pb->progress, pb->halfWh.y));
	}
	void ProgressBar::directionXMiddle(sf::ConvexShape & sh, Gui::ProgressBar * pb)
	{
		
		sh.setPoint(0, Vector2D(-pb->halfWh.x * pb->progress, -pb->halfWh.y));
		sh.setPoint(1, Vector2D(pb->halfWh.x * pb->progress, -pb->halfWh.y));
		sh.setPoint(2, Vector2D(pb->halfWh.x * pb->progress, pb->halfWh.y));
		sh.setPoint(3, Vector2D(-pb->halfWh.x * pb->progress, pb->halfWh.y));
	}
	void ProgressBar::directionXRight(sf::ConvexShape & sh, Gui::ProgressBar * pb)
	{
		sh.setPoint(0, Vector2D(-pb->halfWh.x, -pb->halfWh.y));
		sh.setPoint(1, Vector2D(-pb->halfWh.x + pb->halfWh.x * 2 * pb->progress, -pb->halfWh.y));
		sh.setPoint(2, Vector2D(-pb->halfWh.x + pb->halfWh.x * 2 * pb->progress, pb->halfWh.y));
		sh.setPoint(3, Vector2D(-pb->halfWh.x, pb->halfWh.y));
	}
	void ProgressBar::directionYUp(sf::ConvexShape & sh, Gui::ProgressBar * pb)
	{
		sh.setPoint(0, Vector2D(-pb->halfWh.x, -pb->halfWh.y + pb->halfWh.y * 2 * (1 - pb->progress)));
		sh.setPoint(1, Vector2D(pb->halfWh.x, -pb->halfWh.y + pb->halfWh.y * 2 * (1 - pb->progress)));
		sh.setPoint(2, Vector2D(pb->halfWh.x, pb->halfWh.y));//
		sh.setPoint(3, Vector2D(-pb->halfWh.x, pb->halfWh.y));//
	}
	void ProgressBar::directionYMiddle(sf::ConvexShape & sh, Gui::ProgressBar * pb)
	{
		sh.setPoint(0, Vector2D(-pb->halfWh.x, -pb->halfWh.y* pb->progress));
		sh.setPoint(1, Vector2D(pb->halfWh.x, -pb->halfWh.y* pb->progress));
		sh.setPoint(2, Vector2D(pb->halfWh.x, pb->halfWh.y* pb->progress));
		sh.setPoint(3, Vector2D(-pb->halfWh.x, pb->halfWh.y* pb->progress));
	}
	void ProgressBar::directionYDown(sf::ConvexShape & sh, Gui::ProgressBar * pb)
	{
		sh.setPoint(0, Vector2D(-pb->halfWh.x, -pb->halfWh.y)); //
		sh.setPoint(1, Vector2D(pb->halfWh.x, -pb->halfWh.y)); //
		sh.setPoint(2, Vector2D(pb->halfWh.x, -pb->halfWh.y + pb->halfWh.y * 2 * pb->progress));
		sh.setPoint(3, Vector2D(-pb->halfWh.x, -pb->halfWh.y + pb->halfWh.y * 2 * pb->progress));
	}
}
