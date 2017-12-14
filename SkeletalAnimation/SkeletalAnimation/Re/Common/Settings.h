#pragma once
/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)


// sfml
#include <SFML\Graphics.hpp>
using namespace sf;


// std
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>

using namespace std;

#ifndef M_PI
#define M_PI		3.14159265359f
#endif

#include <memory>
#include <functional>


/// Constant sized types
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long int int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long int uint64;
typedef float float32;
typedef double float64;


#define Super __super



/// setters -> functions witch sets up initial state of a effect
/// they return pointner to calling class that you can do chain calls (like with std::cout or std::cin)
/// if you derrive from base class then setters from base class still returns ptr to base type
/// so you have to redefine ptr to reduce casts

#define REDEFINE_SETTER_1(NewClass, functionName, ParamType)\
	NewClass* functionName(ParamType s)	\
	{										\
		Super:: functionName (s);			\
		return this;						\
	}

#define REDEFINE_SETTER_2(NewClass, functionName, ParamType, ParamType2)\
	NewClass* functionName(ParamType s, ParamType2 s2)	\
	{													\
		Super:: functionName (s, s2);					\
		return this;									\
	}

#define REDEFINE_SETTER_3(NewClass, functionName, ParamType, ParamType2, ParamType3)\
	NewClass* functionName(ParamType s, ParamType2 s2, ParamType3 s3)	\
	{																	\
		Super:: functionName (s, s2, s3);								\
		return this;													\
	}