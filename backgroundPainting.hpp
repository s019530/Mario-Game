#include <iostream>
#include <windows.h>
#include <winuser.h>

int generateNumber(int offset, int max);

void generateClouds();

void paintGround(HWND hwnd);

void paintClouds(HWND hwnd);

void paintBlueSkyBackground(HWND hwnd);

void paintCharacter(HWND hwnd);

void move_char(int i);