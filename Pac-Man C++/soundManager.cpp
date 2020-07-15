#include "stdafx.h"
#include "soundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

bool SoundManager::loadSound(std::string name)
{
	if (this->buffer[name].loadFromFile("Sounds/" + name + ".wav"))
	{
		this->sound[name].setBuffer(this->buffer[name]);
		return true;
	}
	return false;
}

void SoundManager::setVolume(float volume)
{
	for (auto& i : this->sound)
	{
		i.second.setVolume(volume);
	}
}

void SoundManager::play(std::string name)
{
	this->sound[name].play();
}