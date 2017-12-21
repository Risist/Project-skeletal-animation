#pragma once
#include <Re\Common\utility.h>

namespace Graphics
{

	/*
	*	class holding all animatable propertites of model 
	*	like color, pos, rotation, scale ect.
	*/
	class ModelDef : public Res::ISerialisable
	{
	public: /// functions section

			/// ctors
		ModelDef(const Vector2D& position = Vector2D(), Angle rot = Angle::zero,
			Color_f color = Color_f(),
			const Vector2D& scale = Vector2D(), Angle rotAround = Angle::zero);
		ModelDef(std::istream& file, Res::DataScriptLoader& loader) { deserialise(file, loader); }

	public: /// Data section

		Vector2D position;
		Vector2D scale{ Vector2D(1,1) };
		/// model color, clamped at range [0,255]
		Color_f color;
		/// rotation of sprite and its childs
		Angle rotation,
			/// rotation of sprite only
			mineRotation;

	public: /// operators section
		ModelDef operator+(const ModelDef& other) const;
		ModelDef operator-(const ModelDef& other) const;
		ModelDef operator*(float32 other) const;
		ModelDef operator/(float32 other) const;

		void operator+=(const ModelDef& other);
		void operator-=(const ModelDef& other);
		void operator*=(float32 other);
		void operator/=(float32 other);

	protected: /// ISerialisable section
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;

	public: /// predefined values section

			/// default ModelDef, not changing sprite at update; to use in Model class
		static const ModelDef default;
		/// ModelDef with all values equal to 0; to use in animation class
		static const ModelDef zero;
	};

}