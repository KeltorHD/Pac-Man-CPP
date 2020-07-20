#include "stdafx.h"
#include "ghost.h"

sf::Texture Ghost::frightenedTexture; /*инициализация статической текстуры*/
sf::Texture Ghost::toHomeTexture; /*инициализация статической текстуры*/
Ghost::patternMode Ghost::pattern; /*инициализация статического вектора*/

Ghost::Ghost(const sf::Color& color, const float pos_x, const float pos_y, const float speed)
	: Entity(speed, dirType::left, dirType::none)
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

const Ghost::modeType& Ghost::getMode() const
{
	return this->mode;
}

const bool Ghost::isMoveDone() const
{
	return int(this->getCenterPosition().x) == int(this->targetCell.x)
		&& int(this->getCenterPosition().y) == int(this->targetCell.y);

}

const bool Ghost::isFrightened() const
{
	return this->mode == modeType::frightened;
}

const bool Ghost::isNotMatherial() const
{
	return (this->mode == modeType::inHome 
		|| this->mode == modeType::toHome 
		|| this->mode == modeType::outHome);
}

void Ghost::setModeFrightened()
{
	if (this->mode != modeType::frightened && this->mode != modeType::toHome
		&& this->mode != modeType::inHome && this->mode != modeType::outHome)
	{
		/*изменяем направление на противоположное*/
		this->current = getOppositeDir(this->current);

		this->animationComponent->setTextureSheet(this->frightenedTexture);
		this->mode = modeType::frightened;

		/*обнуляем таймер*/
		this->frigthetenedTimer = 0.f;
	}
}

void Ghost::setModeToHome() 
{
	if (this->mode != modeType::toHome)
	{
		/*изменяем направление на противоположное*/
		this->current = getOppositeDir(this->current);
		this->animationComponent->setTextureSheet(this->toHomeTexture);
		this->mode = modeType::toHome;
	}
}

void Ghost::setMode(modeType mode)
{
	if (this->mode == modeType::toHome)
	{
		/*если дошли до домика*/
		if (this->isMoveDone() && mode != modeType::toHome)
		{
			this->animationComponent->setTextureSheet(this->baseTexture);
			this->mode = mode;
		}
	}
	else
	{
		if (this->mode != mode)
		{
			/*меняем направление на противоположное*/
			this->current = getOppositeDir(this->current);

			/*выставляем обычную текстуру*/
			this->animationComponent->setTextureSheet(this->baseTexture);

			this->mode = mode;
		}
	}
}

void Ghost::updateHouse(const Map* map)
{
}

void Ghost::loadStaticVar()
{
	if (!Ghost::frightenedTexture.loadFromFile("Images/frightened.png"))
		throw "NOT COULD LOAD FRIGHTENED IMAGE";
	if (!Ghost::toHomeTexture.loadFromFile("Images/to_home.png"))
		throw "NOT COULD LOAD TOHOME IMAGE";

	Ghost::loadPatternFromFile();
}

void Ghost::reloadPattern(const int& level)
{
	if (level == 2)
	{
		Ghost::pattern[5].second = 1033.f;
		Ghost::pattern[6].second = 0.017f;
	}
	else if (level == 5)
	{
		Ghost::pattern[0].second = 5.f;
		Ghost::pattern[2].second = 5.f;
		Ghost::pattern[5].second = 1037.f;
		Ghost::pattern[6].second = 0.017f;
	}
}

void Ghost::reload(const int& level)
{
	this->current = dirType::none;
	this->next = dirType::none;
	this->animationComponent->setTextureSheet(this->baseTexture);
	this->patternCounter = 0;
	this->patternTimer = 0.f;

	if (level <= 21)
		this->speed += 0.5f;
}

void Ghost::update(const Map* map, const Player* player, const float& dt)
{
	this->updateTimers(dt); /*обновление таймеров*/
	this->updateTargetcell(player, map); /*обновление целевой точки*/
	this->updateMoveGhost(map, dt); /*обновление движения*/
	this->updateHouseMove(map, dt); /*обновление движения выход из домика*/
	this->hitboxComponent->update(); /*перемещение спрайта вслед за хитбоксом*/
	this->updateAnimation(dt); /*обновление анимации*/
}

void Ghost::loadPatternFromFile()
{
	std::ifstream ifs;
	ifs.open("Config/patternMode.ini");
	if (!ifs.is_open())
		throw "NOT COULD LOAD PATTERNMODE.ini";

	Ghost::pattern.clear();
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

void Ghost::updateHouseMove(const Map* map, const float& dt)
{
	this->updateHouse(map);

	if (this->mode == modeType::outHome)
	{
		/*сначала выравниваем привидение по x*/
		if (this->getPosition().x != OUT_HOME_POS_X)
		{
			/*если привидение левее*/
			if (this->getPosition().x < OUT_HOME_POS_X)
			{
				this->current = dirType::right;
				if (this->getNextPosition(dt).x < OUT_HOME_POS_X + TILE_WIDTH)
				{
					this->move(dt);
				}
				else
				{
					this->hitboxComponent->setPosition(OUT_HOME_POS_X, this->getPosition().y);
				}
			}
			else
			{
				this->current = dirType::left;
				if (this->getNextPosition(dt).x > OUT_HOME_POS_X - TILE_WIDTH)
				{
					this->move(dt);
				}
				else
				{
					this->hitboxComponent->setPosition(OUT_HOME_POS_X, this->getPosition().y);
				}
			}
		}
		else if (this->getPosition().y != OUT_HOME_POS_Y) /*выравниваем по y*/
		{
			this->current = dirType::up;
			if (this->getNextPosition(dt).y > OUT_HOME_POS_Y)
			{
				this->move(dt);
			}
			else
			{
				this->hitboxComponent->setPosition(OUT_HOME_POS_X, OUT_HOME_POS_Y);
			}
		}
		else
		{
			this->setMode(this->pattern[this->patternCounter].first);
			this->current = dirType::left;
		}
	}
}

void Ghost::initSprite(const sf::Color& color, const float pos_x, const float pos_y)
{
	sf::Image imageGhost; /*изображение привидения*/
	if (!imageGhost.loadFromFile("Images/ghost.png"))
		throw "NOT COULD LOAD GHOST IMAGE";

	/*перекрашивание общей текстуры*/
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

	/*добавление анимаций*/
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
	/*центр следующей позиции привидения по текущему направлению*/
	sf::Vector2i next = 
	{
		(int(this->getNextPosition(this->current, dt).x) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2,
		(int(this->getNextPosition(this->current, dt).y) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2
	};

	/*следующая позиция стена?*/
	if (!map->isWall
	(
		next.x / TILE_WIDTH,
		next.y / TILE_WIDTH
	))
	{
		/*
		Находим из всех доступных сторон для движения ту, которая наиболее
		близка к целевой точке и не обратна к текущей стороне движения.
		Если число свободных путей равно 3-м, то не можем пойти наверх.
		Если все доступные пути равнозначно близки к целевой точке, то
		приоритеты располагаются таким образом:
		верхняя > левая > нижняя
		*/
		dirType cur = this->current; /*проверяемое направление*/

		/*Первое направление*/
		sf::Vector2i tmpPos = getNextCoordWidthDir(next, cur);
		/*если следующая позиция по этому направлению не стена*/
		if (!map->isWall
		(
			tmpPos.x / TILE_WIDTH,
			tmpPos.y / TILE_WIDTH
		))
		{
			distance.push_back({ cur, map->distance(static_cast<sf::Vector2f>(tmpPos), this->targetCell) });
		}

		/*второе направление*/
		cur = getPerpendicularDir(cur); /*перпендикулярное направление*/
		tmpPos = getNextCoordWidthDir(next, cur);
		/*если следующая позиция по этому направлению не стена*/
		if (!map->isWall
		(
			tmpPos.x / TILE_WIDTH,
			tmpPos.y / TILE_WIDTH
		))
		{
			distance.push_back({ cur, map->distance(static_cast<sf::Vector2f>(tmpPos), this->targetCell) });
		}

		/*третье направление*/
		cur = getOppositeDir(cur); /*противоположное перпендикулярному направлению*/
		tmpPos = getNextCoordWidthDir(next, cur);
		/*если следующая позиция по этому направлению не стена*/
		if (!map->isWall
		(
			tmpPos.x / TILE_WIDTH,
			tmpPos.y / TILE_WIDTH
		))
		{
			distance.push_back({ cur, map->distance(static_cast<sf::Vector2f>(tmpPos), this->targetCell) });
		}

	}
}

void Ghost::updateTimers(const float& dt)
{
	/*проверки по таймеру страха*/
	if (this->mode == modeType::frightened)
	{
		this->frigthetenedTimer += dt;

		if (this->frigthetenedTimer >= FRIGHTENED_TIME)
		{
			this->setMode(modeType::chase);
		}
	}
	else if (
		this->mode != modeType::inHome 
		&& this->mode != modeType::toHome
		&& this->mode != modeType::outHome)
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

	/*выбор направления рандомно*/
	if (distance.size())
	{
		this->setDir(distance[rand() % distance.size()].first);
	}
}

void Ghost::updateDirMin(const Map* map, const float& dt)
{
	distanceType distance;
	this->updateDirBase(distance, map, dt);

	/*выбор направления по наименьшему расстоянию*/
	if (distance.size())
	{
		/*обработка особых клеток*/
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
	if (this->mode == modeType::inHome)
		return;
	if (this->mode == modeType::outHome)
		return;

	float koef;

	if (this->mode == modeType::frightened)
	{
		/*обновление движения в рандомную сторону*/
		this->updateDirRand(map, dt);
		koef = 0.7f;
	}
	else
	{
		/*обновление направления движения по целевой точке*/
		this->updateDirMin(map, dt);
		
		/*если идем к домику - скорость в 1.5 раза больше*/
		if (this->mode == modeType::toHome)
			koef = 1.5f;
		else
			koef = 1.f;
	}

	if (this->current == dirType::none) /*если привидение немного встряло*/
	{
		this->setDir(dirType(rand() % 5));
	}
 
	if (int(this->getNextPosition(dt).y) / TILE_WIDTH == TELEPORT_POS_Y
		&& ((int(this->getNextPosition(dt).x) / TILE_WIDTH <= 2) || (int(this->getNextPosition(dt).x) / TILE_WIDTH >= GAME_COL - 2)))
	{
		koef = 0.5f;
	}

	/*движение*/
	this->updateMove(map, dt, koef);

	/*если дошли до домика*/
	if (this->mode == modeType::toHome && this->isMoveDone())
	{
		this->setMode(this->pattern[this->patternCounter].first);
		this->current = dirType::left;
	}
}

void Ghost::updateAnimation(const float& dt)
{
	if (this->mode == modeType::inHome)
		return;

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
	case Ghost::modeType::outHome:
		os << "outHome";
		break;
	}
	return os;
}
