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

#define COUNT_EAT 240
#define COUNT_ENERGIZERE 4

#define LIFES_POS_X 36
#define LIFES_POS_Y 548

#define PLAYER_WIDTH 24
#define GHOST_WIDTH 28

#define NOT_UP_CELL_X1 12 /*позиции, в которых привидение не может пойти вверх*/
#define NOT_UP_CELL_X2 15
#define NOT_UP_CELL_Y1 14
#define NOT_UP_CELL_Y2 26

#define BLINKY_POS_X 210.f /*начальная позиция блинки*/
#define BLINKY_POS_Y 218.f

/*время действия страха*/
#define FRIGHTENED_TIME 5.f /*пять секунд*/

#define GAME_TITLE "Pac-Man C++"

/*Core*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

/*SFML*/
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

/*enum*/
enum class dirType
{
	left,
	right,
	up,
	down,
	none
};

/*перпендикулярны ли направления*/
bool isPerpendicularDir(const dirType& d1, const dirType& d2);

/*получение перпендикулярного направления*/
dirType getPerpendicularDir(const dirType& dir);

/*получение противоположного направления*/
dirType getOppositeDir(const dirType& dir);

/*получение координаты ячейки по направлению. Влево x-1, вверх y-1*/
sf::Vector2i getNextCoordWidthDir(const sf::Vector2i& point, const dirType& dir);

/*преобразование sf::Vector2i к sf::Vector2f*/
sf::Vector2f conversion(const sf::Vector2i& point);

/*Debug output*/
std::ostream& operator<<(std::ostream& os, const dirType& dir);

#endif // !HEADER_H