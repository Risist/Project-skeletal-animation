#pragma once
/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)


#include <Re\Common\Math\Angle.h>
#include <Re\Common\Math\Vector2D.h>
#include <Re\Common\Math\NewtonianResource.h>
#include <Re\Common\Math\Transform.h>

using namespace Math;

namespace Math
{

	template <typename Ty>
	inline Ty min(Ty x, Ty y)
	{
		return x > y ? y : x;
	}

	template <typename Ty>
	inline Ty max(Ty x, Ty y)
	{
		return x > y ? x : y;
	}

	template< class Type>
	inline Type clamp(Type value, Type min, Type max)
	{
		if (value > max)
			return max;
		else if (value < min)
			return min;
		return value;
	}

	inline Vector2D max(const Vector2D& v1, const Vector2D& v2);
	inline Vector2D min(const Vector2D& v1, const Vector2D& v2);

	inline float32 randRange(float32 min, float32 max)
	{
		return (float)rand() / RAND_MAX * (max - min) + min;
	}
	inline sf::Time randRange(sf::Time min, sf::Time max)
	{
		return (float)rand() / RAND_MAX * (max - min) + min;
	}

	template<typename Ty, typename AlphaTy >
	inline Ty lerp(Ty x1, Ty x2, AlphaTy t)
	{
		return x1 + (x2 - x1)*t;
	}

	template<typename Ty = Angle, typename AlphaTy >
	inline Angle lerp(Angle x1, Angle x2, AlphaTy t)
	{
		return x1 + x2.minimalDiffirence(x1)*t;
	}


	template<typename Ty>
	inline Ty smoothstepHermite(Ty x, Ty edge0 = 0, Ty edge1 = 1)
	{
		x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);

		return x*X*(3 - 2 * x);
	}

	template<typename Ty>
	inline Ty smoothstepPerlin(Ty x, Ty edge0 = 0, Ty edge1 = 1)
	{
		// Scale, and clamp x to 0..1 range
		x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
		// Evaluate polynomial
		return x*x*x*(x*(x * 6 - 15) + 10);
	}

	template<typename Ty>
	inline Ty smoothstepMcDonald(Ty x, Ty edge0 = 0, Ty edge1 = 1)
	{
		// Scale, and clamp x to 0..1 range
		x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
		// Evaluate polynomial
		return  x*x*x*x*(x*(x* (x* -20 + 70) - 84) + 35);
	}
}