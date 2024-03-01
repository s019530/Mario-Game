#include <iostream>
#include <windows.h>
#include <winuser.h>

#include <thread>

static bool isJumping = false;

typedef enum type_of_movement{
    WALK,
    JUMP,
    JUMP_START
}type_of_movement;

int generateNumber(int offset, int max);

void generateClouds();

void paintGround(HWND hwnd);

void paintClouds(HWND hwnd);

void paintBlueSkyBackground(HWND hwnd);

void paintCharacter(HWND hwnd);

void move_char(int i, type_of_movement movement_type);

void jumpControl();
