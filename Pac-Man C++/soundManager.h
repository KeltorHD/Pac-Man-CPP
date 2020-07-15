#pragma once

class SoundManager
{
private:
	std::map<std::string, sf::SoundBuffer> buffer;
	std::map<std::string, sf::Sound> sound;

public:
	SoundManager();
	~SoundManager();

	/*load sound*/
	bool loadSound(std::string name);

	/*set Volume*/
	void setVolume(float volume);
	
	/*play*/
	void play(std::string name);
};