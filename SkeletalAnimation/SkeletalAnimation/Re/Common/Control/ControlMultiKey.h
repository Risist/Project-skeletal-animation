/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#pragma once
#include <Re\Common\Control\ControlKey.h>

namespace Control
{

	/// Control::Key supports checking for key press a singular key
	/// But in case if you want player to set up some alternative keys use the class
	class MultiKey : public Res::ISerialisable
	{
	public:
		MultiKey() {}
		MultiKey(sf::Keyboard::Key code)
		{
			addKey(Key(code));
		}
		MultiKey(sf::Keyboard::Key code, Key::EPressState state)
		{
			addKey(Key(code, state));
		}

		MultiKey(sf::Mouse::Button code)
		{
			addKey(Key(code));
		}
		MultiKey(sf::Mouse::Button code, Key::EPressState state)
		{
			addKey(Key(code, state));
		}

		void reset();

		bool isReady() const;
		bool isReadySimple() const;

		/// adds new key activating this multikey
		MultiKey* addKey( const Control::Key& s)
		{
			keys.push_back(s);
			return this;
		}
	private:
		vector<Control::Key> keys;
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};


}