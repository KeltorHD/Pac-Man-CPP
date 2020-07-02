#ifndef HEADER_H
#define HEADER_H

/*defines*/
#define GAME_WIDTH 448
#define GAME_HEIGHT 576
#define GAME_COL 28
#define GAME_ROW 36
#define TILE_WIDTH 16
#define START_POS_X 212
#define START_POS_Y 412
#define GAME_TITLE "Pac-Man C++"

/*Core*/
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

/*SFML*/
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>

/*enum*/
enum class dirType
{
	left,
	right,
	up,
	down,
	none
};

#endif // !HEADER_H