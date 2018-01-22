#include <Re\Graphics\Model\GraphicsAnimationPart.h>
#include <Re\Graphics\Model\GraphicsModel.h>
#include <Re\Common\Math\Math.h>

namespace Graphics
{



	void AnimationPart::update() const
	{
		assert(isValid());
		model->applayAnimation(getModelDef());
	}

	void AnimationPart::applyPose() const
	{
		assert(isValid());
		model->applyPose(getModelDef());
	}

	void AnimationPart::setModelPart(ModelPart * s)
	{
		assert(keystones.empty());
		model = s;
		addKeystone(Keystone(ModelDef::zero , 0.f));
	}

	ModelDef AnimationPart::getModelDefAtStep(Step_t step) const
	{
		assert(isValid());
		if (keystones.empty())
			return ModelDef::zero;
		
		/// the iterator to 1st keystone
		auto it = keystones.begin();
		for (; it != keystones.end() - 1; ++it)
			if (Keystone::isInRange(step, *it, *(it + 1)) )
				return Keystone::countOffset(step, *it, *(it + 1) );

		return keystones.back().def;
	}

	void AnimationPart::addKeystone(const Keystone & s)
	{
		assert(model);
		sorted = false;
		keystones.push_back(s);
	}

	void AnimationPart::removeKeystone(size_t id)
	{
		keystones.erase(keystones.begin() + id);
	}

	void AnimationPart::sortKeystones()
	{
		std::sort(keystones.begin(), keystones.end());
		sorted = true;
	}

	void AnimationPart::clearKeystones()
	{
		Keystone defaultKeystone = keystones[0];
		keystones.clear();
		keystones.push_back(defaultKeystone);
	}
	void AnimationPart::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		AnimationStepHolder::serialiseF(file, saver);
		saver.nextLine(file);
		
		if (keystones.empty())
		{
			saver.setEndLine();
			return;
		}

		auto it = keystones.begin();
		do
		{
			saver.save("time", it->time );

			saver.save("posX", it->def.position.x, ModelDef::zero.position.x);
			saver.save("posY", it->def.position.y, ModelDef::zero.position.y);

			saver.save("scaleX", it->def.scale.x, ModelDef::zero.scale.x);
			saver.save("scaleY", it->def.scale.y, ModelDef::zero.scale.y);

			saver.save("rot", it->def.rotation.asDegree(), ModelDef::zero.rotation.asDegree());
			saver.save("mineRot", it->def.mineRotation.asDegree(), ModelDef::zero.mineRotation.asDegree());

			saver.save("clR", it->def.color.r, ModelDef::zero.color.r);
			saver.save("clG", it->def.color.g, ModelDef::zero.color.g);
			saver.save("clB", it->def.color.b, ModelDef::zero.color.b);
			saver.save("clA", it->def.color.a, ModelDef::zero.color.a);

			++it;
		}
		DATA_SCRIPT_MULTILINE_SAVE(file, saver, it != keystones.end() );
	}
	void AnimationPart::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		AnimationStepHolder::deserialiseF(file,loader);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			Keystone ks;
			ks.time = loader.load("time", 0.f);

			ks.def.position.x = loader.load("posX", ModelDef::zero.position.x);
			ks.def.position.y = loader.load("posY", ModelDef::zero.position.y);

			ks.def.scale.x = loader.load("scaleX", ModelDef::zero.scale.x);
			ks.def.scale.y = loader.load("scaleY", ModelDef::zero.scale.y);

			ks.def.rotation = Degree(loader.load("rot", ModelDef::zero.rotation.asDegree()));
			ks.def.mineRotation = Degree(loader.load("mineRot", ModelDef::zero.mineRotation.asDegree()));

			ks.def.color.r = loader.load("clR", ModelDef::zero.color.r);
			ks.def.color.g = loader.load("clG", ModelDef::zero.color.g);
			ks.def.color.b = loader.load("clB", ModelDef::zero.color.b);
			ks.def.color.a = loader.load("clA", ModelDef::zero.color.a);

			addKeystone(ks);
		}
		sortKeystones();
	}
}