/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#pragma once
#include <Re\Common\Settings.h>
#include <Re\Common\Scripts\ResScripts.h>

namespace Control
{

	/// class which unify pressing keys for mouse, keyboard, joysticks ect
	/// supports serialisation
	class Key : public Res::ISerialisable
	{
	public:
		/// invalid key constructor, will never be ready
		Key();
		/// constructor of keyboard key
		Key(sf::Keyboard::Key key);
		/// constructor of mouse button
		Key(sf::Mouse::Button button);
		/// constructor of joystick key
		///explicit Key(uint8 joystickId, uint8 joystickKeyId);


		/// when the key is ready: 
		enum class EPressState : int8
		{
			pressedOnce, /// only once the key is pressed, waits until released for next
			hold,		 /// everytime the key is down
			released,	 /// once the key stopped to be holded
			invalid		 /// invalid state
		};
		/// what hardware device is the Key object on control
		enum class EDevice : int8
		{
			keyboard,	 /// keyboard key
			mouse,		 /// mouse button
			///joystick, /// not yet supported /// joystick key
			invalid		 /// not supported device
		};

		/// constructor of keyboard key and 
		Key(sf::Keyboard::Key key, EPressState _desiredState);
		/// constructor of mouse button
		Key(sf::Mouse::Button button, EPressState _desiredState);

		/// resets amortisation key state
		/// should be called every frame
		void reset();
		/// key check with amortisation
		/// if the same Control::Key is used in many places result is computed only once. 
		/// but you should call reset before every frame.
		/// @return if the key represented by the class is in required state
		bool isReady() const;
		/// tells whether key was pressed - without lookong on desired state
		bool isReadySimple() const;

		EPressState desiredState{EPressState::hold};

		/////////////

		void setKeyCode(sf::Keyboard::Key key)
		{
			keyCode = key;
			device = EDevice::keyboard;
		}
		void setKeyCode(sf::Mouse::Button key)
		{
			keyCode = key;
			device = EDevice::mouse;
		}
		/// not supported yet
		///void setKeyCode(uint8 joystickId, uint8 keyCode){}

		sf::Keyboard::Key getAsKeyboardKey() const
		{
			return (sf::Keyboard::Key)keyCode;
		}
		sf::Mouse::Button getAsMouseButton() const
		{
			return (sf::Mouse::Button)keyCode;
		}

	private:
		/// possible keys/device data:
		uint16 keyCode = -1;

		/// not yet supported
		// uint8 joistickId : 3;
		// uint8 joistickKeyId : 5;

		EDevice device = EDevice::invalid;

		mutable uint8 isPressed : 1;
		
		/// amortisation allows to reduce computations needed to gain key press state
		/// in case of using the same key in multiplay places this allows to compute key state only once
		mutable uint8 wasAmortized :  1;
		mutable uint8 amortizedResult : 1;
		
		/// serialisation helper functions
		static const char* fromCodeToString(sf::Keyboard::Key key);
		static const char* fromCodeToString(sf::Mouse::Button key);

		static sf::Keyboard::Key fromStringToCode_Keyboard(const char* str);
		static sf::Mouse::Button fromStringToCode_Mouse(const char* str);

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};
}