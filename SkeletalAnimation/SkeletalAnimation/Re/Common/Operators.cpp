/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include <Re\Common\Operators.h>

Color operator+(const Color& c1, const Color& c2)
{
	return Color(
		c1.r + c2.r,
		c1.g + c2.g,
		c1.b + c2.b,
		c1.a + c2.a
		);
}
Color operator-(const Color& c1, const Color& c2)
{
	return Color(
		c1.r - c2.r,
		c1.g - c2.g,
		c1.b - c2.b,
		c1.a - c2.a
		);
}
Color operator*(const Color& c1, const Color& c2)
{
	return Color(
		c1.r * c2.r,
		c1.g * c2.g,
		c1.b * c2.b,
		c1.a * c2.a
		);
}
Color operator/(const Color& c1, const Color& c2)
{
	return Color(
		c1.r / c2.r,
		c1.g / c2.g,
		c1.b / c2.b,
		c1.a / c2.a
		);
}

Color operator+(const Color& c1, sf::Uint8 c2)
{
	return Color(
		c1.r + c2,
		c1.g + c2,
		c1.b + c2,
		c1.a + c2
		);
}
Color operator-(const Color& c1, sf::Uint8 c2)
{
	return Color(
		c1.r - c2,
		c1.g - c2,
		c1.b - c2,
		c1.a - c2
		);
}
Color operator*(const Color& c1, sf::Uint8 c2)
{
	return Color(
		c1.r * c2,
		c1.g * c2,
		c1.b * c2,
		c1.a * c2
		);
}
Color operator/(const Color& c1, sf::Uint8 c2)
{
	return Color(
		c1.r / c2,
		c1.g / c2,
		c1.b / c2,
		c1.a / c2
		);
}

void operator+=(Color& c1, const Color& c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	c1.a += c2.a;
}
void operator-=(Color& c1, const Color& c2)
{
	c1.r -= c2.r;
	c1.g -= c2.g;
	c1.b -= c2.b;
	c1.a -= c2.a;
}
void operator*=(Color& c1, const Color& c2)
{
	c1.r *= c2.r;
	c1.g *= c2.g;
	c1.b *= c2.b;
	c1.a *= c2.a;
}
void operator/=(Color& c1, const Color& c2)
{
	c1.r /= c2.r;
	c1.g /= c2.g;
	c1.b /= c2.b;
	c1.a /= c2.a;
}

/// Color_f


Color_f operator+(const Color_f& c1, const Color_f& c2)
{
	return Color_f(
		c1.r + c2.r,
		c1.g + c2.g,
		c1.b + c2.b,
		c1.a + c2.a
	);
}
Color_f operator-(const Color_f& c1, const Color_f& c2)
{
	return Color_f(
		c1.r - c2.r,
		c1.g - c2.g,
		c1.b - c2.b,
		c1.a - c2.a
	);
}
Color_f operator*(const Color_f& c1, const Color_f& c2)
{
	return Color_f(
		c1.r * c2.r,
		c1.g * c2.g,
		c1.b * c2.b,
		c1.a * c2.a
	);
}
Color_f operator/(const Color_f& c1, const Color_f& c2)
{
	return Color_f(
		c1.r / c2.r,
		c1.g / c2.g,
		c1.b / c2.b,
		c1.a / c2.a
	);
}
void operator+=(Color_f& c1, const Color_f& c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	c1.a += c2.a;
}
void operator-=(Color_f& c1, const Color_f& c2)
{
	c1.r -= c2.r;
	c1.g -= c2.g;
	c1.b -= c2.b;
	c1.a -= c2.a;
}
void operator*=(Color_f& c1, const Color_f& c2)
{
	c1.r *= c2.r;
	c1.g *= c2.g;
	c1.b *= c2.b;
	c1.a *= c2.a;
}
void operator/=(Color_f& c1, const Color_f& c2)
{
	c1.r /= c2.r;
	c1.g /= c2.g;
	c1.b /= c2.b;
	c1.a /= c2.a;
}

Color_f operator*(const Color_f & c1, float32 c2)
{
	return Color_f(
		c1.r * c2,
		c1.g * c2,
		c1.b * c2,
		c1.a * c2
	);
}

Color_f operator/(const Color_f & c1, float32 c2)
{
	assert(c2);
	return Color_f(
		c1.r / c2,
		c1.g / c2,
		c1.b / c2,
		c1.a / c2
	);
}

void operator*=(Color_f & c1, float32 c2)
{
	c1.r *= c2;
	c1.g *= c2;
	c1.b *= c2;
	c1.a *= c2;
}

void operator/=(Color_f & c1, float32 c2)
{
	assert(c2);
	c1.r /= c2;
	c1.g /= c2;
	c1.b /= c2;
	c1.a /= c2;
}
