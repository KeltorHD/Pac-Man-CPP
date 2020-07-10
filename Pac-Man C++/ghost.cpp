#include "stdafx.h"
#include "ghost.h"

sf::Texture Ghost::frightenedTexture; /*������������� ����������� ��������*/
sf::Texture Ghost::toHomeTexture; /*������������� ����������� ��������*/
Ghost::patternMode Ghost::pattern; /*������������� ������������ �������*/

Ghost::Ghost(const sf::Color& color, const float pos_x, const float pos_y)
	: Entity(75.f, dirType::left, dirType::none)
{
	this->initTimers();
	this->initSprite(color, pos_x, pos_y);
	this->initComponents();
	this->animationComponent->setTextureSheet(this->baseTexture);

	this->targetCell = sf::Vector2f(0.f, 0.f);
	this->mode = this->pattern[this->patternCounter].first;
}

Ghost::~Ghost()
{
	delete this->hitboxComponent;
	delete this->animationComponent;
}

const Ghost::modeType& Ghost::getMode()
{
	return this->mode;
}

const bool Ghost::isMoveDone()
{
	return int(this->getPosition().x) == int(this->targetCell.x)
		&& int(this->getPosition().y) == int(this->targetCell.y);
}

void Ghost::setMode(modeType mode)
{
	if (this->mode == modeType::toHome)
	{
		/*���� ����� �� ������*/
		if (this->isMoveDone() && mode != modeType::toHome)
		{
			this->animationComponent->setTextureSheet(this->baseTexture);
			this->mode = mode;
		}
	}
	else
	{
		if (mode == modeType::frightened)
		{
			this->frigthetenedTimer = 0.f;
		}
		if (this->mode != mode)
		{
			/*�������� ����������� �� ���������������*/
			this->current = getOppositeDir(this->current);
			/*������� �������� ��� ��������*/
			if (mode == modeType::frightened)
			{
				this->frigthetenedTimer = 0.f;
				this->animationComponent->setTextureSheet(this->frightenedTexture);
			}
			else if (mode == modeType::toHome)
			{
				this->animationComponent->setTextureSheet(this->toHomeTexture);
			}
			else
			{
				this->animationComponent->setTextureSheet(this->baseTexture);
			}
		}

		this->mode = mode;
	}
}

void Ghost::loadStaticVar()
{
	if (!Ghost::frightenedTexture.loadFromFile("Images/frightened.png"))
		throw "NOT COULD LOAD FRIGHTENED IMAGE";
	if (!Ghost::toHomeTexture.loadFromFile("Images/to_home.png"))
		throw "NOT COULD LOAD TOHOME IMAGE";

	std::ifstream ifs;
	ifs.open("Config/patternMode.ini");
	if (!ifs.is_open())
		throw "NOT COULD LOAD PATTERNMODE.ini";

	for (size_t i = 0; i < 8; i++)
	{
		int tmp;
		Ghost::pattern.push_back(std::pair<modeType, float>());
		ifs >> tmp;
		Ghost::pattern[i].first = modeType(tmp);
		ifs >> Ghost::pattern[i].second;
	}
	ifs.close();
}

void Ghost::update(const Map* map, const Player* player, const float& dt)
{
	this->updateTimers(dt);
	this->updateTargetcell(player, map);
	this->updateMoveGhost(map, dt);
	this->hitboxComponent->update();
	this->updateAnimation(dt);
}

void Ghost::initSprite(const sf::Color& color, const float pos_x, const float pos_y)
{
	sf::Image imageGhost; /*����������� ����������*/
	if (!imageGhost.loadFromFile("Images/ghost.png"))
		throw "NOT COULD LOAD GHOST IMAGE";

	/*�������������� ����� ��������*/
	for (size_t i = 0; i < imageGhost.getSize().x; i++)
	{
		for (size_t j = 0; j < imageGhost.getSize().y; j++)
		{
			if (imageGhost.getPixel(i, j) == sf::Color::Red)
				imageGhost.setPixel(i, j, color);
		}
	}
	this->baseTexture.loadFromImage(imageGhost);

	this->sprite.setTexture(this->baseTexture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 28, 28));
	this->sprite.setPosition(pos_x, pos_y);
}

void Ghost::initComponents()
{
	this->animationComponent = new AnimationComponent(this->sprite, this->baseTexture);
	this->hitboxComponent = new HitboxComponent(this->sprite, 6, 6, 16, 16);

	/*���������� ��������*/
	this->animationComponent->addAnimation("horizontal", 15.f, 0, 0, 1, 0, 28, 28);
	this->animationComponent->addAnimation("down", 15.f, 0, 1, 1, 1, 28, 28);
	this->animationComponent->addAnimation("up", 15.f, 0, 2, 1, 2, 28, 28);
}

void Ghost::initTimers()
{
	this->frigthetenedTimer = 0.f;
	this->patternTimer = 0.f;
}

void Ghost::updateDirBase(distanceType& distance, const Map* map, const float& dt)
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

	}
}

void Ghost::updateTimers(const float& dt)
{
	/*�������� �� ������� ������*/
	if (this->mode == modeType::frightened)
	{
		this->frigthetenedTimer += dt;

		if (this->frigthetenedTimer >= FRIGHTENED_TIME)
		{
			this->setMode(modeType::chase);
		}
	}
	else if (this->mode != modeType::inHome && this->mode != modeType::toHome)
	{
		this->patternTimer += dt;

		if (this->patternTimer >= this->pattern[this->patternCounter].second)
		{
			this->patternTimer = 0.f;
			this->setMode(this->pattern[++this->patternCounter].first);
		}
	}
}

void Ghost::updateDirRand(const Map* map, const float& dt)
{
	distanceType distance;
	this->updateDirBase(distance, map, dt);

	/*����� ����������� ��������*/
	if (distance.size())
	{
		this->setDir(distance[rand() % distance.size()].first);
	}
	else if (this->current == dirType::none) /*���� ���������� ������� �������*/
	{
		this->setDir(dirType(rand() % 5));
	}
}

void Ghost::updateDirMin(const Map* map, const float& dt)
{
	distanceType distance;
	this->updateDirBase(distance, map, dt);

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

void Ghost::updateMoveGhost(const Map* map, const float& dt)
{
	if (this->mode == modeType::frightened)
	{
		/*���������� �������� � ��������� �������*/
		this->updateDirRand(map, dt);
	}
	else
	{
		/*���������� ����������� �������� �� ������� �����*/
		this->updateDirMin(map, dt);
	}

	/*��������*/
	this->updateMove(map, dt);

	/*���� ����� �� ������*/
	if (this->mode == modeType::toHome && this->isMoveDone())
	{
		this->setMode(modeType::chase);
		this->setDir(dirType::left);
	}
}

void Ghost::updateAnimation(const float& dt)
{
	switch (this->current)
	{
	case dirType::left:
		this->animationComponent->play("horizontal", dt);
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(28.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}
		break;
	case dirType::right:
		this->animationComponent->play("horizontal", dt);
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		break;
	case dirType::up:
		this->animationComponent->play("up", dt);
		break;
	case dirType::down:
		this->animationComponent->play("down", dt);
		break;
	case dirType::none:
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const Ghost::modeType& mode)
{
	switch (mode)
	{
	case Ghost::modeType::chase:
		os << "chase";
		break;
	case Ghost::modeType::frightened:
		os << "frightened";
		break;
	case Ghost::modeType::inHome:
		os << "inHome";
		break;
	case Ghost::modeType::toHome:
		os << "toHome";
		break; 
	case Ghost::modeType::scatter:
		os << "scatter";
		break;
	}
	return os;
}
