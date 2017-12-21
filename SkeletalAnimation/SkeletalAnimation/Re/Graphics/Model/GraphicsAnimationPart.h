#pragma once
#include <Re\Graphics\Model\GraphicsKeystone.h>
#include <Re\Graphics\Model\GraphicsAnimationStep.h>

namespace Graphics
{
	class ModelPart;

	/// animation part which affects only one ModelPart.
	/// there should be at most one AnimationPart per ModelPart in each AnimationController
	/// 
	/// Holds keystones and is able to interpolate keystones 
	class AnimationPart
		: public AnimationStepHolder, public Res::ISerialisable
	{
	public:

		/// applies animation offset to animation part
		void update() const;

		/// permanently edits the base def of a model
		void applyPose() const;

		/// sets modelPart
		/// adds default keystone at 0 time of ModelPart propertites
		void setModelPart(ModelPart* s);
		ModelPart* getModelPart() const { return model; }

		/// returns interpolated modelDef at given @step
		/// @warring make sure that
		///		model is assigned
		///		keystones are sorted
		///		step is within range of min/max step of AnimationPart
		///	otherwise the function will assert
		ModelDef getModelDefAtStep(Step_t step) const;
		/// returns model def at current step
		ModelDef getModelDef() const { return getModelDefAtStep(*step); }

		/// inserts a new keystone to the container. Doesnt sort. Before usage please call @sortKeystones() function
		/// call after modeldef is assigned
		/// never try to apply multiplay Keystones with the same @time 
		void addKeystone(const Keystone& s);

		/// sorts keystones by their step. Call it before any update
		void sortKeystones();
		/// removes all keystones besides default one
		void clearKeystones();
	private:
		std::vector<Keystone> keystones;
		ModelPart *model = nullptr;
		bool sorted = true;

		/// to check whether the animation part is ready to use eg has assigned model and is sorted after any addiction of keystone
		bool isValid() const { return sorted && model; }

		/// for serialization purpose
		friend class AnimationController;
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};
}