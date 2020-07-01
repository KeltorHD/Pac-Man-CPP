#include "stdafx.h"
#include "map.h"

Map::Map()
{
	mapTexture.loadFromFile("Images/map.png");
	mapSprite.setTexture(mapTexture);
}

Map::~Map()
{
}

void Map::render(sf::RenderTarget* target)
{
	target->draw(mapSprite);
}
