/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include <Re\Graphics\Gui\Gui.h>
#include <Re\Graphics\Gui\GuiSpecial.h>

namespace Gui
{
	Menu::Menu(const sf::Vector2f& pos)
		: Base(pos)
	{
	}

	void Menu::onUpdate(RenderTarget& wnd, RenderStates states)
	{
		for(auto it = el.begin(); it != el.end(); ++it)
			if ( *it && it->get()->isActivated()) // update an element if is not hidden
			{
				it->get()->updateActualPosition(getActualPosition());
				it->get()->onUpdate(wnd, states);
			}
	}
	void Menu::onSetActivated(bool s)
	{
		for (auto it = el.begin(); it != el.end(); ++it)
			it->get()->onSetActivated(s);
	}
	void Menu::remove(size_t id)
	{
		el.erase(el.begin() + id);
	}
	void Menu::remove(Gui::Base * ptr)
	{
		for (auto it = el.begin(); it != el.end(); ++it)
			if ((*it).get() == ptr)
			{
				el.erase(it);
				return;
			}
	}
	void Menu::clear()
	{
		el.clear();
	}

	Base* Menu::desetializeInclude(Res::DataScriptLoader & loader)
	{
		string path = loader.loadRaw("path", "wrong_path");
		if (path == "wrong_path")
			cerr << "At menu deserialize include path is not set\n";
		ifstream file(path);
		if (file)
		{
			Res::DataScriptLoader _loader;
			_loader.nextLine(file);
			string type = _loader.load<string>("type", "UNDEFINED");
			auto sh = Gui::Base::creationFunction(type);
			if (sh)
			{
				sh->deserialise(file, _loader);
				return sh;
			}
			else
			{
				cerr << "Gui type: \"" << type << "\" is undefined" << endl;
			}
		}
		else
			cerr << "failed to open the file to load: \"" << path << "\"";

		return nullptr;
	}
	void Menu::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Base::serialiseF(file, saver);
		
		auto it = el.begin();
		{
			saver.save("type", (*it)->getSerialisationName() );
			(*it)->serialise(file, saver);
		}
		DATA_SCRIPT_MULTILINE_SAVE(file, saver, it != el.end());
	}
	void Menu::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);
		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string type = loader.load<string>("type", "UNDEFINED");

			Base* sh;

			/// include the element from other file
			if (type == "Include")
			{
				sh = desetializeInclude(loader);
				if (sh)
				{
					Vector2D pos(loader.load("posX", 0.f), loader.load("posY", 0.f));
					sh->setPosition(pos + sh->getPosition());
					sh->setActivated(loader.load("activated", false));
				}
			}
			else {
				sh = creationFunction(type);
				if (sh) sh->deserialise(file,loader);
			}

			if (sh) /// load from file all propertites of newly created element
			{
				el.push_back(unique_ptr<Base>(sh));
			}

		}
	}

}/// namespace