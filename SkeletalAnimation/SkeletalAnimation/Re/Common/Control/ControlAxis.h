/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)
#pragma once
#include <Re\Common\Control\ControlMultiKey.h>

namespace Control
{
	/// WIP
	
	
	class Axis
	{
	public:
		virtual float32 getValue() const = 0;

	};

	/// axis created from values of two keys
	/// takes only values: 1, 0, -1
	class AxisKey : public Axis
	{
	public:
		AxisKey(MultiKey *_positiveKey = nullptr, MultiKey *_negativeKey = nullptr)
			: positiveKey(_positiveKey), negativeKey(_negativeKey)
		{
		}

		virtual float32 getValue() const override;

		void setPositiveKey(MultiKey* s)
		{
			positiveKey = s;
		}
		void setNegativeKey(MultiKey* s)
		{
			negativeKey = s;
		}

	private:
		MultiKey *positiveKey, *negativeKey;
	};

	/// axis created where the  
	/*class AxisMouse : public Axis
	{
		/// which axis
		enum
		{
			X,
			Y
		} mode;

		virtual float32 getValue() const override;

		
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};
	*/



}