#include <iostream>
#include <windows.h>
#include <winuser.h>

#include <thread>

#define block_size 250;
const int char_width = 20;
const int window_width = 1200;

static bool isJumping = false;

typedef enum type_of_movement{
    WALK,
    JUMP,
    JUMP_START,
    FREE_FALL,
    SET_POS
}type_of_movement;

typedef enum type_of_collision{
    UNDER,
    SIDE,
    TOP,
    ALL
}type_of_collision;

void generateClouds();

void generateGround();

void paintGround(HWND hwnd);

void paintClouds(HWND hwnd);

void paintBlueSkyBackground(HWND hwnd);

void paintCharacter(HWND hwnd);

void move_char(int i, type_of_movement movement_type);

bool check_collison(type_of_collision collision_type);

void jumpControl(bool skip_jump);
