#ifndef MAINMENU_H_

#define MAINMENU_H_

#include <windows.h>
#include <winuser.h>
#include <vector>
#include <string>
#include "util.hpp"


extern std::vector<RECT> main_menu_objects; //0 - Main Menu Window, 1 - 1st Word, 2 - 2nd word
extern std::vector<RECT> esc_menu_objects; //0 - Main Menu Window, 

extern const std::string esc_menu_words[1];

extern int word_highlighted;

void init_mainmenu();

void paint_mainmenu(HWND hwnd, bool isMainMenu);

void paint_escmenu(HWND hwnd);




#endif