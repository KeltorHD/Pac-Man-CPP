#ifndef GAME_H

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::map<std::string, int> supportedKeys;

	/*Initialization*/
	void initVariables();
	void initWindow();
	void initKeys();

public:
	Game();
	~Game();

	/*update*/
	void updateDt();
	void updateSFMLEvents();
	void update();

	/*render*/
	void render();

	/*core*/
	void run();
};

#endif // !GAME_H