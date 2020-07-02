#include "stdafx.h"
#include "map.h"

Map::Map()
{
	this->initSprites();
	this->initTiles();
}

Map::~Map()
{
}

void Map::render(sf::RenderTarget* target)
{
	target->draw(map);

	renderFood(target);
}

void Map::initTiles()
{
	std::ifstream ifs("Config/tile.map");
	if (!ifs.is_open())
		throw "NOT COULD OPEN FILE TILE.MAP";

	for (size_t i = 0; i < GAME_ROW; i++)
	{
		for (size_t j = 0; j < GAME_COL; j++)
		{
			int tmp;
			ifs >> tmp;
			this->tiles[i][j] = static_cast<tileType>(tmp);
		}
	}
	ifs.close();
}

void Map::initSprites()
{
	if (!mapTexture.loadFromFile("Images/map.png"))
		throw "NOT COULD LOAD MAP IMAGE";
	map.setTexture(mapTexture);

	if (!food_ener.loadFromFile("Images/ener_food.png"))
		throw "NOT COULD LOAD FOOD IMAGE";
	food.setTexture(food_ener);
	food.setTextureRect(sf::IntRect(sf::Vector2i(16, 0), sf::Vector2i(16, 16)));

	energizere.setTexture(food_ener);
	energizere.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16, 16)));
}

void Map::updateCollision(Enemy* enemy, const float& dt)
{
}

void Map::renderFood(sf::RenderTarget* target)
{
	for (size_t i = 0; i < GAME_ROW; i++)
	{
		for (size_t j = 0; j < GAME_COL; j++)
		{
			switch (this->tiles[i][j])
			{
			case tileType::food:
				food.setPosition(float(j) * 16, float(i) * 16);
				target->draw(food);
				break;
			case tileType::energizere:
				energizere.setPosition(float(j) * 16, float(i) * 16);
				target->draw(energizere);
				break;
			case tileType::wall:
				break;
			case tileType::free:
				break;
			}
		}
	}
}
