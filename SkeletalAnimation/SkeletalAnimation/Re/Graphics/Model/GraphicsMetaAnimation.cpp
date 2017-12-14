#include <Re\Graphics\Model\GraphicsMetaAnimation.h>

/**
namespace Graphics
{

	void MetaAnimationPart::onUpdate() const
	{
		assert(maintainedController);
	}

	Step_t MetaAnimationPart::getDesiredAtMeta(Step_t step) const
	{/// Animation Part has to have at least one keystone
		assert(!keystones.empty());

		/// bounding range checks
		if (step >= keystones.back().metaStep)
			return keystones.back().desiredStep;
		else if (step <= keystones.front().metaStep)
			return keystones.front().desiredStep;
		/// case of one keystone is handled by checks above

		/// find the most fitting partition

		/// front keystone of partition step is within
		auto actualKeystone = keystones.begin();
		for (; actualKeystone != keystones.end() - 1; ++actualKeystone)
			if (step >= actualKeystone->metaStep && step <= (actualKeystone + 1)->metaStep)
				goto ret;

		/// this should be never hit
		/// if does probably keystones are not sorted
		assert(false);

	ret:
		Step_t retStep = actualKeystone->desiredStep +
			((actualKeystone + 1)->desiredStep - actualKeystone->desiredStep)
			*(step - actualKeystone->metaStep)
			/ ((actualKeystone + 1)->metaStep - actualKeystone->metaStep);

		return retStep;
	}

	void MetaAnimationPart::finaliseKeystones()
	{
		std::sort(keystones.begin(), keystones.end());
	}
	/////////////////////////////////////////////////////////////////

	void MetaAnimationController::onUpdate() const
	{
		for (auto &it : parts)
			it.onUpdate();
	}

	void MetaAnimationController::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		/// TODO
	}

	void MetaAnimationController::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		AnimationStep::deserialiseF(file, loader);

		map<size_t, MetaAnimationPart> partMap;

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			size_t controllerId = loader.load<size_t>("controller", 0);
			
			Step_t desiredStep = loader.load<Step_t>("desiredStep", 0);
			Step_t metaStep = loader.load<Step_t>("step", 0.f);
			
			partMap[controllerId].keystones.push_back({ desiredStep,metaStep });

			//controllers[controllerId] = { loader.load<Step_t>("desiredStep", 0.f) , loader.load<Step_t>("step", 0.f) }

			//parts.
			/**ModelDef def;
			{
				def.position.x = loader.load("posX", ModelDef::zero.position.x);
				def.position.y = loader.load("posY", ModelDef::zero.position.y);

				def.scale.x = loader.load("scaleX", ModelDef::zero.scale.x);
				def.scale.y = loader.load("scaleY", ModelDef::zero.scale.y);

				def.rotation = Degree(loader.load("rot", ModelDef::zero.rotation.asDegree()));
				def.mineRotation = Degree(loader.load("mineRot", ModelDef::zero.mineRotation.asDegree()));

				def.color.r = loader.load("clR", ModelDef::zero.color.r);
				def.color.g = loader.load("clG", ModelDef::zero.color.g);
				def.color.b = loader.load("clB", ModelDef::zero.color.b);
				def.color.a = loader.load("clA", ModelDef::zero.color.a);
			}*


			modelMap[controllerId].addKeyStone(def, loader.load<Step_t>("step", 0.f));
		}

		for (auto it : modelMap)
		{
			it.second.finaliseKeystones();
			it.second.modelId = it.first;
			addPart(it.second);
		}
	}

}/**/