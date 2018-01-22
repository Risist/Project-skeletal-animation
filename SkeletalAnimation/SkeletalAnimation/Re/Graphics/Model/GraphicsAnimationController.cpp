#include <Re\Graphics\Model\GraphicsAnimationController.h>
#include <Re\Graphics\Model\GraphicsModel.h>

namespace Graphics
{

	AnimationController::AnimationController()
	{
	}

	void AnimationController::update() const
	{
		for (auto &it : parts)
			it.update();
	}

	void AnimationController::applyPose() const
	{
		for (auto it : parts)
			it.applyPose();
	}

	
	void AnimationController::addPart(const AnimationPart& newPart)
	{
		parts.push_back(newPart);
		parts.back().step = &step;
	}

	void AnimationController::attachToModel(vector<ModelPart*>& model)
	{
		parts.clear();
		for (auto&it : model)
		{
			parts.push_back(AnimationPart());
			parts.back().setModelPart(it);

			parts.back().setStepPtr(&step);
		}
	}
	void AnimationController::clearKeystones()
	{
		for (auto&it : parts)
		{
			it.clearKeystones();
		}
	}
	void AnimationController::clear()
	{
		parts.clear();
	}
	void AnimationController::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		AnimationStep::serialiseF(file, saver);

		saver.nextLine(file);
		for (int modelId = 0; modelId < parts.size(); ++modelId)
			for (int keyId = 0; keyId < parts[modelId].keystones.size(); ++keyId)
		{
			auto &it = parts[modelId].keystones[keyId];
			if (it.time == 0)
				continue;

			saver.save("model", modelId);
			saver.save("time", it.time);

			saver.save("posX", it.def.position.x, ModelDef::zero.position.x);
			saver.save("posY", it.def.position.y, ModelDef::zero.position.y);

			saver.save("scaleX", it.def.scale.x, ModelDef::zero.scale.x);
			saver.save("scaleY", it.def.scale.y, ModelDef::zero.scale.y);

			saver.save("rot", it.def.rotation.asDegree(), ModelDef::zero.rotation.asDegree());
			saver.save("mineRot", it.def.mineRotation.asDegree(), ModelDef::zero.mineRotation.asDegree());

			saver.save("clR", it.def.color.r, ModelDef::zero.color.r);
			saver.save("clG", it.def.color.g, ModelDef::zero.color.g);
			saver.save("clB", it.def.color.b, ModelDef::zero.color.b);
			saver.save("clA", it.def.color.a, ModelDef::zero.color.a);

			saver.nextLine(file);
		}

		saver.setEndLine();
	}

	void AnimationController::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		AnimationStep::deserialiseF(file, loader);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			size_t modelId = loader.load<size_t>("model", 0);
			assert(parts.size() > modelId);

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

			parts[modelId].addKeystone(ks);
		}

		for (auto &it : parts)
		{
			it.sortKeystones();
		}
	}

}