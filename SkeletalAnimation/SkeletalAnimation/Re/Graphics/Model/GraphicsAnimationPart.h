#pragma once
#include <Re\Graphics\Model\GraphicsModelDef.h>
#include <Re\Graphics\Model\GraphicsAnimationStep.h>

namespace Graphics
{
	class ModelPart;

	class AnimationPart :
		public AnimationStepHolder
	{
	public:

		/// desired model state at certain animation step
		/// state between keystones is interpolated
		struct KeyStone
		{
			ModelDef desiredDef;
			Step_t step;
			bool operator< (const KeyStone& other) const { return step < other.step; }
			bool operator> (const KeyStone& other) const { return step > other.step; }
		};

		/// applies animation offset to the model
		void onUpdate() const;
		/// permanently modify model by keystone value at current step
		void applyPose() const;

		/// finds model def the animation will apply at passed as an argument step
		/// aproximation bettween discreet keystones
		ModelDef getDefAtStep(Step_t step) const;

		/// changes focus model part so onUpdateFunction will applay animation to the part
		void attachToModel(ModelPart* part) { maintainedModel = part; }
		
		/// returns keystone data at certain id
		/// @warring make sure id is not exceeding keystone range
		KeyStone getKeyStone(size_t id) const { return keystones[id]; }
		size_t getKeyStoneCount() const { return keystones.size(); }

	private:
		/// container of Keystones sorted by step
		vector<KeyStone> keystones;

		/// model part which the animaion part will edit while update
		ModelPart *maintainedModel{ nullptr };

		size_t modelId{0};

		friend class AnimationController;
	protected:
		/// adds new keystone
		void addKeyStone(ModelDef def, Step_t step){keystones.push_back({def, step});}

		/// call this when al the keystones are added
		/// sorts them by step;
		void finaliseKeystones();
	};

}