#include "stdafx.h"

bool isPerpendicularDir(const dirType& d1, const dirType& d2)
{
	if (d1 == dirType::left)
	{
		if (d2 == dirType::up || d2 == dirType::down)
			return true;
		return false;
	}
	if (d1 == dirType::right)
	{
		if (d2 == dirType::up || d2 == dirType::down)
			return true;
		return false;
	}
	if (d2 == dirType::left)
	{
		if (d1 == dirType::up || d1 == dirType::down)
			return true;
		return false;
	}
	if (d2 == dirType::right)
	{
		if (d1 == dirType::up || d1 == dirType::down)
			return true;
		return false;
	}
	return false;
}

dirType getPerpendicularDir(const dirType& dir)
{
	switch (dir)
	{
	case dirType::left:
		return dirType::up;
	case dirType::right:
		return dirType::down;
	case dirType::up:
		return dirType::left;
	case dirType::down:
		return dirType::right;
	case dirType::none:
		return dirType::none;
	}
	return dirType::none;
}

dirType getOppositeDir(const dirType& dir)
{
	switch (dir)
	{
	case dirType::left:
		return dirType::right;
	case dirType::right:
		return dirType::left;
	case dirType::up:
		return dirType::down;
	case dirType::down:
		return dirType::up;
	case dirType::none:
		return dirType::none;
	}
	return dirType::none;
}

sf::Vector2i getNextCoordWidthDir(const sf::Vector2i& point, const dirType& dir, const int i)
{
	switch (dir)
	{
	case dirType::left:
		return sf::Vector2i(point.x - i * TILE_WIDTH, point.y);
	case dirType::right:
		return sf::Vector2i(point.x + i * TILE_WIDTH, point.y);
	case dirType::up:
		return sf::Vector2i(point.x, point.y - i * TILE_WIDTH);
	case dirType::down:
		return sf::Vector2i(point.x, point.y + i * TILE_WIDTH);
	case dirType::none:
		return sf::Vector2i(point.x, point.y);
	}
	return sf::Vector2i(point.x, point.y);
}

sf::Vector2f getNextCoordWidthDir(const sf::Vector2f& point, const dirType& dir, const int i)
{
	switch (dir)
	{
	case dirType::left:
		return sf::Vector2f(point.x - i * TILE_WIDTH, point.y);
	case dirType::right:
		return sf::Vector2f(point.x + i * TILE_WIDTH, point.y);
	case dirType::up:
		return sf::Vector2f(point.x, point.y - i * TILE_WIDTH);
	case dirType::down:
		return sf::Vector2f(point.x, point.y + i * TILE_WIDTH);
	case dirType::none:
		return sf::Vector2f(point.x, point.y);
	}
	return sf::Vector2f(point.x, point.y);
}

std::ostream& operator<<(std::ostream& os, const dirType& dir)
{
	switch (dir)
	{
	case dirType::left:
		os << "left";
		break;
	case dirType::right:
		os << "right";
		break;
	case dirType::up:
		os << "up";
		break;
	case dirType::down:
		os << "down";
		break;
	case dirType::none:
		os << "none";
		break;
	}
	return os;
}
