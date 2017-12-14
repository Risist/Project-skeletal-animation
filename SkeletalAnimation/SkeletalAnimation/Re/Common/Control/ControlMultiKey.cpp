/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include <Re\Common\Control\ControlMultiKey.h>

namespace Control
{
	void MultiKey::reset()
	{
		for (auto&it : keys)
			it.reset();
	}
	bool MultiKey::isReady() const
	{
		for (auto&it : keys)
			if (it.isReady())
				return true;
		return false;
	}

	bool MultiKey::isReadySimple() const
	{
		for (auto&it : keys)
			if (it.isReadySimple())
				return true;
		return false;
	}

	void MultiKey::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.nextLine(file);
		auto it = keys.begin();
		do
		{
			it->serialise(file, saver);
		}
		DATA_SCRIPT_MULTILINE_SAVE(file, saver, it != keys.end())
	}

	void MultiKey::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		DATA_SCRIPT_MULTILINE(file, loader)
		{
			Control::Key key;
			key.deserialise(file, loader);
			addKey(key);
		}
	}

}