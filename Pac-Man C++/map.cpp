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

	target->draw(food);
	target->draw(energizere);
}

void Map::initTiles()
{
	std::ifstream ifs("Config/tile.map");
	if (!ifs.is_open())
		throw "NOT COULD OPEN FILE TILE.MAP";

	for (size_t i = 0; i < GAME_COL; i++)
	{
		for (size_t j = 0; j < GAME_ROW; j++)
		{
			int tmp;
			ifs >> tmp;
			this->tiles[i][j] = tileType(tmp);
		}
	}
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

	food.setPosition(0, 0);
	energizere.setPosition(16, 0);
}
