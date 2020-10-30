#include "GameEngine/Engine.h"
#include "PhysicSystem.h"
#include "PlayerSystem.h"
#include "BulletComponent.h"
#include "BulletSystem.h"
#include "UISystem.h"
#include "MapSystem.h"
#include "EnemySystem.h"

#include <ctime>
#include <algorithm>
#include <vector>

#ifdef _DEBUG
#define EngineMain main
#else
#define EngineMain WinMain
#endif

int EngineMain()
{

	int width = 640;
	int height = 480;
	std::shared_ptr<Engine> engine = std::make_shared<Engine>(width, height, "Test", false);

	//Normally this all would be defined in data which is somehow loaded during runtime
	std::shared_ptr<PhysicSystem> physicSystem = std::make_shared<PhysicSystem>();
	engine->AddSystem(physicSystem);

	std::shared_ptr<PlayerSystem> playerSystem = std::make_shared<PlayerSystem>();
	engine->AddSystem(playerSystem);

	std::shared_ptr<EnemySystem> enemySystem = std::make_shared<EnemySystem>();
	engine->AddSystem(enemySystem);

	std::shared_ptr<BulletSystem> bulletSystem = std::make_shared<BulletSystem>();
	engine->AddSystem(bulletSystem);

	std::shared_ptr<UISystem> uiSystem = std::make_shared<UISystem>();
	engine->AddSystem(uiSystem);

	std::shared_ptr<MapSystem> mapSystem = std::make_shared<MapSystem>();
	engine->AddSystem(mapSystem);

	while (engine->IsRunning())
	{
		engine->Update();
		engine->Draw();
	}

	return 0;
}