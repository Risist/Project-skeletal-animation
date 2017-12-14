#pragma once
#include <Re\Graphics\Model\GraphicsAnimationPart.h>

namespace Graphics
{
	class AnimationController : public Res::ISerialisable, public AnimationStep
	{
	public:
		AnimationController();
		
		/// call this on every frame before model update/ after drawing
		/// applies animations from the conntroller to model
		void onUpdate() const;

		/// permanently edits model state by actual animation data
		void applyPose() const;

		/// add new animation part 
		void addPart(const AnimationPart& newPart);

		/// attach the animation to model
		/// AnimationParts holds ptr to models they are animating 
		/// modelId determine which modelPart is choosen
		/// call after initialisation of modelId(deserialise function) and before first onUpdate
		/// @Warring! slow operation. Don't use that on every frame 
		void attachToModel(vector<ModelPart*>& model);

	private:
		/// animation parts holded
		vector<AnimationPart> parts;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}