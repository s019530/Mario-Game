#include "backgroundPainting.hpp"
#include "util.hpp"
#include "file_managment.hpp"

HBRUSH skyBlue = CreateSolidBrush(RGB(68,243, 255));
HBRUSH white = CreateSolidBrush(RGB(250,250,250));
HBRUSH black = CreateSolidBrush(RGB(0,0,0));
HBRUSH green = CreateSolidBrush(RGB(0, 250, 0));
HBRUSH brown = CreateSolidBrush(RGB(150,75,0));

bool level_loaded = false;
bool initialCharacter = false;

const int char_right = (window_width / 2) + (char_width/2);
const int char_left = (window_width / 2) - (char_width/2);

std::vector<RECT> clouds;
std::vector<RECT> ground;
std::vector<RECT> brown_blocks;
std::vector<RECT> blocks_cache;

//0 - clouds, 1 - ground
std::vector<std::vector<RECT>*> objects_to_be_painted = {&clouds, &ground, &brown_blocks};

std::vector<RECT> under_check;//things that need to be checked for collision under
std::vector<RECT> side_check;//things that need to be checked for collision to the side

RECT characterRect;

int char_pos = 0;// 590 from the border
int char_y_pos = 100;


void initLevel()
{
    load_file("levelone", &objects_to_be_painted);
    level_loaded = true;
    copy(ground.begin(), ground.end(), std::back_inserter(under_check));
    copy(brown_blocks.begin(), brown_blocks.end(), std::back_inserter(under_check));

    //copy(ground.begin(), ground.end(), std::back_inserter(side_check));
    copy(brown_blocks.begin(), brown_blocks.end(), std::back_inserter(side_check));
    copy(ground.begin(), ground.end(), std::back_inserter(side_check));

    std::cout << std::to_string(side_check.size()) << std::endl;
    std::cout << std::to_string(ground.size()) << std::endl;

}

void paintAllObjects(HWND hwnd)
{
    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);

    HBRUSH *temp_color = &green;

    int count = 0;

    for(auto elements : objects_to_be_painted)
    {
        switch(count)
        {
            case(0)://clouds
                temp_color = &white;
                break;
            case(1)://ground
                temp_color = &green;
                break;
            case(2)://brown block
                temp_color = &brown;
                break;
        }
        blocks_cache.clear();

        for(int i = 0; i != elements->size(); i++)
        {
            if((elements->at(i).right+char_pos < 0) || elements->at(i).left+char_pos > 1200){}
            else if((elements->at(i).left+char_pos < 0) && (elements->at(i).right + char_pos > 0)) // left border
            {
                RECT temp = elements->at(i);
                SetRect(&temp, 0, elements->at(i).top, elements->at(i).right + char_pos, elements->at(i).bottom);
                FillRect(paints.hdc, &temp, *temp_color);



            }
            else if((elements->at(i).right + char_pos > 1200) && (elements->at(i).left + char_pos < 1200))//right border
            {
                RECT temp = elements->at(i);
                SetRect(&temp, elements->at(i).left+char_pos, elements->at(i).top, 1200, elements->at(i).bottom);
                FillRect(paints.hdc, &temp, *temp_color);



            }
            else
            {
                RECT rect;
                rect = elements->at(i);
                rect.right = rect.right + char_pos;
                rect.left = rect.left + char_pos;
                FillRect(paints.hdc, &rect, *temp_color);

            }
            RECT rect = elements->at(i);

            for(RECT g : side_check) 
            {
                if(
                    (g.top == rect.top) && 
                    (g.bottom == rect.bottom) &&
                    (g.left == rect.left) &&
                    (g.right == rect.right)
                )
                {
                    blocks_cache.push_back(rect);
                }
            }
        }
        count = count + 1;
        //std::cout << std::to_string(blocks_cache.size())<< std::endl;
    }
    DeleteObject(temp_color);
    EndPaint(hwnd, &paints);
}

void paintBlueSkyBackground(HWND hwnd)
{
    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);

    if(!level_loaded){
        initLevel();
    }
    
    RECT rect;
    FillRect(paints.hdc, &paints.rcPaint, skyBlue);//paint sky

    paintAllObjects(hwnd); //paints all the objects

    //paint char;
    if(initialCharacter == false) {
        paintCharacter(hwnd);
        initialCharacter = true;
    }

   
    EndPaint(hwnd, &paints);
}

void paintCharacter(HWND hwnd)
{
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
    bool buffered_output = true;
    //check for ground position
    switch(collision_type) {
        case (UNDER):
        {
            if(800 - char_y_pos >= 795){
                move_char(0, SET_POS_Y);
                return true; // hit the floor
            }
            for(RECT g : under_check)
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
            for(RECT g : side_check)
            {
                std::cout << "top " + std::to_string(g.top) + " bot " + std::to_string(g.bottom) << std::endl;
                std::cout << "left " + std::to_string(g.left + char_pos) + " right " + std::to_string(g.right + char_pos) << std::endl;

                std::cout << "char _ right " + std::to_string(char_right);
                std::cout << "char _ left " + std::to_string(char_left);
                std::cout << "\n\n\n\n\n";
                if(((g.left+char_pos) >= char_right) && ((g.right+char_pos) <= char_right)) // inequality flipped
                {
                    int mid = 800 - (char_y_pos + (char_height/2));
                    std::cout << "top " + std::to_string(g.top) + " bot " + std::to_string(g.bottom) << std::endl;
                    std::cout << "mid " + std::to_string(mid) + "\n\n\n";
                    if((mid > g.top) && (mid < g.bottom)) {
                        std::cout << "block found" << std::endl;
                        if(!check_collison(UNDER))
                        {
                            buffered_output = false;
                            //return false;
                        }
                        if(g.top > (800 - char_y_pos)){
                            buffered_output = false;
                            //return false;
                        }                        
                        if(buffered_output){
                            std::cout << "blocked char right" << std::endl;
                            return true;
                        }
                        //return true;
                    }
                }
                if(((g.right+char_pos) <= char_left) && ((g.left+char_pos) >= char_left)) //inequality flipped
                {
                    int mid = 800 - (char_y_pos + (char_height/2));
                    std::cout << "top " + std::to_string(g.top) + " bot " + std::to_string(g.bottom) << std::endl;
                    std::cout << "mid " + std::to_string(mid) + "\n\n\n";
                    if((mid > g.top) && (mid < g.bottom)) {
                        std::cout << "block found" << std::endl;
                        if(!check_collison(UNDER))
                        {
                            buffered_output = false;
                            //return false;
                        }
                        if(g.top > (800 - char_y_pos)){
                            buffered_output = false;
                            //return false;
                        }
                        if(buffered_output){
                            std::cout << "blocked char left" << std::endl;
                            return true;
                        }
                        //return true;
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

    while(check_collison(UNDER) == false)
    {
        move_char(-10, JUMP);
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

void mouseButton(HWND hwnd)
{
    std::cout << "mouse";
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);
    std::cout << "x : " + std::to_string(pt.x - char_pos) + " y: " + std::to_string(pt.y) << std::endl;
}