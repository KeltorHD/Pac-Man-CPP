#include "stdafx.h"
#include "entity.h"

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	/*this->hitboxComponent->render(*target);*/
}

Entity::Entity(float speed, dirType current, dirType next)
{
	this->speed = speed;
	this->current = current;
	this->next = next;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
}

Entity::~Entity()
{
}

void Entity::setDir(dirType dir)
{
	if (this->current == dirType::none)
		this->current = dir;
	else if (this->current != dir)
		this->next = dir;
}

void Entity::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::clearDir()
{
	this->current = this->next;
	this->next = dirType::none;
}

void Entity::clearDir(dirType dir)
{
	this->current = dir;
	this->next = dirType::none;
}

const dirType& Entity::getCurDir() const
{
	return this->current;
}

const dirType& Entity::getNextDir() const
{
	return this->next;
}

const sf::Vector2f Entity::getCenterPosition() const
{
	return sf::Vector2f
	(
		this->hitboxComponent->getPosition().x + TILE_WIDTH / 2,
		this->hitboxComponent->getPosition().y + TILE_WIDTH / 2
	);
}

const sf::Vector2f& Entity::getPosition() const
{
	return this->hitboxComponent->getPosition();
}

const sf::Vector2f Entity::getPosition(const dirType& dir) const
{
	switch (dir)
	{
	case dirType::left:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y);
	case dirType::right:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + TILE_WIDTH,
			this->hitboxComponent->getPosition().y);
	case dirType::up:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y);
	case dirType::down:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y + TILE_WIDTH);
	case dirType::none:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y);
	}
	return sf::Vector2f();
}

const sf::Vector2f Entity::getNextPosition(const float& dt) const
{
	return this->getNextPosition(this->current, dt);
}

const sf::Vector2f Entity::getNextPosition(const dirType& dir, const float& dt) const
{
	switch (dir)
	{
	case dirType::left:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x - dt * this->speed,
			this->hitboxComponent->getPosition().y + TILE_WIDTH / 2);
	case dirType::right:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + TILE_WIDTH + dt * this->speed,
			this->hitboxComponent->getPosition().y + TILE_WIDTH / 2);
	case dirType::up:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + TILE_WIDTH / 2,
			this->hitboxComponent->getPosition().y - dt * this->speed);
	case dirType::down:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + TILE_WIDTH / 2,
			this->hitboxComponent->getPosition().y + TILE_WIDTH + dt * this->speed);
	case dirType::none:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y);
	}
	return sf::Vector2f();
}

void Entity::updateMove(const Map* map, const float& dt)
{
	int next_x = int(this->getNextPosition(this->next, dt).x);
	int next_y = int(this->getNextPosition(this->next, dt).y);

	/*проверка: можно ли изменить направление движения*/
	if (this->next != dirType::none)
	{
		/*проверка: следующая позиция - не стена?*/
		if (!map->isWall
		(
			next_x / TILE_WIDTH,
			next_y / TILE_WIDTH
		))
		{
			/*проверяем, достаточно ли мы близко к повороту*/
			bool isChange = false;
			switch (this->next)
			{
			case dirType::left:
			case dirType::right:
				if (int(this->getPosition().y) % TILE_WIDTH == 0)
					isChange = true;
				break;
			case dirType::up:
			case dirType::down:
				if (int(this->getPosition().x) % TILE_WIDTH == 0)
					isChange = true;
				break;
			}
			if (isChange)
			{
				this->moveToBorder(); /*сдвигаемся к границе плитки*/
				this->clearDir();
			}
		}
	}

	/*проверка: можно ли продолжать движение в текущую сторону*/
	if (this->current != dirType::none)
	{
		/*если следующая позиция игрока находится в стене*/
		if (map->isWall
		(
			int(this->getNextPosition(dt).x / TILE_WIDTH),
			int(this->getNextPosition(dt).y / TILE_WIDTH)
		))
		{
			this->moveToBorder(); /*сдвигаемся к границе плитки*/
			this->clearDir();
		}
		else
		{
			this->move(dt);
		}
	}
}

void Entity::move(const float& dt)
{
	if (this->current != dirType::none)
	{
		switch (this->current)
		{
		case dirType::left:
			this->hitboxComponent->move(-dt * this->speed, 0);
			break;
		case dirType::right:
			this->hitboxComponent->move(dt * this->speed, 0);
			break;
		case dirType::up:
			this->hitboxComponent->move(0, -dt * this->speed);
			break;
		case dirType::down:
			this->hitboxComponent->move(0, dt * this->speed);
			break;
		}
	}
}

void Entity::moveToBorder()
{
	switch (this->current)
	{
	case dirType::left:
		this->hitboxComponent->setPosition
		(
			float(int(this->hitboxComponent->getPosition().x / TILE_WIDTH) * TILE_WIDTH),
			this->hitboxComponent->getPosition().y
		);
		break;
	case dirType::right:
		this->hitboxComponent->setPosition
		(
			float((int(this->hitboxComponent->getPosition().x) % TILE_WIDTH > 0) ?
				((int(this->hitboxComponent->getPosition().x / TILE_WIDTH) + 1) * TILE_WIDTH) :
				(int(this->hitboxComponent->getPosition().x / TILE_WIDTH) * TILE_WIDTH)),
			this->hitboxComponent->getPosition().y
		);
		break;
	case dirType::up:
		this->hitboxComponent->setPosition
		(
			float(int(this->hitboxComponent->getPosition().x / TILE_WIDTH) * TILE_WIDTH),
			float(int(this->hitboxComponent->getPosition().y / TILE_WIDTH) * TILE_WIDTH)
		);
		break;
	case dirType::down:
		this->hitboxComponent->setPosition
		(
			float(int(this->hitboxComponent->getPosition().x / TILE_WIDTH) * TILE_WIDTH),
			float((int(this->hitboxComponent->getPosition().y) % TILE_WIDTH > 0) ?
				((int(this->hitboxComponent->getPosition().y / TILE_WIDTH) + 1) * TILE_WIDTH) :
				(int(this->hitboxComponent->getPosition().y / TILE_WIDTH) * TILE_WIDTH))
		);
		break;
	}
}