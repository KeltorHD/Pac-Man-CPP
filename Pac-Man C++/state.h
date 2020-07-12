#pragma once

class State
{
protected:
	std::stack<State*>* states;

	const std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosWindow;


	/*func*/

public:
	State(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//accessors
	const bool& getQuit() const;
	const bool getKeyTime();

	//func
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePosition(sf::RenderTarget* target);
	virtual void updateKeyTime(const float& dt);
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};