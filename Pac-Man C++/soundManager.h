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
	void setAllVolume(float volume);
	void setVolume(std::string name, float volume);
	
	/*play*/
	void play(std::string name);

	/*stop*/
	void stop(std::string name);

	/*isPlyaing*/
	bool isPlaying(std::string name);
};