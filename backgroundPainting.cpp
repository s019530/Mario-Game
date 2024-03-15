#include "backgroundPainting.hpp"
#include "util.hpp"
#include "file_managment.hpp"

HBRUSH skyBlue = CreateSolidBrush(RGB(68,243, 255));
HBRUSH white = CreateSolidBrush(RGB(250,250,250));
HBRUSH black = CreateSolidBrush(RGB(0,0,0));
HBRUSH green = CreateSolidBrush(RGB(0, 250, 0));

bool level_loaded = false;
bool initialCharacter = false;

const int char_right = (window_width / 2) + (char_width/2);
const int char_left = (window_width / 2) - (char_width/2);

std::vector<RECT> clouds;
std::vector<RECT> ground;
//0 - clouds, 1 - ground
std::vector<std::vector<RECT>*> objects_to_be_painted = {&clouds, &ground};

RECT characterRect;

int char_pos = 0;// 590 from the border
int char_y_pos = 100;

void paintClouds(HWND hwnd){
    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);

    for(int i = 0; i != (std::end(clouds) - std::begin(clouds)); i++)
    {
        if((clouds[i].right+char_pos < 0) || (clouds[i].left+char_pos > 1200))
        {   
        }
        else if((clouds[i].left+char_pos < 0) && (clouds[i].right + char_pos > 0)) // left border
        {
            RECT temp = clouds[i];
            
            SetRect(&temp, 0, clouds[i].top, clouds[i].right + char_pos, clouds[i].bottom);

            FillRect(paints.hdc, &temp, white);
        }
        else if((clouds[i].right + char_pos > 1200) && (clouds[i].left + char_pos < 1200))//right border
        {

            RECT temp = clouds[i];
            
            SetRect(&temp, clouds[i].left+char_pos, clouds[i].top, 1200, clouds[i].bottom);

            FillRect(paints.hdc, &temp, white);
        }
        else
        {
            RECT rect;
            rect = clouds[i];
            rect.right = rect.right + char_pos;
            rect.left = rect.left + char_pos;

            FillRect(paints.hdc, &rect, white);
        }
    }

    EndPaint(hwnd, &paints);
}

void paintGround(HWND hwnd)
{

    InvalidateRect(hwnd, NULL, false);
    PAINTSTRUCT paints;
    BeginPaint(hwnd, &paints);

    for(RECT rect : ground)
    {
        if((rect.right+char_pos < 0) || (rect.left+char_pos > 1200))
        {}
        else if((rect.left+char_pos < 0) && (rect.right + char_pos) > 0) // left border
        {
            RECT temp = rect;
            SetRect(&temp, 0, temp.top, temp.right+char_pos, temp.bottom);
            FillRect(paints.hdc, &temp, green);
        }
        else if((rect.right + char_pos > 1200) && (rect.left + char_pos < 1200)) //right border
        {
            RECT temp = rect;
            SetRect(&temp, rect.left+char_pos, rect.top, 1200, rect.bottom);
            FillRect(paints.hdc, &temp, green);
        }
        else
        {
            RECT temp = rect;
            temp.right = temp.right + char_pos;
            temp.left = temp.left + char_pos;

            FillRect(paints.hdc, &temp, green);
        }
    }
    EndPaint(hwnd, &paints);
}

void paintBlueSkyBackground(HWND hwnd)
{

    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);

    if(!level_loaded){
        load_file("levelone", &objects_to_be_painted);
        level_loaded = true;
    }
    
    RECT rect;
    //paint sky
    FillRect(paints.hdc, &paints.rcPaint, skyBlue);

    //paint clouds;
    paintClouds(hwnd);

    //paint ground;
    paintGround(hwnd);

    //paint char;
    if(initialCharacter == false) {
        paintCharacter(hwnd);
        initialCharacter = true;
    }

   
    EndPaint(hwnd, &paints);
}

void paintCharacter(HWND hwnd)
{
    //SetRect(&characterRect, 590, 725 - char_y_pos, 610, 800 - char_y_pos);
    SetRect(&characterRect, char_left, 750 - char_y_pos, char_right, 800 - char_y_pos);

    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);

    FillRect(paints.hdc, &characterRect, black);

    EndPaint(hwnd, &paints);

    if(check_collison(UNDER) == false) {
        move_char(0, FREE_FALL);
    }
}

void move_char(int i, type_of_movement movement_type)
{
    switch(movement_type)
    {
        case(WALK):

            char_pos = char_pos + i;
            if(check_collison(SIDE)){
                char_pos = char_pos - i;
            }
            break;
        case(JUMP):
            char_y_pos += i;
            break;
        case(JUMP_START):
            if(isJumping == false){
                std::thread idc (jumpControl, false);
                idc.detach();
            }
            break;
        case(FREE_FALL):
        {
            if(isJumping == false)
            {
                std::thread idc (jumpControl, true);
                idc.detach();
            }
            break;
        }
        case(SET_POS_Y):
        {
            char_y_pos = i;
            break;
        }
        case(SET_POS_X):
        {
            char_pos = i;
            break;
        }
    }
}

bool check_collison(type_of_collision collision_type)
{
    //check for ground position
    switch(collision_type) {
        case (UNDER):
        {
            if(800 - char_y_pos >= 795){
                move_char(0, SET_POS_Y);
                return true; // hit the floor
            }
            for(RECT g : ground)
            {
                if((g.left + char_pos <= char_left) && (g.right + char_pos >= char_right))
                {
                    if((800 - char_y_pos) < g.top)
                    {
                        return false;//ground is found and you're above it
                    }
                    else if ((800 - char_y_pos) < g.top + 50){ //clips you back up if the bottom of the character is 50 units into the block other wise lets u fall
                        move_char(800 - g.top, SET_POS_Y);
                        return true; //ground is found but ur on the ground
                    }
                }
            }
            return false; //IF NO GROUND IS FOUND AT ALL
        }
        case (SIDE):
        {
            for(RECT g : ground)
            {
                if(((g.left+char_pos) <= char_right) && ((g.right+char_pos) >= char_right))
                {
                    int mid = 800 - (char_y_pos + (char_height/2));
                    std::cout << "block found" << std::endl;
                    std::cout << "left :" + std::to_string(g.left) + " right : " + std::to_string(g.right) + "char pos " + std::to_string(char_pos) + " MID " + std::to_string(mid) << std::endl; 
                    if((mid > g.top) && (mid < g.bottom)) {
                        if(!check_collison(UNDER))
                        {
                            return false;
                        }
                        if(g.top > (800 - char_y_pos)){
                            return false;
                        }
                        std::cout << "blocked char right" << std::endl;
    
                        return true;
                    }
                }
                if(((g.right+char_pos) >= char_left) && ((g.left+char_pos) <= char_left))
                {
                    int mid = 800 - (char_y_pos + (char_height/2));
                    std::cout << "block found" << std::endl;
                    std::cout << "left :" + std::to_string(g.left) + " right : " + std::to_string(g.right) + "char pos " + std::to_string(char_pos) + " MID " + std::to_string(mid) << std::endl; 

                    if((mid > g.top) && (mid < g.bottom)) {
                        if(!check_collison(UNDER))
                        {
                            return false;
                        }
                        if(g.top > (800 - char_y_pos)){
                            return false;
                        }
                        std::cout << "blocked char left" << std::endl;
    
                        return true;
                    }
                }
            }
            return false;
        }
    }
    return true;
}

void jumpControl(bool skip_jump)
{
    isJumping = true;
    for(int i = 0; i != 15; i++)
    {
        if(skip_jump == true){break;}
        move_char(10, JUMP);
        Sleep(10);
    }
    for(int i = 0; i != 15; i++)
    {
        move_char(-10, JUMP);
        if(check_collison(UNDER) == true){break;}
        Sleep(10);
    }
    isJumping = false;
}


void restartGame()
{
    level_loaded = false;
    initialCharacter = false;
    char_pos = 0;
    char_y_pos = 100;
}