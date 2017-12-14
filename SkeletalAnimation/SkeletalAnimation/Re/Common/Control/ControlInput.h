/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#pragma once
#include <Re\Common\Control\ControlMultiKey.h>
#include <Re\Common\Control\ControlAxis.h>
#include <unordered_map>

namespace Control
{

	/// manages virtual input keys
	/// holds whole input settings in one place
	///
	/// there is declared global value
	/// 
	/// usage: declare a ptr to Multikey or Axis and assign it by
	/// multikeyPtr = Game::input.getKey(keyid);
	/// axisPtr = Game::input.getAxis(axisid);
	class InputController : public Res::ISerialisable
	{
	public:

		/// reset amortisation of key state
		/// call this on frame basis
		void update() const;

		Control::MultiKey* setKey(const string& code, Control::MultiKey* key)
		{
			keys[code] = std::unique_ptr<Control::MultiKey>(key);
			return key;
		}
		Control::MultiKey* getKey(const string& code)
		{
			return keys[code].get();
		}

		Control::Axis* setAxis(const string& code, Control::Axis* key)
		{
			axis[code] = std::unique_ptr<Control::Axis>(key);
			return key;
		}
		void setAxis(const string& code, const string& positiveKey, const string& negativeKey)
		{
			setAxis(code,
				new Control::AxisKey(
					getKey(positiveKey),
					getKey(negativeKey)
				)
			);
		}
		Control::Axis* getAxis(const string& code)
		{
			return axis[code].get();
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<Control::MultiKey> > keys;
		std::unordered_map<std::string, std::unique_ptr<Control::Axis> > axis;


	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

	extern InputController input;
}