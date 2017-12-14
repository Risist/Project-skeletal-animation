#pragma once
/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include <Re\Common\utility.h>

namespace Gui
{
	/// Base gui fragment class
	/// Prepared for serialisation/deserialisation or manual setting
	class Base : public Res::ISerialisable
	{
	public:
		MULTI_SERIALISATION_INTERFACE(Base);
	public:
		Base(const Vector2f& pos = Vector2f());
		virtual ~Base() = default;

	public:
		////// events

		// display and update gui element
		virtual void onUpdate(RenderTarget& wnd, RenderStates states) = 0;
		/// event called on atempt to change activation state
		virtual void onSetActivated(bool s) {}
		

		
		////// setters

		// set pos relative to pos of element connected to
		void updateActualPosition(const Vector2f parentActualPosition = Vector2f())
		{
			actualPosition = Base::position + parentActualPosition;
		}


		Base* setPosition(const sf::Vector2f& _new)
		{
			position = _new;
			return this;
		}		
		Base* setActivated(bool s)
		{
			activated = s;
			onSetActivated(s);
			return this;
		}
		Base* setWh( const Vector2f& wh)
		{
			halfWh = { wh.x*0.5f, wh.y * 0.5f };
			return this;
		}


		////// getters

		bool isActivated() const
		{
			return activated;
		}
		Vector2f getActualPosition() const
		{
			return actualPosition;
		}
		Vector2f getPosition() const
		{
			return position;
		}
		Vector2f getWh() const
		{
			return { halfWh.x*2.f, halfWh.y*2.f };
		}


	protected:

		/// which area the object holds
		Vector2f halfWh;

		/// offset of pos relative to parent transform
		Vector2f position;

		// actual pos of gui element
		Vector2f actualPosition;

		/// hidden gui object is not updated nor drawn onto the screan
		bool activated;

	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	
	
		friend class Menu;
	};
}