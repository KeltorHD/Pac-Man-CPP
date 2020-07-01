#ifndef MAP_H

class Map
{
public:
	enum class tileType
	{
		free,       /*��������� ������*/
		food,       /*���*/
		energizere, /*�����������*/

		wall        /*�����*/
	};

	Map();
	~Map();

	/*func*/
	void render(sf::RenderTarget* target);
private:
	sf::Texture mapTexture;
	sf::Sprite mapSprite;
};


#endif // ! MAP_H