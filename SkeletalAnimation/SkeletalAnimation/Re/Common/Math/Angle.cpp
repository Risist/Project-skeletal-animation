#include <Re\Common\Math\Angle.h>
#include <Re\Common\Math\Math.h>
/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)


namespace Math
{
	const Angle Angle::full = Degree(360);
	const Angle Angle::zero = Degree(0);

	Angle::Angle()
		: degree(0)
	{
	}
	Angle::Angle(float32 initialAngle)
		: degree(initialAngle)
	{
	}

	Angle Radian(float32 angle)
	{
		Angle a;
		a.degree = angle*180.f / (float32)M_PI;
		return a;
	}

	Angle Degree(float32 angle)
	{
		Angle a;
		a.degree = angle;
		return a;
	}

	Angle Angle::minimalDiffirence(const Angle & other) const
	{

		float32 diffirence = degree - other.degree;

		// remainder after division
		diffirence += -((int)(diffirence / 360)) * 360;

		if (diffirence > 180) diffirence -= 360;

		else if (diffirence < -180) diffirence += 360;

		/*debug*
		cout << "myAngle " << myAngle << "\n";
		cout << "forceAngle " << forceAngle << "\n";
		cout << "diffirence " << diffirence << "\n";
		/**/

		return Degree(diffirence);
	}

	Angle randRange(Angle min, Angle max)
	{
		return Degree(randRange(min.asDegree(), max.asDegree()));
	}

	Angle clamp(Angle value, Angle min, Angle max)
	{
		return Degree(clamp(value.asDegree(), min.asDegree(), max.asDegree()));
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////


	const PrecomputedAngle PrecomputedAngle::full = DegreeP(360);
	const PrecomputedAngle PrecomputedAngle::zero = DegreeP(0);


	PrecomputedAngle RadianP(float32 angle)
	{
		return PrecomputedAngle(angle*180.f / (float32)M_PI);
	}

	PrecomputedAngle DegreeP(float32 angle)
	{
		return PrecomputedAngle(angle);
	}


	PrecomputedAngle::PrecomputedAngle(float32 angle)
		: hasToBeUpdated(true), Angle(angle)
	{
	}

	PrecomputedAngle::PrecomputedAngle()
		: hasToBeUpdated(false), Angle(Angle::zero), sinValue(0), cosValue(1)
	{
	}

	PrecomputedAngle::PrecomputedAngle(const Angle & angle)
		: Angle(angle.asDegree()), hasToBeUpdated(true)
	{
	}


	PrecomputedAngle randRange(PrecomputedAngle min, PrecomputedAngle max)
	{
		return DegreeP(randRange(min.asDegree(), max.asDegree()));
	}

	PrecomputedAngle clamp(PrecomputedAngle value, Angle min, PrecomputedAngle max)
	{
		return DegreeP(clamp(value.asDegree(), min.asDegree(), max.asDegree()));
	}

}