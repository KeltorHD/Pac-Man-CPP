#include "stdafx.h"
#include "game.h"

int main()
{
    /*Задание сида для гпсч*/
    srand(unsigned(time(NULL)));

    try
    {
        Game game;

        game.run();

        return 1;
    }
    catch (const char * error)
    {
        std::ofstream ofs;
        ofs.open("error.txt");
        ofs << error;
        ofs.close();
        return 0;
    }
}