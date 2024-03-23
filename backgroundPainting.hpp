#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <vector>
#include <string>
#include <algorithm>

#include <thread>

const int block_size = 250;
const int char_width = 20;
const int window_width = 1200;
const int char_move_speed = 10;
const int char_height = 50;

static bool isJumping = false;

typedef enum type_of_movement{
    WALK,
    JUMP,
    JUMP_START,
    FREE_FALL,
    SET_POS_Y,
    SET_POS_X
}type_of_movement;

typedef enum type_of_collision{
    UNDER,
    SIDE,
    TOP,
    ALL
}type_of_collision;

void initLevel();

void paintAllObjects(HWND hwnd);

void paintBlueSkyBackground(HWND hwnd);

void paintCharacter(HWND hwnd);

void move_char(int i, type_of_movement movement_type);

bool check_collison(type_of_collision collision_type);

void jumpControl(bool skip_jump);

void restartGame();

void mouseButton(HWND hwnd);
