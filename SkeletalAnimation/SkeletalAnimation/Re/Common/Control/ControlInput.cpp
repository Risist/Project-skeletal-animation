/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include <Re\Common\Control\ControlInput.h>

namespace Control
{
	InputController input;

	void InputController::update() const
	{
		for (auto it = keys.begin(); it != keys.end(); ++it)
			it->second->reset();
	}

	void InputController::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.nextLine(file);

		auto it = keys.begin();
		do
		{
			saver.save<std::string>("keyName", it->first);
			it->second->serialise(file, saver);

			++it;
		}
		DATA_SCRIPT_MULTILINE_SAVE(file, saver, it != keys.end());
	}
	void InputController::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		DATA_SCRIPT_MULTILINE(file, loader)
		{
			Control::MultiKey * newKey = new Control::MultiKey();
			newKey->deserialise(file, loader);
			std::string code = loader.load<string>("keyName", "invalid");
			if (code != "invalid")
			{
				setKey(code, newKey);
			}
			else
				cerr << "InputController: wrong key code" << endl;
		}
	}
}