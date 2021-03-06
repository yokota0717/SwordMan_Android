#include "GameController.h"
#include "../../Class/Sound.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../Components/BasicComponents.hpp"
#include "../Components/Renderer.hpp"
#include "../Components/Collider.hpp"
#include "../ArcheType/Map.hpp"
#include "../ArcheType/Player.hpp"
#include "../Class/TouchInput.hpp"
#include "../Class/Scene/SceneManager.hpp"
#include "../Events/EventManager.hpp"
#include "../Events/AtackEvent.hpp"
#include "../ArcheType/Enemy.hpp"
#include "../Events/AddScoreEvent.hpp"
#include "../Events/GoalEvent.hpp"
#include "../Events/PauseTap.hpp"

#include "../Class/Scene/Title.h"
#include "../Class/Scene/Game.h"
#include "../Class/Scene/Pause.h"
#include "../Class/Scene/Result.h"

void GameController::ResourceLoad()
{
	ResourceManager::GetSound().Load("sounds/Grass.wav", "BGM",SoundType::BGM);
	ResourceManager::GetSound().Load("sounds/rolling.wav", "rolling", SoundType::SE);
	ResourceManager::GetSound().Load("sounds/smash.wav", "smash", SoundType::SE);
	ResourceManager::GetSound().Load("sounds/hit.wav", "hit", SoundType::SE);
	ResourceManager::GetSound().Load("sounds/bomb.wav", "bomb", SoundType::SE);
	ResourceManager::GetGraph().Load("image/cloud.png", "cloud");
	ResourceManager::GetGraph().Load("image/a.png", "a");
	ResourceManager::GetGraph().Load("image/font_text.png", "font");
	ResourceManager::GetGraph().Load("image/ui/goalMessage.png", "goalMessage");
	ResourceManager::GetGraph().Load("image/ui/pauseButton.png", "pauseButton");
	ResourceManager::GetGraph().Load("image/ui/life.png", "health");
	ResourceManager::GetGraph().Load("image/ui/pauseUI.png", "pauseUI");
	ResourceManager::GetGraph().Load("image/ui/fade.png", "fade");
	ResourceManager::GetGraph().Load("image/ui/pauseMessage.png", "pauseMessage");
	ResourceManager::GetGraph().LoadDiv("image/sword.png", "sword", 5, 5, 1, 193, 193);
	ResourceManager::GetGraph().LoadDiv("image/rolling.png", "rolling", 12, 4, 3, 288, 288);	
	ResourceManager::GetGraph().LoadDiv("image/enemy01.png", "enemy1", 2, 2, 1, 96, 96);
	ResourceManager::GetGraph().LoadDiv("image/enemy02.png", "enemy2", 4, 4, 1, 96, 96);
	ResourceManager::GetGraph().LoadDiv("image/enemy03.png", "enemy3", 6, 6, 1, 96, 96);
	ResourceManager::GetGraph().LoadDiv("image/enemy04.png", "enemy4", 4, 4, 1, 96, 96);
	ResourceManager::GetGraph().LoadDiv("image/goal.png", "goal", 1, 1, 1, 144, 192);
	ResourceManager::GetGraph().LoadDiv("image/player.png", "player", 6, 2, 3, 96, 96);
	ResourceManager::GetGraph().LoadDiv("image/effect/hit_weak.png", "hitWeak", 4, 4, 1, 192, 192);
	ResourceManager::GetGraph().LoadDiv("image/effect/bomb.png", "bomb", 4, 4, 1, 192, 192);
	ResourceManager::GetGraph().LoadDiv("image/effect/hit_strong.png", "hitStrong", 5, 5, 1, 192, 192);
}

GameController::GameController()
{
	//最初に必要なリソースやEntityの生成、ロードを行う
	ResourceLoad();
	pManager = &ECS::EcsSystem::GetManager();	
	//初期シーン
	sceneStack.push(std::make_unique< Scene::Title >(this, param));	//タイトルシーンを作成し、プッシュ
	Sound s("BGM");
	s.Play(true,false);
}

void GameController::ResetGame()
{

}

void GameController::Update()
{
	TouchInput::GetInput().Update();
	pManager->Refresh();
	sceneStack.top()->Update();
	MasterSound::Get().Update();
}

void GameController::Draw()
{
	sceneStack.top()->Draw();
}


void GameController::OnSceneChange(const Scene::SceneName& scene, const Parameter& parame, const Scene::SceneStack& stackClear)
{
	switch (stackClear)
	{
	case Scene::SceneStack::Non:
		break;
	case Scene::SceneStack::OneClear:
		sceneStack.pop();
		break;
	case Scene::SceneStack::AllClear:
		StackAllClear();
		break;
	}
	switch (scene)
	{
	case Scene::SceneName::Title:
		sceneStack.push(std::make_unique<Scene::Title>(this, parame));
		break;
	case Scene::SceneName::Game:
		sceneStack.push(std::make_unique<Scene::Game>(this, parame));
		break;
	case Scene::SceneName::Pause:
		sceneStack.push(std::make_unique<Scene::Pause>(this, parame));
		break;
	case Scene::SceneName::Menu:
		break;
	case Scene::SceneName::Result:
		sceneStack.push(std::make_unique<Scene::Result>(this, parame));
		break;
	default:
		break;
	}
}

void GameController::StackAllClear()
{
	while (!sceneStack.empty())
	{
		sceneStack.pop();
	}
}
