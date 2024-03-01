#include "LevelOne.hpp"
#include "backgroundPainting.hpp"
#include "util.hpp"

void levelOneSetup(HWND hwnd)
{
    paintBlueSkyBackground(hwnd);
}

void levelOneKeyHandler(HWND hwnd, int wparam)//pos moves forward, neg moves backwards
{
    if(wparam == CK_A)
    {
        move_char(10, WALK);
        paintBlueSkyBackground(hwnd);
        paintCharacter(hwnd);
    }
    if(wparam == CK_D)
    {
        std::cout << "d" << std::endl;
        move_char(-10, WALK);
        paintBlueSkyBackground(hwnd);
        paintCharacter(hwnd);
    }
    if(wparam == CK_W)
    {
        std::cout << "w" << std::endl;
        move_char(0, JUMP_START);

        if(isKeyDown(CK_D)){
            move_char(-10, WALK);
        }
        else if(isKeyDown(CK_A))
        {
            move_char(10, WALK);
        }

        paintBlueSkyBackground(hwnd);
        paintCharacter(hwnd);
    }
}


void drawLevelOne(HWND hwnd)
{

}   

