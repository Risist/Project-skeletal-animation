/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#pragma once
#include <Re\Graphics\Gui\GuiBase.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	class Text : public Base
	{
		SERIALISATION_NAME(Text)
	public:
		Text();
		
		////// events

		virtual void onUpdate(RenderTarget& target, RenderStates states) override;

		////// setters
		template<class T>
		Text* setStr(T s)
		{
			(*this) << s;
			return this;
		}
		Text* setPosition(const Vector2f& pos)
		{
			Base::setPosition(pos);
			return this;
		}
		Text* setActivated(bool s)
		{
			Base::setActivated(s);
			return this;
		}
		Text* setColor(Color color)
		{
			txt.setFillColor(color);
			return this;
		}
		Text* setSize(unsigned int s)
		{
			txt.setCharacterSize(s);
			return this;
		}
		Text* setOutlineColor(Color color)
		{
			txt.setOutlineColor(color);
			return this;
		}
		Text* setOutlineThickness(float s)
		{
			txt.setOutlineThickness(s);
			return this;
		}
		Text* setStyle(sf::Uint32 style)
		{
			txt.setStyle(style);
			return this;
		}
		Text* setFont(ResId fontId)
		{
			txt.setFont(fontInst[fontId]);
			return this;
		}
		Text* setRotation(Angle s)
		{
			txt.setRotation(s.asDegree());
			return this;
		}



		/// stream
		template<typename T>
		Text& operator<<(T s)
		{
			std::ostringstream stream;
			stream << s;
			str += stream.str();

			return *this;
		}
		Text& operator<<(const std::string& s)
		{
			str += s;
			return *this;
		}
		Text& operator<<(const char* s)
		{
			str += s;
			return *this;
		}


		Text& clear()
		{
			str = "";
			return *this;
		}

		/// returns sfml text class
		const sf::Text& getText() const
		{
			return txt;
		}
		/// returns actually contined text
		const string& getString() const
		{
			return str;
		}

	private:

		// graphical representation of text
		sf::Text txt;
		// what is to write
		string str;

	protected:
		using Base::setWh;
		
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}