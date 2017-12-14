#pragma once
#include <Re\Graphics\Model\GraphicsAnimationStep.h>
#include <unordered_map>

/*
/// meta animation is an animation that animates other animations
/// it is usefull when you blend sevral animations and want them to not break model
///		for example humanoid one will be allowed to move its bones only on certain range soas it cannnot do any innatural move
///
/// MetaAnimationController takes control over sevral pointners to AnimationStep* deriving classes 
///	And alters them using the interface.
/// Basic example of AnimationStep class is AnimationController class, but you can create addictional ones which will fit to your needs the best
/// 
namespace Graphics
{

	class MetaAnimationPart :
		public AnimationStepHolder
	{
	public:

		/// applies animation offset to the model
		void onUpdate() const;

		struct KeyStone
		{
			Step_t desiredStep;
			Step_t metaStep;
			bool operator< (const KeyStone& other) const { return metaStep < other.metaStep; }
			bool operator> (const KeyStone& other) const { return metaStep > other.metaStep; }
		};

		/// finds desired controller step an taken as an argument meta step 
		Step_t getDesiredAtMeta(Step_t step) const;

		/// returns keystone data at certain id
		/// @warring make sure id is not exceeding keystone range
		KeyStone getKeyStone(size_t id) const { return keystones[id]; }
		size_t getKeyStoneCount() const { return keystones.size(); }

	private:
		/// container of Keystones sorted by step
		vector<KeyStone> keystones;

		AnimationStep* maintainedController{nullptr};
		friend class MetaAnimationController;

		/// call this when al the keystones are added
		/// sorts them by step;
		void finaliseKeystones();
	};


	class MetaAnimationController 
		: public AnimationStep,
		public Res::ISerialisable
	{
	public:

		/// call this on every frame before model update/ after drawing
		/// applies animations from the conntroller to model
		void onUpdate() const;

		/// adds new controller to the availavle controllers list. Gets an id depended on order of applying.
		void registerController(AnimationStep* s)
		{
			controllers[id] = s;
		}
		void addPart(const MetaAnimationPart& s)
		{
			parts.push_back(s);
		}

	private:
		vector<AnimationStep*> controllers;
		vector<MetaAnimationPart> parts;
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};



}*/