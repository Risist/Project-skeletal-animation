#pragma once
#include <Re\ReEngine.h>
#include <Re\Graphics\Model\GraphicsModel.h>
#include <Re\Graphics\Model\GraphicsAnimationPart.h>
#include <Re\Graphics\ResourceManager.h>

namespace Editor
{

	class StateModel : public Game::State
	{
	public:
		virtual void onStart() override;
		virtual State* onUpdate(sf::Time dt = sf::seconds(1)) override;
		virtual void onExit() override;


	private:
		Graphics::Model model;
		Graphics::AnimationController animation;

		Math::Transform view;

		void loadResources();

		Gui::SetBar *guiModel, *guiTexture;
		Gui::SetBar *guiModelA, *guiKeystone;
		Gui::CheckBox *guiPlayReturn, *guiPlayRestart;

		inline Graphics::ModelPart*		getActualPart() const	{ return model.partsUpdate[guiModel->getProgres()]; }
		inline Graphics::AnimationPart* getActualPartA() const	{ return &(Graphics::AnimationPart&)animation.getPart(guiModelA->getProgres()); }
		inline Graphics::Keystone*		getActualKeystone() const { return &getActualPartA()->getKeystone(guiKeystone->getProgres()); }

		ResId getActualPartTsId() const 
		{
			int n = guiTexture->getProgres();
			auto it = tsInst.begin();
			for (int i = 0; i < n; ++i)
				++it;
			return it->first;
		}
		ResId mapPartTsId(ResId tsId) const
		{
			auto it = tsInst.begin();
			int n = 0;
			while (it->second.atlasId != tsInst[tsId].atlasId && 
				it->second.bounds != tsInst[tsId].bounds
			)
			{
				++n;
				++it;
			}
			return n;
		}

		int findIdOf(Graphics::ModelPart* p)
		{
			auto it = model.partsUpdate.begin();
			for (int i = 0; i < model.partsUpdate.size(); ++i)
			{
				if (*it == p)
					return i;

				++it;
			}
			return -1;
		}

		Gui::Menu *guiEditorModel;
		Gui::Menu *guiEditorAnimation;
		void createEditorModel();
		void createEditorAnimation();

	};

}