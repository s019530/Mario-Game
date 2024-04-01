#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <string>
#include <vector>
#include "LevelLoader.hpp"

extern HFONT menuFontNormal;
extern HFONT menuFontBig;

extern HBRUSH skyBlue;
extern HBRUSH white;
extern HBRUSH black;
extern HBRUSH green;
extern HBRUSH brown;

extern int state_of_game;
extern int previous_state_of_game;

typedef enum gameState{
    MAINMENU, 
    LOADED_LEVEL,
    CREATE_LEVEL
}gameState;


typedef enum CUSTOM_KEY{
    CK_A = 65,
    CK_W = 87,
    CK_D = 68,
    CK_ONE = 49,
    CK_ESC = VK_ESCAPE,
    CK_SPACE = VK_SPACE,
    CK_LEFT_MOUSE =  1
}CUSTOM_KEY;

bool isKeyDown(CUSTOM_KEY key);

int generateNumber(int offset, int max);

std::vector<std::string> split(std::string input, char delim);

RECT createRectUsingCords(RECT rect, int size_width, int size_height);

bool mouseInBox(RECT rect, POINT pt);

#endif