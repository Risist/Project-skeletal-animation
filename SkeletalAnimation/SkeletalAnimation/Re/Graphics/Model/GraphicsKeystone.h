#pragma once
#include <Re\Graphics\Model\GraphicsModelDef.h>
#include <Re\Graphics\Model\GraphicsAnimationStep.h>

namespace Graphics
{
	/*
	Keystone of animation
	Real animation state is blended between two keystones
	*/
	class Keystone
	{
	public:
		Keystone() = default;
		Keystone(ModelDef _def, Step_t _time) : def(_def), time(_time) {}

		/// checks whether @step is in range of k1 and k2
		static bool isInRange(Step_t step, const Keystone& k1, const Keystone& k2) 
		{ 
			Step_t _min = k1.time < k2.time ? k1.time : k2.time;
			Step_t _max = k1.time > k2.time ? k1.time : k2.time;
			return step >= _min && step <= _max;
		}

		/// returns a modelDef interpolated between two keystones
		static ModelDef countOffset(Step_t step, const Keystone& k1, const Keystone& k2);

		bool operator>(const Keystone& other) const { return time > other.time; }
		bool operator<(const Keystone& other) const { return time < other.time; }


		ModelDef def;
		Step_t time = 0.f;
	};

}