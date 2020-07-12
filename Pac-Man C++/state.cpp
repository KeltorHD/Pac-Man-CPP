#include "stdafx.h"
#include "state.h"

State::State(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->paused = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
}

State::~State()
{

}

/*accessors*/
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

/*func*/
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}


void State::updateMousePosition(sf::RenderTarget* target)
{
	if (dynamic_cast<sf::Window*>(target))
		this->mousePosWindow = sf::Mouse::getPosition(*dynamic_cast<sf::Window*>(target));
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 50.f * dt;
}