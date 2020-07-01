#ifndef MAP_H

class Map
{
public:
	enum class tileType
	{
		free,       /*свободная клетка*/
		food,       /*еда*/
		energizere, /*энерджайзер*/

		wall        /*стена*/
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