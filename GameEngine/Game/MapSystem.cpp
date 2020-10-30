#include "MapSystem.h"
#include "GameEngine/Engine.h"
#include "GameEngine/LevelComponent.h"
#include "GameEngine/SpriteComponent.h"
#include "PlayerComponent.h"
#include "PhysicComponent.h"
#include "EnemyComponent.h"
#include "ItemComponent.h"
#include "ScoreEvent.h"
#include "ScoreComponent.h"
#include "AmmoComponent.h"
#include "HealthComponent.h"
#include "GameEngine/TextComponent.h"
#include <GameEngine/EventManager.h>

#include "CollisionFlags.h"

MapSystem::MapSystem()
{

}

MapSystem::~MapSystem()
{

}

bool MapSystem::DoesEntityMatch(std::shared_ptr<Entity> entity)
{
	//for reload, we save everything that has a physicsComponent
	if (entity->HasComponent<SpriteComponent>() || entity->HasComponent<TextComponent>())
	{
		return true;
	}
	return false;
}

void MapSystem::Update(Engine* engine, float dt)
{
	bool keyPress = engine->IsKeyPressed(Key::F1);
	if (!m_ReloadKeyPress && keyPress)
	{
		Reload(engine, "levels/level1.tmx");
		m_ReloadKeyPress = true;
	}
	else if(m_ReloadKeyPress && !keyPress)
	{
		m_ReloadKeyPress = false;
	}
}

void MapSystem::Init(Engine* engine)
{
	m_LevelEntity = std::make_shared<Entity>();
	std::shared_ptr<LevelComponent> levelComp = m_LevelEntity->AddComponent<LevelComponent>();
	engine->AddEntity(m_LevelEntity);

	LoadLevel(engine, "levels/level1.tmx");
}

const tmx::Tileset::Tile* MapSystem::GetTile(tmx::Map& map, int tileID)
{
	for (const tmx::Tileset& tileset : map.getTilesets())
	{
		if (tileset.hasTile(tileID))
		{
			return tileset.getTile(tileID);
		}
	}
	return nullptr;
}

void MapSystem::Reload(Engine* engine, std::string level)
{
	while (m_Entities.size() != 0)
	{
		engine->RemoveEntity(m_Entities[0]);
	}
	LoadLevel(engine, level);
}

void MapSystem::LoadLevel(Engine* engine, std::string level)
{
	tmx::Map map;
	map.load(level);
	SetTileset(engine, map);

	const std::vector<tmx::Layer::Ptr>& layers = map.getLayers();
	m_MapWidth = map.getTileCount().x;
	m_MapHeight = map.getTileCount().y;

	for (int i = 0; i < layers.size(); ++i)
	{
		if (layers[i]->getType() == tmx::Layer::Type::Tile)
		{
			const tmx::TileLayer* layer = dynamic_cast<const tmx::TileLayer*>(layers[i].get());
			AddTiles(layer, map);
		}
		else if (layers[i]->getType() == tmx::Layer::Type::Object)
		{
			const tmx::ObjectGroup& objects = *dynamic_cast<const tmx::ObjectGroup*>(layers[i].get());
			for (const tmx::Object& object : objects.getObjects())
			{
				const tmx::Tileset::Tile* tile = GetTile(map, object.getTileID());
				if (tile->type == "Player")
				{
					AddPlayer(engine, object, tile);
				}
				else if (tile->type == "Enemy")
				{
					AddEnemy(engine, object, tile);
				}
				else if (tile->type == "Item")
				{
					AddItem(engine, object, tile);
				}
			}

		}
	}
	LoadUI(engine);
}

void MapSystem::LoadUI(Engine* engine)
{
	std::shared_ptr<Entity> scoreEntity = std::make_shared<Entity>();
	std::shared_ptr<TextComponent> scoreText = scoreEntity->AddComponent<TextComponent>();
	std::shared_ptr<ScoreComponent> scoreComp = scoreEntity->AddComponent<ScoreComponent>();

	scoreText->SetFont("Hyperspace.otf");
	scoreText->SetColor(255, 255, 255, 255);
	scoreText->SetPosition(10.0f, 10.0f);
	scoreText->SetSize(24);

	engine->AddEntity(scoreEntity);

	std::shared_ptr<Entity> ammoEntity = std::make_shared<Entity>();
	std::shared_ptr<TextComponent> ammoText = ammoEntity->AddComponent<TextComponent>();
	std::shared_ptr<AmmoComponent> ammoComp = ammoEntity->AddComponent<AmmoComponent>();

	ammoText->SetFont("Hyperspace.otf");
	ammoText->SetColor(255, 255, 255, 255);
	ammoText->SetPosition(10.0f, 40.0f);
	ammoText->SetSize(24);

	engine->AddEntity(ammoEntity);

	std::shared_ptr<Entity> healthEntity = std::make_shared<Entity>();
	std::shared_ptr<TextComponent> healthText = healthEntity->AddComponent<TextComponent>();
	std::shared_ptr<HealthComponent> healthComp = healthEntity->AddComponent<HealthComponent>();

	healthText->SetFont("Hyperspace.otf");
	healthText->SetColor(255, 255, 255, 255);
	healthText->SetPosition(10.0f, 70.0f);
	healthText->SetSize(24);

	engine->AddEntity(healthEntity);
}

void MapSystem::SetTileset(Engine* engine, tmx::Map& map)
{
	std::shared_ptr<LevelComponent> levelComp = m_LevelEntity->GetComponent<LevelComponent>();
	for (const tmx::Tileset& tileset : map.getTilesets())
	{
		bool isTileMap = false;
		for (const tmx::Property& property : tileset.getProperties())
		{
			if (property.getName() == "IsTileMap")
			{
				isTileMap = true;
				break;
			}
		}

		if (isTileMap)
		{
			m_TileWidth = tileset.getTileSize().x;
			m_TileHeight = tileset.getTileSize().y;
			levelComp->CreateTileset(tileset.getImagePath(), m_TileWidth, m_TileHeight);
			break;
		}
	}
}

void MapSystem::AddTiles(const tmx::TileLayer* layer, tmx::Map& map)
{
	std::vector<Tile> gameTiles;
	std::shared_ptr<LevelComponent> levelComp = m_LevelEntity->AddComponent<LevelComponent>();
	const std::vector<tmx::TileLayer::Tile>& layerTiles = layer->getTiles();
	for (int j = 0; j < layerTiles.size(); ++j)
	{
		const tmx::TileLayer::Tile& layerTile = layerTiles[j];
		const tmx::Tileset::Tile* tile = GetTile(map, layerTile.ID);

		Tile gameTile;
		gameTile.X = (j % m_MapWidth) * m_TileWidth;
		gameTile.Y = std::floor(j / m_MapHeight) * m_TileHeight;
		gameTile.textureX = tile->imagePosition.x;
		gameTile.textureY = tile->imagePosition.y;
		for (const tmx::Property& property : tile->properties)
		{
			if (property.getName() == "Collidable")
			{
				gameTile.IsCollidable = property.getBoolValue();
			}
		}
		gameTiles.push_back(gameTile);
	}

	levelComp->SetLevel(gameTiles, m_MapWidth, m_MapHeight);
}

void MapSystem::AddPlayer(Engine* engine, const tmx::Object& object, const tmx::Tileset::Tile* tile)
{
	std::shared_ptr<Entity> playerEntity = std::make_shared<Entity>();
	std::shared_ptr<SpriteComponent> playerSprite = playerEntity->AddComponent<SpriteComponent>();
	std::shared_ptr<PhysicComponent> playerPhysics = playerEntity->AddComponent<PhysicComponent>();
	std::shared_ptr<PlayerComponent> playerComp = playerEntity->AddComponent<PlayerComponent>();
	playerSprite->CreateSprite(tile->imagePath);
	playerSprite->SetPosition(object.getPosition().x, object.getPosition().y);

	playerPhysics->SetVelocity(0.f, 0.0f);
	playerPhysics->SetDamping(0.1f);
	playerPhysics->SetTargetFlag(EnemyCollisionFlag | ItemCollisionFlag);

	for (const tmx::Property& property : tile->properties)
	{
		if (property.getName() == "BulletSpeedPerSecond")
		{
			playerComp->SetBulletSpeedPerSecond(property.getFloatValue());
		}
		if (property.getName() == "MaxBulletSpawnCooldown")
		{
			playerComp->SetMaxBulletSpawnCooldown(property.getFloatValue());
		}
		if (property.getName() == "SpeedPerSecond")
		{
			playerComp->SetSpeedPerSecond(property.getFloatValue());
		}
		if (property.getName() == "StartAmmo")
		{
			playerComp->SetAmmo(property.getIntValue());
		}
		if (property.getName() == "StartHP")
		{
			playerComp->SetHP(property.getIntValue());
		}
	}
	engine->AddEntity(playerEntity);
}

void MapSystem::AddEnemy(Engine* engine, const tmx::Object& object, const tmx::Tileset::Tile* tile)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	std::shared_ptr<SpriteComponent> spriteComp = entity->AddComponent<SpriteComponent>();
	std::shared_ptr<PhysicComponent> physicComp = entity->AddComponent<PhysicComponent>();
	std::shared_ptr<EnemyComponent> enemyComp = entity->AddComponent<EnemyComponent>();
	spriteComp->CreateSprite(tile->imagePath);
	spriteComp->SetPosition(object.getPosition().x, object.getPosition().y);

	physicComp->SetVelocity(0.f, 0.0f);
	physicComp->SetDamping(0.1f);
	physicComp->SetCollisionFlag(EnemyCollisionFlag);
	physicComp->SetTargetFlag(BulletCollisionFlag);
	for (const tmx::Property& property : tile->properties)
	{
		if (property.getName() == "HP")
		{
			enemyComp->SetHP(property.getIntValue());
		}
		if (property.getName() == "SpeedPerSecond")
		{
			enemyComp->SetSpeedPerSecond(property.getFloatValue());
		}
	}
	engine->AddEntity(entity);
}

void MapSystem::AddItem(Engine* engine, const tmx::Object& object, const tmx::Tileset::Tile* tile)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	std::shared_ptr<SpriteComponent> spriteComp = entity->AddComponent<SpriteComponent>();
	std::shared_ptr<PhysicComponent> physicComp = entity->AddComponent<PhysicComponent>();
	std::shared_ptr<ItemComponent> itemComp = entity->AddComponent<ItemComponent>();
	spriteComp->CreateSprite(tile->imagePath);
	spriteComp->SetPosition(object.getPosition().x, object.getPosition().y);
	physicComp->SetCollisionFlag(ItemCollisionFlag);
	for (const tmx::Property& property : tile->properties)
	{
		if (property.getName() == "HP")
		{
			itemComp->SetHP(property.getIntValue());
		}
		if (property.getName() == "Ammo")
		{
			itemComp->SetAmmo(property.getIntValue());
		}
	}
	engine->AddEntity(entity);
}
