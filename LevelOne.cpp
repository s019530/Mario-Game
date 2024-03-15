#include "LevelOne.hpp"
#include "backgroundPainting.hpp"
#include "util.hpp"

void LevelKeyHandler(HWND hwnd, int wparam)//pos moves forward, neg moves backwards
{
    if(wparam == CK_A)
    {
        move_char(char_move_speed, WALK);
        paintBlueSkyBackground(hwnd);
        paintCharacter(hwnd);
    }
    if(wparam == CK_D)
    {
        move_char(char_move_speed * -1, WALK);
        paintBlueSkyBackground(hwnd);
        paintCharacter(hwnd);
    }
    if(wparam == CK_W)
    {
        move_char(0, JUMP_START);

        if(isKeyDown(CK_D)){
            move_char(char_move_speed * -1, WALK);
        }
        else if(isKeyDown(CK_A))
        {
            move_char(char_move_speed, WALK);
        }

        paintBlueSkyBackground(hwnd);
        paintCharacter(hwnd);
    }
    if(wparam == CK_ONE)
    {
        restartGame();
        std::cout << "game restart";
    }
}

