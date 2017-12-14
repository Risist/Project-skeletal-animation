#pragma once
/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)


#include <Re\Common\Settings.h>
#include <iostream>

namespace Math
{

	class Angle;
	Angle Radian(float32 angle);
	Angle Degree(float32 angle);

	class Angle
	{
	protected:
		Angle(float32 initialDegree);
	public:
		Angle();

		/// most usefull angle constants
		static const Angle full;
		static const Angle zero;

		friend Angle Radian(float32 angle);
		friend Angle Degree(float32 angle);


		inline float32 asRadian() const
		{
			return (float32)(degree / 180.f * M_PI);
		}
		inline float32 asDegree() const
		{
			return degree;
		}

		inline float32 sin() const
		{
			return ::sin(asRadian());
		}
		inline float32 cos() const
		{
			return ::cos(asRadian());
		}


		inline Vector2f getVersor() const
		{
			return Vector2f(-sin(), cos());
		}

		Angle minimalDiffirence(const Angle& other) const;
		///
		Angle normalized() const
		{
			return Degree((float32)((int)degree % 360));
		}
		void normalize()
		{
			degree = (float32)((int)degree % 360);
		}

		inline bool operator>(const Angle& other) const
		{
			return degree > other.degree;
		}
		inline bool operator>=(const Angle& other) const
		{
			return degree >= other.degree;
		}
		inline bool operator<(const Angle& other) const
		{
			return degree < other.degree;
		}
		inline bool operator<=(const Angle& other) const
		{
			return degree <= other.degree;
		}

		inline Angle operator+(const Angle& other) const
		{
			return Degree(asDegree() + other.asDegree());
		}
		inline Angle operator-(const Angle& other) const
		{
			return Degree(asDegree() - other.asDegree());
		}
		inline Angle operator*(const Angle& other) const
		{
			return Degree(asDegree() * other.asDegree());
		}
		inline Angle operator/(const Angle& other) const
		{
			assert(other.degree != 0);
			return Degree(asDegree() / other.asDegree());
		}


		inline Angle operator*(float32 other) const
		{
			return Degree(asDegree() * other);
		}
		inline Angle operator/(float32 other) const
		{
			assert(other != 0);
			return Degree(asDegree() / other);
		}

		inline void operator+=(const Angle& other)
		{
			degree += other.asDegree();
		}
		inline void operator-=(const Angle& other)
		{
			degree -= other.asDegree();
		}
		inline void operator*=(const Angle& other)
		{
			degree *= other.asDegree();
		}
		inline void operator/=(const Angle& other)
		{
			assert(other.degree != 0);
			degree /= other.asDegree();
		}

		inline void operator*=(float32 other)
		{
			degree *= other;
		}
		inline void operator/=(float32 other)
		{
			assert(other != 0);
			degree /= other;
		}

		inline Angle operator-() const
		{
			return Degree(-degree);
		}

		inline bool operator==(Angle other) const
		{
			return degree == other.degree;
		}
		inline bool operator!=(Angle other) const
		{
			return degree != other.degree;
		}



		/// asserts whether the angle can be a divider
		void assertDivider() const { assert(degree != 0); }
	protected:
		// angle in degrees
		float32 degree;
	};

	Angle randRange(Angle min, Angle max);
	Angle clamp(Angle value, Angle min, Angle max);

	///////////////////////////////////////////////////////////////////////

	class PrecomputedAngle;
	PrecomputedAngle RadianP(float32 angle);
	PrecomputedAngle DegreeP(float32 angle);

	/// extended version of Angle
	/// Precomputed angle is bigger than Angle
	/// holds addictional data about values of sin and cos allowing to fast computation while angle doesn't change
	class PrecomputedAngle : public Angle
	{
	protected:
		PrecomputedAngle(float32 angle);
	public:
		PrecomputedAngle();
		/// creates Precomputed angle from normal angle
		PrecomputedAngle(const Angle& angle);

		/// most usefull angle constants
		static const PrecomputedAngle full;
		static const PrecomputedAngle zero;

		inline float32 sin() const
		{
			if (hasToBeUpdated)
				sinValue = ::sin(asRadian());
			return sinValue;
		}
		inline float32 cos() const
		{
			if (hasToBeUpdated)
				cosValue = ::cos(asRadian());
			return cosValue;
		}


		inline Vector2f getVersor() const
		{
			return Vector2f(-sin(), cos());
		}

		PrecomputedAngle minimalDiffirence(const Angle& other) const { return Angle::minimalDiffirence(other); }
		///
		PrecomputedAngle normalized() const
		{
			return DegreeP((float32)((int)degree % 360));
		}
		void normalize()
		{
			Angle::normalize();
			hasToBeUpdated = true;
		}

		inline PrecomputedAngle operator+(const Angle& other) const
		{
			return DegreeP(asDegree() + other.asDegree());
		}
		inline PrecomputedAngle operator-(const Angle& other) const
		{
			return DegreeP(asDegree() - other.asDegree());
		}
		inline PrecomputedAngle operator*(const Angle& other) const
		{
			return DegreeP(asDegree() * other.asDegree());
		}
		inline PrecomputedAngle operator/(const Angle& other) const
		{
			other.assertDivider();
			return DegreeP(asDegree() / other.asDegree());
		}

		////

		inline Angle operator*(float32 other) const
		{
			return DegreeP(asDegree() * other);
		}
		inline PrecomputedAngle operator/(float32 other) const
		{
			return DegreeP(asDegree() / other);
		}

		inline void operator+=(const Angle& other)
		{
			Angle::operator+=(other);
			hasToBeUpdated = true;
		}
		inline void operator-=(const Angle& other)
		{
			Angle::operator-=(other);
			hasToBeUpdated = true;
		}
		inline void operator*=(const Angle& other)
		{
			Angle::operator*=(other);
			hasToBeUpdated = true;
		}
		inline void operator/=(const Angle& other)
		{
			Angle::operator/=(other);
			hasToBeUpdated = true;
		}

		inline void operator*=(float32 other)
		{
			Angle::operator*=(other);
			hasToBeUpdated = true;
		}
		inline void operator/=(float32 other)
		{
			Angle::operator/=(other);
			hasToBeUpdated = true;
		}

		inline PrecomputedAngle operator-() const
		{
			return DegreeP(-degree);
		}

	private:
		mutable float32 sinValue{ 0 };
		mutable float32 cosValue{ 1 };
		int8 hasToBeUpdated : 1;

		friend PrecomputedAngle RadianP(float32 angle);
		friend PrecomputedAngle DegreeP(float32 angle);
	};

	PrecomputedAngle randRange(PrecomputedAngle min, PrecomputedAngle max);
	PrecomputedAngle clamp(PrecomputedAngle value, Angle min, PrecomputedAngle max);

}