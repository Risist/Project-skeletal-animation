#pragma once
/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include <Re\Common\Settings.h>

/// addictional operators that would be usefull but sfml didn't defined


/// Color operators

/// color struct which contains floats instead Uints
class Color_f
{
public:
	Color_f(float32 _clR=0, float32 _clG=0, float32 _clB=0, float32 _clA=0)
		:r(_clR), g(_clG), b(_clB), a(_clA){}

	/// color data [0, 255]
	/// holded that way because of animations 
	float32 r, g, b, a;
};


Color operator+(const Color& c1, const Color& c2);
Color operator-(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const Color& c2);
Color operator/(const Color& c1, const Color& c2);

Color operator*(const Color& c1, sf::Uint8 c2);
Color operator/(const Color& c1, sf::Uint8 c2);

void operator+=(Color& c1, const Color& c2);
void operator-=(Color& c1, const Color& c2);
void operator*=(Color& c1, const Color& c2);
void operator/=(Color& c1, const Color& c2);

void operator*=(Color& c1, sf::Uint8 c2);
void operator/=(Color& c1, sf::Uint8 c2);

/// Color_f
Color_f operator+(const Color_f& c1, const Color_f& c2);
Color_f operator-(const Color_f& c1, const Color_f& c2);
Color_f operator*(const Color_f& c1, const Color_f& c2);
Color_f operator/(const Color_f& c1, const Color_f& c2);

void operator+=(Color_f& c1, const Color_f& c2);
void operator-=(Color_f& c1, const Color_f& c2);
void operator*=(Color_f& c1, const Color_f& c2);
void operator/=(Color_f& c1, const Color_f& c2);

Color_f operator*(const Color_f& c1, float32 c2);
Color_f operator/(const Color_f& c1, float32 c2);

void operator*=(Color_f& c1, float32 c2);
void operator/=(Color_f& c1, float32 c2);
