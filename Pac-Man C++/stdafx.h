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

#define NOT_UP_CELL_X1 12 /*�������, � ������� ���������� �� ����� ����� �����*/
#define NOT_UP_CELL_X2 15
#define NOT_UP_CELL_Y1 14
#define NOT_UP_CELL_Y2 26

#define OUT_HOME_POS_X 216.f
#define OUT_HOME_POS_Y 224.f

#define BLINKY_SPEED 75.f /*�������� ������*/
#define PINKY_SPEED 65.f /*�������� �����*/
#define CLYDE_SPEED 75.f /*�������� ������*/
#define INKY_SPEED 75.f /*�������� ����*/

#define BLINKY_POS_X 210.f /*��������� ������� ������*/
#define BLINKY_POS_Y 218.f
#define PINKY_POS_X 210.f /*��������� ������� �����*/
#define PINKY_POS_Y 266.f
#define CLYDE_POS_X 242.f /*��������� ������� ������*/
#define CLYDE_POS_Y 266.f
#define INKY_POS_X 178.f /*��������� ������� ����*/
#define INKY_POS_Y 266.f

/*����� �������� ������*/
#define FRIGHTENED_TIME 5.f /*���� ������*/

/*����� �� ���*/
#define POINT_EAT 10
/*����� �� ����������*/
#define POINT_ENER 50
/*����� �� ����������*/
#define POINT_GHOST 200

#define GAME_TITLE "Pac-Man C++"

/*Core*/
#include <iostream>
#include <stack>
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

/*��������������� �� �����������*/
bool isPerpendicularDir(const dirType& d1, const dirType& d2);

/*��������� ����������������� �����������*/
dirType getPerpendicularDir(const dirType& dir);

/*��������� ���������������� �����������*/
dirType getOppositeDir(const dirType& dir);

/*��������� ���������� ������ �� �����������. ����� x-TILE_WIDTH, ����� y-TILE_WIDTH*/
sf::Vector2i getNextCoordWidthDir(const sf::Vector2i& point, const dirType& dir, const int i = 1);

/*��������� ���������� ������ �� �����������. ����� x-TILE_WIDTH, ����� y-TILE_WIDTH*/
sf::Vector2f getNextCoordWidthDir(const sf::Vector2f& point, const dirType& dir, const int i = 1);

/*�������������� sf::Vector2i � sf::Vector2f*/
sf::Vector2f conversion(const sf::Vector2i& point);

/*Debug output*/
std::ostream& operator<<(std::ostream& os, const dirType& dir);

#endif // !HEADER_H