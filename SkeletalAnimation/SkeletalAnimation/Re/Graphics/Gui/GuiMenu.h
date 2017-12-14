/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#pragma once
#include <Re\Graphics\Gui\GuiBase.h>


namespace Gui
{
	/// Gui class used to connect and treat many gui elements as one
	class Menu : public Base
	{
		SERIALISATION_NAME(Menu)
	public:
		Menu(const Vector2f& pos = Vector2f());

		////// creation
		template<class T>
		T* add(bool active = true);

		/// creates gui element from file
		template<class T>
		T* add(const char * path, bool active = true);


		void remove(size_t id);
		void remove(Gui::Base *ptr);

		/// remove all menu elements
		void clear();


	public: ////// events
		virtual void onUpdate(RenderTarget& wnd, RenderStates states) override;
		virtual void onSetActivated(bool s) override;


	public:		
		////// setters

		REDEFINE_SETTER_1(Menu, setPosition, const Vector2f&);
		REDEFINE_SETTER_1(Menu, setWh, const Vector2f&);
		REDEFINE_SETTER_1(Menu, setActivated, bool);

		////// getters

		/// how many gui elements are contained?
		size_t getSize() { return el.size(); }
		Base* operator[](size_t id) {	return el[id].get(); }

	protected:
		/// vector of contained elements
		vector<unique_ptr<Base>> el;

	protected:
		/// deserialise one element from another file
		Base* desetializeInclude(Res::DataScriptLoader& loader);
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};


	template<class T>
	T* Menu::add(bool active)
	{
		el.push_back(unique_ptr<Base>(new T));
		el.back()->setActivated(active);
		return (T*)el.back().get();
	}

	template<class T>
	T* Menu::add(const char* path, bool active)
	{
		el.push_back(unique_ptr<Base>(new T));
		el.back()->deserialise(path);
		el.back()->setActivated(active);
		return (T*)el.back().get();
	}
}