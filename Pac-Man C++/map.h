#ifndef MAP_H

#include "entity.h"

class Map
{
public:
	enum class tileType
	{
		free = 1,       /*свободная клетка*/
		food = 2,       /*еда*/
		energizere = 3, /*энерджайзер*/

		wall = 0        /*стена*/
	};

	Map();
	~Map();

	/*func*/
	bool isMove(const dirType& dir, const int& x, const int& y);
	bool isWall(const int& x, const int& y);

	void update(const float& dt);
	void render(sf::RenderTarget* target);
private:
	/*map*/
	sf::Texture mapTexture;
	tileType tiles[GAME_ROW][GAME_COL];
	sf::Sprite map;

	/*food, ener*/
	sf::Texture food_ener;
	sf::Sprite food;
	sf::Sprite energizere;

	/*func*/
	void initTiles();
	void initSprites();
	void updateCollision(Entity* entity, const float& dt);
	void renderFood(sf::RenderTarget* target);
};


#endif // ! MAP_H