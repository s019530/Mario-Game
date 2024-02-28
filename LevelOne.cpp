#include "LevelOne.hpp"
#include "backgroundPainting.hpp"


void levelOneSetup(HWND hwnd)
{
    paintBlueSkyBackground(hwnd);
}

void levelOneKeyHandler(HWND hwnd, WPARAM wparam)//pos moves forward, neg moves backwards
{
    if(wparam == 65)
    {
        move_char(10);
        paintBlueSkyBackground(hwnd);
        paintCharacter(hwnd);
    }
    if(wparam == 68)
    {
        std::cout << "d" << std::endl;
        move_char(-10);
        paintBlueSkyBackground(hwnd);
        paintCharacter(hwnd);
    }
}


void drawLevelOne(HWND hwnd)
{

}   

