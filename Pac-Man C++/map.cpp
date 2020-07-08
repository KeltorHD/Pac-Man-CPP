#include "stdafx.h"
#include "map.h"

Map::Map()
{
	this->initVar();
	this->initSprites();
	this->initTiles();
}

Map::~Map()
{
}

const size_t& Map::getCountEat() const
{
	return this->eat;
}

bool Map::isGhostUp(const int& cell_x, const int& cell_y) const
{
	if (
		(((cell_x == NOT_UP_CELL_X1) || (cell_x == NOT_UP_CELL_X2)) && (cell_y == NOT_UP_CELL_Y1))
		|| (((cell_x == NOT_UP_CELL_X1) || (cell_x == NOT_UP_CELL_X2)) && (cell_y == NOT_UP_CELL_Y2))
		)
	{
		return false;
	}
	return true;
}

bool Map::isMove(const dirType& dir, const int& x, const int& y) const
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

bool Map::isWall(const int& x, const int& y) const
{
	if (x < GAME_COL && x > 0 && y < GAME_ROW)
	{
		if (this->tiles[y][x] == tileType::wall)
			return true;
		return false;
	}
	return true;
}

bool Map::isEqual(const sf::Vector2f& one, const sf::Vector2f& two)
{
	int one_x = int(one.x / TILE_WIDTH);
	int one_y = int(one.y / TILE_WIDTH);

	int two_x = int(two.x / TILE_WIDTH);
	int two_y = int(two.y / TILE_WIDTH);

	if (one_x == two_x && one_y == two_y)
		return true;
	return false;
}

void Map::reload()
{
	this->initTiles();
	this->initVar();
}

float Map::distance(const sf::Vector2f& p1, const sf::Vector2f& p2) const
{
	return pow((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y), 0.5f);
}

int Map::updateFood(const sf::Vector2f& playerPos)
{
	int x = int(playerPos.x);
	int y = int(playerPos.y);
	if (this->tiles[y / TILE_WIDTH][x / TILE_WIDTH] == tileType::food)
	{
		this->eat--;
		this->tiles[y / TILE_WIDTH][x / TILE_WIDTH] = tileType::free;
		return 1;
	}
	if (this->tiles[y / TILE_WIDTH][x / TILE_WIDTH] == tileType::energizere)
	{
		this->ener--;
		this->tiles[y / TILE_WIDTH][x / TILE_WIDTH] = tileType::free;
		return 2;
	}
	return 0;
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

void Map::initVar()
{
	this->eat = COUNT_EAT;
	this->ener = COUNT_ENERGIZERE;
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
	foodSprite.setTexture(food_ener);
	foodSprite.setTextureRect(sf::IntRect(sf::Vector2i(16, 0), sf::Vector2i(16, 16)));

	energizereSprite.setTexture(food_ener);
	energizereSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16, 16)));
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
				foodSprite.setPosition(float(j) * 16, float(i) * 16);
				target->draw(foodSprite);
				break;
			case tileType::energizere:
				energizereSprite.setPosition(float(j) * 16, float(i) * 16);
				target->draw(energizereSprite);
				break;
			case tileType::wall:
				break;
			case tileType::free:
				break;
			}
		}
	}
}
