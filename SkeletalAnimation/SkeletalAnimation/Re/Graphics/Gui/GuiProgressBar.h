/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#pragma once
#include <Re\Graphics\Gui\GuiButton.h>

namespace Gui
{
	class ProgressBar : public Base
	{
		SERIALISATION_NAME(ProgressBar)
	public:
		ProgressBar();


		////// events

		virtual void onUpdate(RenderTarget& wnd, RenderStates states) override;
		
		////// setters
		ProgressBar* setStateBackground(Color color = Color::White, ResId tsId = 0)
		{
			background.cl = color;
			background.setTexture(tsId);
			return this;
		}
		ProgressBar* setStateForeground(Color color = Color::White, ResId tsId = 0)
		{
			foreground.cl = color;
			foreground.setTexture(tsId);
			return this;
		}
		ProgressBar* setProgress(float32 s)
		{
			progress = clamp(s, 0.f, 1.f);
			return this;
		}
		ProgressBar* setDirectionMode(function<void(sf::ConvexShape&, Gui::ProgressBar*)> s)
		{
			directionMode = s;
			return this;
		}

		REDEFINE_SETTER_1(ProgressBar, setPosition, const Vector2f&);
		REDEFINE_SETTER_1(ProgressBar, setActivated, bool);
		REDEFINE_SETTER_1(ProgressBar, setWh, const Vector2D&);

		
		////// getters
		float32 getProgres() const { return progress; }
		State getForeground() const { return foreground; }
		State getBackground() const { return background; }


		////// directionModes
		static void directionXLeft(sf::ConvexShape& sh, Gui::ProgressBar* pb);
		static void directionXMiddle(sf::ConvexShape& sh, Gui::ProgressBar* pb);
		static void directionXRight(sf::ConvexShape& sh, Gui::ProgressBar* pb);

		static void directionYUp(sf::ConvexShape& sh, Gui::ProgressBar* pb);
		static void directionYMiddle(sf::ConvexShape& sh, Gui::ProgressBar* pb);
		static void directionYDown(sf::ConvexShape& sh, Gui::ProgressBar* pb);
	private:
		
		/// Color & texture of 
		State background; ///< back rectangle
		State foreground; ///< forward rectangle (showing progress)

		/// actual progress of the bar. In range of[0,1] inclusive
		float32 progress;
	
		function<void(sf::ConvexShape&, Gui::ProgressBar*)> directionMode{directionXRight};
	protected:
		/// Graphical propertites saved in files 
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};



}

