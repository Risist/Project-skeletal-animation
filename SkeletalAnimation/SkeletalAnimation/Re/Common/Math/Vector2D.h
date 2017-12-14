#pragma once
#include <Re\Common\Settings.h>
#include <Re\Common\Math\Angle.h>
/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)



namespace Math
{

	class Vector2D
	{
	public:
		// -------------------------- default constructor, does nothing (for performance)
		// Or maybe not. There is so lack of intuitivlity. It will led to so many bugs
		Vector2D() : x(0), y(0) {};
		// constructor with two floats
		Vector2D(float32 _x, float32 _y) : x(_x), y(_y) {}

		/// auto conversion:

		/// TODO : sfml // include vector file
		template<typename Ty> Vector2D(const sf::Vector2<Ty>& other) : x((float32)other.x), y((float32)other.y) {}
		template<typename Ty> operator sf::Vector2<Ty>() { return sf::Vector2<Ty>((Ty)x, (Ty)y); }
		template<typename Ty> operator const sf::Vector2<Ty>() const { return sf::Vector2<Ty>((Ty)x, (Ty)y); }


		// sets x and y to zero
		void setZero()
		{
			x = 0;
			y = 0;
		}
		// returns true if x and y are zero
		// for float type checking for simple == Vector2D() cant work
		// because it is only approximation to noumber
		bool isZero() const
		{
			return x*x + y*y < std::numeric_limits<float>::min();
		}

		// returns the lenght of the vector
		inline float getLenght() const
		{
			return sqrtf(x*x + y*y);
		}
		// returns the aquered length of the vector
		// squared version, faster to compute
		// try to use wether it is possible
		inline float getLenghtSq() const
		{
			return x*x + y*y;
		}
		// change the lenght of the vector to 1
		void normalise()
		{
			float vector_lenght = getLenght();
			if (vector_lenght > std::numeric_limits<float>::epsilon())
			{
				x /= vector_lenght;
				y /= vector_lenght;
			}
		}
		// returns a vector which lenght is equal to 1
		// does nothing if isZero() returns true
		Vector2D getNormalised() const
		{
			float vector_lenght = getLenght();
			if (vector_lenght > std::numeric_limits<float>::epsilon())
				return Vector2D(x / vector_lenght, y / vector_lenght);
			else
				return *this;
		}


		// the dot product of this and taken as a parametr vectors
		inline float32 dot(const Vector2D& other) const
		{
			return x*other.x + y*other.y;
		}
		// returns 2d cross product
		inline float32 cross(const Vector2D& other) const
		{
			return x * other.y - other.x * y;
		}
		// returns perpendicular vector
		inline Vector2D perp() const
		{
			return Vector2D(-y, x);
		}

		// returns angle which this vector is directed to
		Angle angle() const;

		inline void rotate(const Angle& angle)
		{
			Vector2D v = (*this);
			x = (v.x)*angle.cos() - (v.y)*angle.sin();
			y = (v.x)*angle.sin() + (v.y)*angle.cos();
		}
		inline void rotate()
		{
			rotate(randRange(PrecomputedAngle::zero, PrecomputedAngle::full));
		}
		inline void rotate(const Angle& angle, const Vector2D& center)
		{
			Vector2D v = (*this);
			x = center.x + (v.x - center.x)*angle.cos() - (v.y - center.y)*angle.sin();
			y = center.y + (v.x - center.y)*angle.sin() + (v.y - center.y)*angle.cos();
		}
		inline Vector2D getRotated(const Angle& angle) const
		{
			float _x = (x)*angle.cos() - (y)*angle.sin();
			float _y = (x)*angle.sin() + (y)*angle.cos();
			return Vector2D(_x, _y);
		}
		inline Vector2D getRotated(const Angle& angle, const Vector2D& center) const
		{
			float _x = center.x + (x - center.x)*angle.cos() - (y - center.y)*angle.sin();
			float _y = center.y + (x - center.y)*angle.sin() + (y - center.y)*angle.cos();
			return Vector2D(_x, _y);
		}


		inline void rotate(const PrecomputedAngle& angle)
		{
			Vector2D v = (*this);
			x = (v.x)*angle.cos() - (v.y)*angle.sin();
			y = (v.x)*angle.sin() + (v.y)*angle.cos();
		}
		inline void rotate(const PrecomputedAngle& angle, const Vector2D& center)
		{
			Vector2D v = (*this);
			x = center.x + (v.x - center.x)*angle.cos() - (v.y - center.y)*angle.sin();
			y = center.y + (v.x - center.y)*angle.sin() + (v.y - center.y)*angle.cos();
		}
		inline Vector2D getRotated(const PrecomputedAngle& angle) const
		{
			float _x = (x)*angle.cos() - (y)*angle.sin();
			float _y = (x)*angle.sin() + (y)*angle.cos();
			return Vector2D(_x, _y);
		}
		inline Vector2D getRotated(const PrecomputedAngle& angle, const Vector2D& center) const
		{
			float _x = center.x + (x - center.x)*angle.cos() - (y - center.y)*angle.sin();
			float _y = center.y + (x - center.y)*angle.sin() + (y - center.y)*angle.cos();
			return Vector2D(_x, _y);
		}

		inline Vector2D getRotated() const
		{
			return getRotated(randRange(PrecomputedAngle::zero, PrecomputedAngle::full));
		}



		// operators for more intuitive use

		Vector2D operator-() const
		{
			return (*this) * -1;
		}

		void operator=(const Vector2D& other)
		{
			x = other.x;
			y = other.y;
		}
		void operator+=(const Vector2D& other)
		{
			x += other.x;
			y += other.y;
		}
		void operator-=(const Vector2D& other)
		{
			x -= other.x;
			y -= other.y;
		}
		void operator*=(const Vector2D& other)
		{
			x *= other.x;
			y *= other.y;
		}
		void operator/=(const Vector2D& other)
		{
			x /= other.x;
			y /= other.y;
		}

		void operator*=(float32 other)
		{
			x *= other;
			y *= other;
		}
		void operator/=(float32 other)
		{
			x /= other;
			y /= other;
		}


		Vector2D operator+(const Vector2D& other) const
		{
			return Vector2D(x + other.x, y + other.y);
		}
		Vector2D operator-(const Vector2D& other) const
		{
			return Vector2D(x - other.x, y - other.y);
		}
		Vector2D operator*(const Vector2D& other) const
		{
			return Vector2D(x * other.x, y * other.y);
		}
		Vector2D operator/(const Vector2D& other) const
		{
			return Vector2D(x / other.x, y / other.y);
		}

		Vector2D operator*(float32 other) const
		{
			return Vector2D(x * other, y * other);
		}
		Vector2D operator/(float32 other) const
		{
			return Vector2D(x / other, y / other);
		}

		bool operator==(const Vector2D& other) const
		{
			return x == other.x && y == other.y;
		}
		bool operator!=(const Vector2D& other) const
		{
			return x != other.x || y != other.y;
		}


		float32 x, y;
	};

	Vector2D randRange(const Vector2D& min, const Vector2D& max);
	Vector2D clamp(const Vector2D& value, const Vector2D& min, const Vector2D& max);
}