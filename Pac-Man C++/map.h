#pragma once

class Map
{
public:
	enum class tileType
	{
		wall = 0,       /*�����*/
		free = 1,       /*��������� ������*/
		food = 2,       /*���*/
		energizere = 3, /*�����������*/
	};

	Map();
	~Map();

	/*accessors*/
	const size_t& getCountEat() const; /*���������� ���������� ����� � ����*/

	/*func*/
	bool isGhostUp(const int& cell_x, const int& cell_y) const; /*����� �� ���������� � ���� ������ ����� �����*/
	bool isMove(const dirType& dir, const int& x, const int& y) const;
	bool isWall(const int& x, const int& y) const; /*����� ��*/
	bool isEqual(const sf::Vector2f& one, const sf::Vector2f& two);
	void reload(); /*����� ����� ����� ����������� ������*/
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2) const; /*��������� ���������� ����� ����� �������*/

	int updateFood(const sf::Vector2f& playerPos); /*���������� ����, 1 - �����, 2 - �����������, 0 - ������*/
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