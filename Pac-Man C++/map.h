#ifndef MAP_H

class Map
{
public:
	enum class tileType
	{
		free = 1,       /*��������� ������*/
		food = 2,       /*���*/
		energizere = 3, /*�����������*/

		wall = 0        /*�����*/
	};

	Map();
	~Map();

	/*func*/
	void render(sf::RenderTarget* target);
private:
	/*map*/
	sf::Texture mapTexture;
	tileType tiles[GAME_COL][GAME_ROW];
	sf::Sprite map;

	/*food, ener*/
	sf::Texture food_ener;
	sf::Sprite food;
	sf::Sprite energizere;

	void initTiles();
	void initSprites();
};


#endif // ! MAP_H