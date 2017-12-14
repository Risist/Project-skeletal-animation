#include <Re\Graphics\Model\GraphicsAnimationPart.h>
#include <Re\Graphics\Model\GraphicsModel.h>
#include <Re\Common\Math\Math.h>

namespace Graphics
{

	void AnimationPart::onUpdate() const
	{
		assert(maintainedModel);
		maintainedModel->applayAnimation(getDefAtStep(getActualStep()));
	}
	void AnimationPart::applyPose() const
	{
		assert(maintainedModel);
		maintainedModel->applayPose(getDefAtStep(getActualStep()));
	}
	ModelDef AnimationPart::getDefAtStep(Step_t step) const
	{
		/// Animation Part has to have at least one keystone
		assert(!keystones.empty());

		/// bounding range checks
		if (step >= keystones.back().step)
			return keystones.back().desiredDef;
		else if (step <= keystones.front().step)
			return keystones.front().desiredDef;
		/// case of one keystone is handled by checks above

		/// find the most fitting partition
		
		/// front keystone of partition step is within
		auto actualKeystone = keystones.begin();
		for (; actualKeystone != keystones.end()-1; ++actualKeystone)
			if (step >= actualKeystone->step && step <= (actualKeystone+1)->step)
				goto ret;
		
		/// this should be never hit
		/// if does probably keystones are not sorted
		assert(false); 

	ret:
		ModelDef retDef = actualKeystone->desiredDef +
			((actualKeystone + 1)->desiredDef - actualKeystone->desiredDef)
			*(step - actualKeystone->step)
			/ ((actualKeystone + 1)->step - actualKeystone->step);

		return retDef;
	}

	void AnimationPart::finaliseKeystones()
	{
		std::sort(keystones.begin(), keystones.end() );
	}
}