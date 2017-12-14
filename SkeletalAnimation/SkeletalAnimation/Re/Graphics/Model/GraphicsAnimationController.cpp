#include <Re\Graphics\Model\GraphicsAnimationController.h>
#include <Re\Graphics\Model\GraphicsModel.h>

namespace Graphics
{

	AnimationController::AnimationController()
	{
	}

	void AnimationController::onUpdate() const
	{
		for (auto &it : parts)
			it.onUpdate();
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
		for (auto&it : parts)
		{
			assert(it.modelId < model.size());
			it.attachToModel(model[it.modelId]);
		}
	}
	void AnimationController::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
#ifdef RE_ENGINE
		/// animation serialization available only in editor
		/// TODO
#endif // RE_ENGINE
	}

	void AnimationController::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		AnimationStep::deserialiseF(file, loader);

		/// here will be saved all the parts to allow to find them by id
		map<size_t, AnimationPart> modelMap;

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			size_t modelId = loader.load<size_t>("model", 0);
			
			ModelDef def;
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
			}

			modelMap[modelId].addKeyStone(def, loader.load<Step_t>("step", 0.f) );
		}

		for (auto it : modelMap)
		{
			it.second.finaliseKeystones();
			it.second.modelId = it.first;
			addPart(it.second);
		}
	}

}