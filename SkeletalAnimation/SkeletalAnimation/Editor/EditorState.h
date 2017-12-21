#pragma once
#include <Re\ReEngine.h>
#include <Re\Graphics\Model\GraphicsModel.h>
#include <Re\Graphics\Model\GraphicsAnimationPart.h>

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

		void loadResources();

	};

}