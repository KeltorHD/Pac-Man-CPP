#include "stdafx.h"

bool isPerpendicular(const dirType& d1, const dirType& d2)
{
	if (d1 == dirType::left)
	{
		if (d2 == dirType::up)
			return true;
		if (d2 == dirType::down)
			return true;
		return false;
	}
	if (d1 == dirType::right)
	{
		if (d2 == dirType::up)
			return true;
		if (d2 == dirType::down)
			return true;
		return false;
	}
	if (d2 == dirType::left)
	{
		if (d1 == dirType::up)
			return true;
		if (d1 == dirType::down)
			return true;
		return false;
	}
	if (d2 == dirType::right)
	{
		if (d1 == dirType::up)
			return true;
		if (d1 == dirType::down)
			return true;
		return false;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, dirType& dir)
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
