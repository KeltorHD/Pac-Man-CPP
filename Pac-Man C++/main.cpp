#include "stdafx.h"
#include "game.h"

int main()
{
    /*������� ���� ��� ����*/
    srand(unsigned(time(NULL)));

    Game game;

    game.run();

    return 0;
}