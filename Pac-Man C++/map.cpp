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

bool Map::isMove(const dirType& dir, const int& x, const int& y)
{
	if (x < GAME_COL && x > 0 && y < GAME_ROW)
	{
		if (dir == dirType::none)
			return false;

		int move_x = x, move_y = y;
		switch (dir)
		{
		case dirType::left:
			move_x--;
			break;
		case dirType::right:
			move_x++;
			break;
		case dirType::up:
			move_y--;
			break;
		case dirType::down:
			move_y++;
			break;
		}

		if (this->tiles[move_y][move_x] != tileType::wall)
			return true;
		return false;
	}
	return false;
}

bool Map::isWall(const int& x, const int& y)
{
	if (x < GAME_COL && x > 0 && y < GAME_ROW)
	{
		if (this->tiles[y][x] == tileType::wall)
			return true;
		return false;
	}
	return true;
}

void Map::render(sf::RenderTarget* target)
{
	target->draw(map);

	/*sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(16, 16));
	shape.setFillColor(sf::Color::Magenta);

	for (size_t i = 0; i < GAME_ROW; i++)
	{
		for (size_t j = 0; j < GAME_COL; j++)
		{
			if (this->tiles[i][j] == tileType::wall)
			{
				shape.setPosition(j * 16, i * 16);
				target->draw(shape);
			}
		}
	}*/

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

void Map::updateCollision(Entity* entity, const float& dt)
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
