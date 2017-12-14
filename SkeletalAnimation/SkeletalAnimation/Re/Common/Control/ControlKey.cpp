/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#include <Re\Common\Control\ControlKey.h>
extern RenderWindow wnd;

namespace Control
{
	
	Key::Key() : isPressed(false), wasAmortized(false)
	{
	}
	Key::Key(sf::Keyboard::Key key) : isPressed(false), wasAmortized(false)
	{
		setKeyCode(key);
	}
	Key::Key(sf::Mouse::Button button) : isPressed(false), wasAmortized(false)
	{
		setKeyCode(button);
	}
	Key::Key(sf::Keyboard::Key key, EPressState _desiredState) : isPressed(false), desiredState(_desiredState), wasAmortized(false)
	{
		setKeyCode(key);
	}
	Key::Key(sf::Mouse::Button button, EPressState _desiredState) : isPressed(false), desiredState(_desiredState), wasAmortized(false)
	{
		setKeyCode(button);
	}

	void Key::reset()
	{
		wasAmortized = false;
	}

	///////////////////////////////
	bool Key::isReady() const
	{
		if (wasAmortized)
			return amortizedResult;

		if (!wnd.hasFocus() )
			return false;

		uint8 lastStatePressed = isPressed;

		switch (device)
		{
		case EDevice::keyboard:
			isPressed = sf::Keyboard::isKeyPressed(getAsKeyboardKey());		
			break;
		case EDevice::mouse:
			isPressed = sf::Mouse::isButtonPressed(getAsMouseButton());		
			break;

		default:
			cerr << "Control::Key: invalid device type" << endl;	
			assert(false);
		}

		switch (desiredState)
		{
		case EPressState::pressedOnce:
			amortizedResult = !lastStatePressed && isPressed;
			break;
		case EPressState::hold:
			amortizedResult = isPressed;
			break;
		case EPressState::released:
			amortizedResult = lastStatePressed && !isPressed;
			break;
		default:
			break;
		}

		wasAmortized = true;
		return amortizedResult;
	}

	bool Key::isReadySimple() const
	{
		switch (device)
		{
		case EDevice::keyboard:
			return sf::Keyboard::isKeyPressed(getAsKeyboardKey());		
		case EDevice::mouse:
			return sf::Mouse::isButtonPressed(getAsMouseButton());		
			

		default:
			cerr << "Control::Key: invalid device type" << endl;	
			assert(false);
			return false;
		}
	}

	////////////////////////////////////
	void Key::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		string sDevice;
		string sCode ;
		string sState;

		/////////////////////
		if (device == EDevice::keyboard)
		{
			sDevice = "keyboard";
			sCode = fromCodeToString(getAsKeyboardKey());
		}
		else if(device == EDevice::mouse)
		{
			sDevice = "mouse";
			sCode = fromCodeToString(getAsMouseButton());
		}

		////////////////////////////
		if (desiredState == EPressState::pressedOnce)
		{
			sState = "pressedOnce";
		}
		else if (desiredState == EPressState::hold)
		{
			sState = "hold";
		}
		else if (desiredState == EPressState::released)
		{
			sState = "released";
		}


		saver.save<string>("device",sDevice, "keyboard");
		saver.save<string>("code", sCode, "Unknown");
		saver.save<string>("desiredState", sState, "pressedOnce");
	}

	void Key::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		string sDevice = loader.load<string>("device", "keyboard");
		string sCode = loader.load<string>("code", "Unknown");
		string sState = loader.load<string>("desiredState", "pressedOnce");

		if (sState == "pressedOnce")
		{
			desiredState = EPressState::pressedOnce;
		}
		else if (sState == "hold")
		{
			desiredState = EPressState::hold;
		}
		else if (sState == "released")
		{
			desiredState = EPressState::released;
		}
		else
		{
			cerr << "invalid key state = " << sState << endl;
			desiredState = EPressState::invalid;
		}

		if (sDevice == "keyboard")
		{
			device = EDevice::keyboard;
			keyCode = fromStringToCode_Keyboard(sCode.c_str());
		}
		else if (sDevice == "mouse")
		{
			device = EDevice::mouse;
			keyCode = fromStringToCode_Mouse(sCode.c_str());
		}
		else
		{
			cerr << "invalid key device = " << sDevice << endl;
			device = EDevice::invalid;
		}
	}

	/////////////////////////////////////
	const char * Key::fromCodeToString(sf::Keyboard::Key key)
	{
		
		switch (key)
		{
		case sf::Keyboard::A:
			return "A";
		case sf::Keyboard::B:
			return "B";
		case sf::Keyboard::C:
			return "C";
		case sf::Keyboard::D:
			return "D";
		case sf::Keyboard::E:
			return "E";
		case sf::Keyboard::F:
			return "F";
		case sf::Keyboard::G:
			return "G";
		case sf::Keyboard::H:
			return "H";
		case sf::Keyboard::I:
			return "I";
		case sf::Keyboard::J:
			return "J";
		case sf::Keyboard::K:
			return "K";
		case sf::Keyboard::L:
			return "L";
		case sf::Keyboard::M:
			return "M";
		case sf::Keyboard::N:
			return "N";
		case sf::Keyboard::O:
			return "O";
		case sf::Keyboard::P:
			return "P";
		case sf::Keyboard::Q:
			return "Q";
		case sf::Keyboard::R:
			return "R";
		case sf::Keyboard::S:
			return "S";
		case sf::Keyboard::T:
			return "T";
		case sf::Keyboard::U:
			return "U";
		case sf::Keyboard::V:
			return "V";
		case sf::Keyboard::W:
			return "W";
		case sf::Keyboard::X:
			return "X";
		case sf::Keyboard::Y:
			return "Y";
		case sf::Keyboard::Z:
			return "Z";
		case sf::Keyboard::Num0:
			return "Num0";
		case sf::Keyboard::Num1:
			return "Num1";
		case sf::Keyboard::Num2:
			return "Num2";
		case sf::Keyboard::Num3:
			return "Num3";
		case sf::Keyboard::Num4:
			return "Num4";
		case sf::Keyboard::Num5:
			return "Num5";
		case sf::Keyboard::Num6:
			return "Num6";
		case sf::Keyboard::Num7:
			return "Num7";
		case sf::Keyboard::Num8:
			return "Num8";
		case sf::Keyboard::Num9:
			return "Num9";
		case sf::Keyboard::Escape:
			return "Escape";
		case sf::Keyboard::LControl:
			return "Lcontrol";
		case sf::Keyboard::LShift:
			return "LShift";
		case sf::Keyboard::LAlt:
			return "LAlt";
		case sf::Keyboard::LSystem:
			return "LSystem";
		case sf::Keyboard::RControl:
			return "RControl";
		case sf::Keyboard::RShift:
			return "RShift";
		case sf::Keyboard::RAlt:
			return "RAlt";
		case sf::Keyboard::RSystem:
			return "RSystem";
		case sf::Keyboard::Menu:
			return "Menu";
		case sf::Keyboard::LBracket:
			return "LBracket";
		case sf::Keyboard::RBracket:
			return "RBracket";
		case sf::Keyboard::SemiColon:
			return "SemiColon";
		case sf::Keyboard::Comma:
			return "Coma";
		case sf::Keyboard::Period:
			return "Period";
		case sf::Keyboard::Quote:
			return "Quote";
		case sf::Keyboard::Slash:
			return "Slash";
		case sf::Keyboard::BackSlash:
			return "BackSlash";
		case sf::Keyboard::Tilde:
			return "Tilde";
		case sf::Keyboard::Equal:
			return "Equal";
		case sf::Keyboard::Dash:
			return "Dash";
		case sf::Keyboard::Space:
			return "Space";
		case sf::Keyboard::Return:
			return "Return";
		case sf::Keyboard::BackSpace:
			return "BackSpace";
		case sf::Keyboard::Tab:
			return "Tab";
		case sf::Keyboard::PageUp:
			return "PageUp";
		case sf::Keyboard::PageDown:
			return "PageDown";
		case sf::Keyboard::End:
			return "End";
		case sf::Keyboard::Home:
			return "Home";
		case sf::Keyboard::Insert:
			return "Insert";
		case sf::Keyboard::Delete:
			return "Delete";
		case sf::Keyboard::Add:
			return "Add";
		case sf::Keyboard::Subtract:
			return "Substract";
		case sf::Keyboard::Multiply:
			return "Multiply";
		case sf::Keyboard::Divide:
			return "Divide";
		case sf::Keyboard::Left:
			return "Left";
		case sf::Keyboard::Right:
			return "Right";
		case sf::Keyboard::Up:
			return "Up";
		case sf::Keyboard::Down:
			return "Down";
		case sf::Keyboard::Numpad0:
			return "Numpad0";
		case sf::Keyboard::Numpad1:
			return "Numpad1";
		case sf::Keyboard::Numpad2:
			return "Numpad2";
		case sf::Keyboard::Numpad3:
			return "Numpad3";
		case sf::Keyboard::Numpad4:
			return "Numpad4";
		case sf::Keyboard::Numpad5:
			return "Numpad5";
		case sf::Keyboard::Numpad6:
			return "Numpad6";
		case sf::Keyboard::Numpad7:
			return "Numpad7";
		case sf::Keyboard::Numpad8:
			return "Numpad8";
		case sf::Keyboard::Numpad9:
			return "Numpad9";
		case sf::Keyboard::F1:
			return "F1";
		case sf::Keyboard::F2:
			return "F2";
		case sf::Keyboard::F3:
			return "F3";
		case sf::Keyboard::F4:
			return "F4";
		case sf::Keyboard::F5:
			return "F5";
		case sf::Keyboard::F6:
			return "f6";
		case sf::Keyboard::F7:
			return "F7";
		case sf::Keyboard::F8:
			return "F8";
		case sf::Keyboard::F9:
			return "F9";
		case sf::Keyboard::F10:
			return "F10";
		case sf::Keyboard::F11:
			return "F11";
		case sf::Keyboard::F12:
			return "F12";
		case sf::Keyboard::F13:
			return "F13";
		case sf::Keyboard::F14:
			return "F14";
		case sf::Keyboard::F15:
			return "F15";
		case sf::Keyboard::Pause:
			return "Pause";
		default:
			return "Unknown";
		}
	}

	const char * Key::fromCodeToString(sf::Mouse::Button key)
	{
		switch (key)
		{
		case sf::Mouse::Left:
			return "MouseLeft";
		case sf::Mouse::Right:
			return "MouseRight";
		case sf::Mouse::Middle:
			return "MouseLeft";
		case sf::Mouse::XButton1:
			return "MouseXButton1";
		case sf::Mouse::XButton2:
			return "MouseXButton2";
		default:
			return "Unknown";
		}
	}

	sf::Keyboard::Key Key::fromStringToCode_Keyboard(const char * str)
	{

#	define KeyCheck(key) \
		if(str == #key)\
			return sf::Keyboard:: key;

		KeyCheck(A);
		KeyCheck(B);
		KeyCheck(C);
		KeyCheck(D);
		KeyCheck(E);
		KeyCheck(F);
		KeyCheck(G);
		KeyCheck(H);
		KeyCheck(I);
		KeyCheck(J);
		KeyCheck(K);
		KeyCheck(L);
		KeyCheck(M);
		KeyCheck(N);
		KeyCheck(O);
		KeyCheck(P);
		KeyCheck(Q);
		KeyCheck(R);
		KeyCheck(S);
		KeyCheck(T);
		KeyCheck(U);
		KeyCheck(V);
		KeyCheck(W);
		KeyCheck(X);
		KeyCheck(Y);
		KeyCheck(Z);
		KeyCheck(Num0);
		KeyCheck(Num1);
		KeyCheck(Num2);
		KeyCheck(Num3);
		KeyCheck(Num4);
		KeyCheck(Num5);
		KeyCheck(Num6);
		KeyCheck(Num7);
		KeyCheck(Num5);
		KeyCheck(Num9);
		KeyCheck(Escape);
		KeyCheck(LControl);
		KeyCheck(LAlt);
		KeyCheck(LSystem);
		KeyCheck(LShift);
		KeyCheck(RControl);
		KeyCheck(RAlt);
		KeyCheck(RSystem);
		KeyCheck(RShift);
		KeyCheck(Menu);
		KeyCheck(LBracket);
		KeyCheck(RBracket);
		KeyCheck(SemiColon);
		KeyCheck(Comma);
		KeyCheck(Period);
		KeyCheck(Quote);
		KeyCheck(Slash);
		KeyCheck(BackSlash);
		KeyCheck(Tilde);
		KeyCheck(Equal);
		KeyCheck(Dash);
		KeyCheck(Space);
		KeyCheck(Return);
		KeyCheck(BackSpace);
		KeyCheck(Tab);
		KeyCheck(PageUp);
		KeyCheck(PageDown);
		KeyCheck(End);
		KeyCheck(Home);
		KeyCheck(Insert);
		KeyCheck(Delete);
		KeyCheck(Add);
		KeyCheck(Subtract);
		KeyCheck(Multiply);
		KeyCheck(Divide);
		KeyCheck(Left);
		KeyCheck(Right);
		KeyCheck(Up);
		KeyCheck(Down);
		KeyCheck(Numpad0);
		KeyCheck(Numpad1);
		KeyCheck(Numpad2);
		KeyCheck(Numpad3);
		KeyCheck(Numpad4);
		KeyCheck(Numpad5);
		KeyCheck(Numpad6);
		KeyCheck(Numpad7);
		KeyCheck(Numpad5);
		KeyCheck(Numpad9);
		KeyCheck(F1);
		KeyCheck(F2);
		KeyCheck(F3);
		KeyCheck(F4);
		KeyCheck(F5);
		KeyCheck(F6);
		KeyCheck(F7);
		KeyCheck(F8);
		KeyCheck(F9);
		KeyCheck(F10);
		KeyCheck(F11);
		KeyCheck(F12);
		KeyCheck(F13);
		KeyCheck(F14);
		KeyCheck(F15);
		KeyCheck(Pause);

#	undef KeyCheck

		cerr << "Unknown key code: " << str << endl;
		return sf::Keyboard::Unknown;
	}

	sf::Mouse::Button Key::fromStringToCode_Mouse(const char * str)
	{

		if(str == "MouseLeft" )
			return sf::Mouse::Left;
		if (str == "MouseRight")
			return sf::Mouse::Left;
		if (str == "MouseLEftMiddle")
			return sf::Mouse::Left;
		if (str == "MouseXButton1")
			return sf::Mouse::Left;
		if (str == "MouseXButton2")
			return sf::Mouse::Left;

		cerr << "Unknown Mouse key code: " << str << endl;
		return sf::Mouse::Button::ButtonCount;
	}

	

}