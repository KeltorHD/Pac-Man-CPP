#include "stdafx.h"
#include "ghost.h"

Ghost::Ghost()
	: Entity(75.f, dirType::left, dirType::none)
{
	this->targetCell = sf::Vector2f(0.f, 0.f);
	this->mode = modeType::chase;
}

Ghost::~Ghost()
{
}

const Ghost::modeType& Ghost::getMode()
{
	return this->mode;
}

void Ghost::setMode(modeType mode)
{
	this->mode = mode;
}

void Ghost::updateDir(const Map* map, const float& dt)
{
	/*����� ��������� ������� ���������� �� �������� �����������*/
	sf::Vector2i next = 
	{
		(int(this->getNextPosition(this->current, dt).x) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2,
		(int(this->getNextPosition(this->current, dt).y) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2
	};

	/*��������� ������� �����?*/
	if (!map->isWall
	(
		next.x / TILE_WIDTH,
		next.y / TILE_WIDTH
	))
	{
		/*
		������� �� ���� ��������� ������ ��� �������� ��, ������� ��������
		������ � ������� ����� � �� ������� � ������� ������� ��������.
		���� ����� ��������� ����� ����� 3-�, �� �� ����� ����� ������.
		���� ��� ��������� ���� ����������� ������ � ������� �����, ��
		���������� ������������� ����� �������:
		������� > ����� > ������
		*/
		std::vector<std::pair<dirType, float>> distance; /*������ ��� �����������-����������*/
		dirType cur = this->current; /*����������� �����������*/

		/*������ �����������*/
		sf::Vector2i tmpPos = getNextCoordWidthDir(next, cur);
		/*���� ��������� ������� �� ����� ����������� �� �����*/
		if (!map->isWall
		(
			tmpPos.x / TILE_WIDTH,
			tmpPos.y / TILE_WIDTH
		))
		{
			distance.push_back({ cur, map->distance(conversion(tmpPos), this->targetCell) });
		}

		/*������ �����������*/
		cur = getPerpendicularDir(cur); /*���������������� �����������*/
		tmpPos = getNextCoordWidthDir(next, cur);
		/*���� ��������� ������� �� ����� ����������� �� �����*/
		if (!map->isWall
		(
			tmpPos.x / TILE_WIDTH,
			tmpPos.y / TILE_WIDTH
		))
		{
			distance.push_back({ cur, map->distance(conversion(tmpPos), this->targetCell) });
		}

		/*������ �����������*/
		cur = getOppositeDir(cur); /*��������������� ����������������� �����������*/
		tmpPos = getNextCoordWidthDir(next, cur);
		/*���� ��������� ������� �� ����� ����������� �� �����*/
		if (!map->isWall
		(
			tmpPos.x / TILE_WIDTH,
			tmpPos.y / TILE_WIDTH
		))
		{
			distance.push_back({ cur, map->distance(conversion(tmpPos), this->targetCell) });
		}

		/*����� ����������� �� ����������� ����������*/
		if (distance.size())
		{
			/*��������� ������ ������*/
			if (!map->isGhostUp(int(this->getNextPosition(this->current, dt).x) / TILE_WIDTH, int(this->getNextPosition(this->current, dt).y) / TILE_WIDTH))
			{
				distance.erase(std::remove_if(distance.begin(), distance.end(),
					[](auto& element) {return element.first == dirType::up; }), distance.end());
			}

			float minimum = 1000.f;
			dirType dir = dirType::none;
			for (size_t i = 0; i < distance.size(); i++)
			{
				if (distance[i].second < minimum)
				{
					minimum = distance[i].second;
					dir = distance[i].first;
				}
			}

			this->setDir(dir);
		}
	}
}

void Ghost::updateMoveGhost(const Map* map, const float& dt)
{
	if (this->mode == modeType::chase)
	{
		/*���������� ����������� �������� �� ������� �����*/
		this->updateDir(map, dt);
	}
	else if (this->mode == modeType::frightened)
	{

	}
	else if (this->mode == modeType::scatter)
	{

	}
	/*��������*/
	this->updateMove(map, dt);
}