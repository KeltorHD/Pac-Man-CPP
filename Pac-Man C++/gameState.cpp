#include "stdafx.h"
#include "gameState.h"

static bool chomp_count = true;

void GameState::initVar()
{
	this->level = 1;
}

void GameState::initSoundManager()
{
	this->soundManager = new SoundManager();
	bool isLoad = true;
	if (!this->soundManager->loadSound(CHOMP1))
		isLoad = false;
	if (!this->soundManager->loadSound(CHOMP2))
		isLoad = false;
	if (!this->soundManager->loadSound(FRIGHTENED))
		isLoad = false;
	if (!this->soundManager->loadSound(SIREN))
		isLoad = false;
	if (!this->soundManager->loadSound(START_GAME))
		isLoad = false;
	if (!isLoad)
		throw "NOT COULD LOAD SOUNDS";
	this->soundManager->setAllVolume(30.f);
	this->soundManager->setVolume(FRIGHTENED, 20.f);
	this->soundManager->setVolume(SIREN, 20.f);
	this->soundManager->play(START_GAME);
}

void GameState::initFont()
{
	if (!this->font.loadFromFile("Font/atari.ttf"))
		throw "NOT COULD LOAD FONT";
}

void GameState::initScore()
{
	this->score = 0;
	this->maxScore = 0;

	std::ifstream ifs;
	ifs.open("Config/statistics.st");
	if (!ifs.is_open())
		throw "COULD NOT LOAD STATISTICS";
	ifs >> this->maxScore;
	ifs.close();
}

void GameState::initText()
{
	this->scoreText = new sf::Text(std::to_string(this->score), font, 16);
	this->scoreText->setFillColor(sf::Color(222, 222, 255));
	this->scoreText->setPosition(112, 24);
	this->maxScoreText = new sf::Text(std::to_string(this->maxScore), font, 16);
	this->maxScoreText->setFillColor(sf::Color(222, 222, 255));
	this->maxScoreText->setPosition(336, 24);
}

void GameState::initLoseSprite()
{
	if (!this->loseTexture.loadFromFile("Images/lose.png"))
		throw "COULD NOT LOAD LOSE IMAGE";
	this->loseSprite.setTexture(this->loseTexture);
	this->loseSprite.setPosition(0.f, 3 * 16.f);
}


void GameState::initEssence()
{
	this->map = new Map();
	this->player = new Player();
	Ghost::loadStaticVar(); /*загрузка статических текстур*/
	this->enemy.push_back(new Blinky());
	this->enemy.push_back(new Pinky());
	this->enemy.push_back(new Inky());
	this->enemy.push_back(new Clyde());
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(this->font);
	this->pmenu->addButton(GAME_HEIGHT / 2.f, GAME_WIDTH / 4.f, GAME_HEIGHT / 12.f, 18, "TO MENU");
}

void GameState::updateCollisionEnemies()
{
	for (auto& i : this->enemy)
	{
		if (this->map->isEqual(i->getCenterPosition(), this->player->getCenterPosition()))
		{
			if (i->isFrightened())
			{
				/*добавление очков за съеденное привидение*/
				this->score += this->ghostScore;
				this->ghostScore *= 2;
				i->setModeToHome();
			}
			else if (i->isNotMatherial())
			{
				continue;
			}
			else
			{
				/*reload player, enemies, level--*/
				this->player->reload();
				for (auto& i : this->enemy)
				{
					i->reload(this->level);
				}
				this->player->decLifes(); /*уменьшение жизней*/
				break;
			}
		}
	}
}

void GameState::updateLevel()
{
	if (!this->map->getCountEat())
	{
		/*reload, level++*/
		this->level++;
		this->map->reload();
		this->player->reload();
		Ghost::reloadPattern(this->level);
		for (auto& i : this->enemy)
		{
			i->reload(this->level);
		}
	}
}

void GameState::updateText()
{
	this->scoreText->setString(std::to_string(this->score));
	this->maxScoreText->setString(std::to_string((this->score > this->maxScore) ? this->score : this->maxScore));

	this->scoreText->setOrigin
	(
		this->scoreText->getLocalBounds().left + this->scoreText->getLocalBounds().width / 2.f,
		this->scoreText->getLocalBounds().top
	);
	this->maxScoreText->setOrigin
	(
		this->maxScoreText->getLocalBounds().left + this->maxScoreText->getLocalBounds().width / 2.f,
		this->maxScoreText->getLocalBounds().top
	);
}

/*Constructor*/
GameState::GameState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::RenderWindow* window)
	: State(supportedKeys, states, window)
{
	this->initVar();
	this->initSoundManager();
	this->initFont();
	this->initLoseSprite();
	this->initScore();
	this->initText();
	this->initEssence();
	this->initPauseMenu();
}

GameState::~GameState()
{
	this->saveStats();
	delete this->soundManager;
	delete this->pmenu;
	delete this->map;
	delete this->player;
	for (auto& i : this->enemy)
	{
		delete i;
	}
	delete this->scoreText;
	delete this->maxScoreText;
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed(TO_MENU))
		this->endState();
}

void GameState::updatePlayerInput(const float& dt)
{
	if (this->player->getLives())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys->at("Escape"))) && this->getKeyTime())
		{
			(!this->paused) ? this->pauseState() : this->unpauseState();
		}

		dirType dir = dirType::none;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys->at("W"))))
		{
			dir = dirType::up;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys->at("S"))))
		{
			dir = dirType::down;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys->at("A"))))
		{
			dir = dirType::left;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys->at("D"))))
		{
			dir = dirType::right;
		}

		this->player->updateInput(this->map, dt, dir);
	}
	else
	{
		/*если нажата любая клавиша*/
		for (int i = int(sf::Keyboard::Key::A); i < int(sf::Keyboard::Key::KeyCount); i++)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i)))
			{
				this->reloadGame();
			}
		}
	}
}

void GameState::updateEntity(const float& dt)
{
	this->player->update(this->map, dt);
	if (dynamic_cast<Inky*>(this->enemy[2]))
		dynamic_cast<Inky*>(this->enemy[2])->updateTargetCell(this->player, this->enemy[0]);
	for (auto& i : this->enemy)
	{
		i->update(this->map, this->player, dt);
	}
}

void GameState::updateFrightened()
{
	bool isFrightened = false;
	for (auto& i : this->enemy)
	{
		if (i->isFrightened())
		{
			isFrightened = true;
			break;
		}
	}

	if (isFrightened)
	{
		this->soundManager->stop(SIREN);
		this->soundManager->play(FRIGHTENED);
	}
	else
	{
		this->soundManager->stop(FRIGHTENED);
		this->soundManager->play(SIREN);
		this->ghostScore = POINT_GHOST;
	}
}

void GameState::updateFood()
{
	/*обновление съеденной игроком еды*/
	int swtch = this->map->updateFood(this->player->getPosition());
	if (swtch == 1)
	{
		/*добавление очков*/
		this->score += POINT_EAT;
		this->player->setDecreaseSpeed();
		this->soundManager->play(chomp_count ? CHOMP1 : CHOMP2);
		chomp_count = !chomp_count;
	}
	else if (swtch == 2)
	{
		/*добавление очков*/
		this->score += POINT_ENER;
		/*выставление призракам режима разбегания*/
		for (auto& i : this->enemy)
		{
			i->setModeFrightened();
		}
		this->ghostScore = POINT_GHOST;
	}
}

void GameState::renderText(sf::RenderTarget* target)
{
	target->draw(*this->scoreText);
	target->draw(*this->maxScoreText);
}

void GameState::saveStats()
{
	std::ofstream ofs;
	ofs.open("Config/statistics.st");
	if (!ofs.is_open())
		throw "COULD NOT SAVE STATISTICS";
	ofs << ((this->score > this->maxScore) ? this->score : this->maxScore);
	ofs.close();
	this->maxScore = (this->score > this->maxScore) ? this->score : this->maxScore;
	this->score = 0;
}

void GameState::reloadGame()
{
	this->level = 1;
	this->player->reload();
	this->player->setLifes(2);
	this->map->reload();
	for (auto& i : this->enemy)
	{
		i->reload(this->level);
	}
	this->saveStats();
	this->updateText();
	this->soundManager->play(START_GAME);
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	/*Input*/
	this->updatePlayerInput(dt);

	if (!this->paused)
	{
		if (!this->soundManager->isPlaying(START_GAME))
		{
			if (this->player->getLives())
			{
				/*update entity*/
				this->updateEntity(dt);

				/*collision*/
				this->updateCollisionEnemies();
				this->updateFrightened();

				this->updateFood();
				this->updateLevel();
				this->updateText();
			}
		}
	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render()
{
	/*render items*/
	this->map->render(this->window);
	this->renderText(this->window);
	this->player->render(this->window);
	for (auto& i : this->enemy)
	{
		i->render(this->window);
	}

	if (!this->player->getLives())
	{
		this->window->draw(this->loseSprite);
	}

	if (this->paused)
	{
		this->pmenu->render(this->window);
	}
}