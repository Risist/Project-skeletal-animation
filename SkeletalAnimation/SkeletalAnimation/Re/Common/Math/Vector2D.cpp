#include <Re\Common\Math\Vector2D.h>
#include <Re\Common\Math\Math.h>
/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)


namespace Math
{
	Angle Vector2D::angle() const
	{
		return Radian(atan2(y, x)) + Degree(90);
	}

	Vector2D randRange(const Vector2D & min, const Vector2D & max)
	{
		return Vector2D(randRange(min.x, max.x), randRange(min.y, max.y));
	}

	Vector2D clamp(const Vector2D & value, const Vector2D & min, const Vector2D & max)
	{
		return Vector2D(clamp(value.x, min.x, max.x), clamp(value.y, min.y, max.y));
	}

}