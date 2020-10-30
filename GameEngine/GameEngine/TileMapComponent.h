#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"

//forward declaration, so that we don't need to include SFML in Game Project
namespace sf
{
	class Sprite;
}

struct Tile
{
	unsigned int Sprite;
	bool IsCollidable;
};

class LevelComponent : public IComponent
{
public:
	TileMapComponent();
	~TileMapComponent();

public:
	void CreateTileMap(std::string url);
	//need to return the Sprite here so that Window can render it
	const sf::Sprite* GetSprite() { return m_Sprite; }

	const Tile& GetTileAtPosition(const float X, const float Y);

	void AddTile(float X, float Y, bool isCollidable);
	void RemoveTile(float X, float Y, bool isCollidable);

private:
	Tile m_Tiles[64][64];
	sf::Sprite* m_Sprite = nullptr;

};