#ifndef MOUSEEVENTS_H_

#define MOUSEEVENTS_H_

#include <windows.h>
#include <winuser.h>
#include <string>
#include <vector>
#include "util.hpp"
#include "MainMenu.hpp"
#include "LevelLoader.hpp"

extern LevelLoader *current_level;

void mouse_move(HWND hwnd);

void mouse_click(HWND hwnd);

void load_level_button(HWND hwnd);


#endif