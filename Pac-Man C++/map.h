#pragma once

class Map
{
public:
	enum class tileType
	{
		wall = 0,       /*стена*/
		free = 1,       /*свободная клетка*/
		food = 2,       /*еда*/
		energizere = 3, /*энерджайзер*/
	};

	Map();
	~Map();

	/*accessors*/
	const size_t& getCountEat() const; /*количество оставшихся точек с едой*/

	/*func*/
	bool isGhostUp(const int& cell_x, const int& cell_y) const; /*может ли привидения в этой клетке пойти вверх*/
	bool isMove(const dirType& dir, const int& x, const int& y) const;
	bool isWall(const int& x, const int& y) const; /*стена ли*/
	bool isEqual(const sf::Vector2f& one, const sf::Vector2f& two);
	void reload(); /*сброс карты после прохождения уровня*/
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2) const; /*получение расстояния между двумя точками*/

	int updateFood(const sf::Vector2f& playerPos); /*обновление пищи, 1 - точка, 2 - энерджайзер, 0 - ничего*/
	void render(sf::RenderTarget* target);
private:
	/*map*/
	sf::Texture mapTexture;
	tileType tiles[GAME_ROW][GAME_COL];
	sf::Sprite map;

	/*food, ener*/
	sf::Texture food_ener;
	sf::Sprite foodSprite;
	size_t eat;
	size_t ener;
	sf::Sprite energizereSprite;

	/*init*/
	void initVar();
	void initTiles();
	void initSprites();

	/*func*/
	void renderFood(sf::RenderTarget* target);
};