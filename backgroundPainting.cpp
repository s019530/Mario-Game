#include "backgroundPainting.hpp"
#include "util.hpp"

HBRUSH skyBlue = CreateSolidBrush(RGB(68,243, 255));
HBRUSH white = CreateSolidBrush(RGB(250,250,250));
HBRUSH black = CreateSolidBrush(RGB(0,0,0));
HBRUSH green = CreateSolidBrush(RGB(0, 250, 0));

bool cloudGenerated = false;
bool initialCharacter = false;

const int char_right = (window_width / 2) + (char_width/2);
const int char_left = (window_width / 2) - (char_width/2);

RECT clouds[24];


RECT ground[10];

RECT characterRect;

int char_pos = 0;// 590 from the border
int char_y_pos = 100;


void generateGround()
{
    RECT rect;
    for(int i = 0; i != (std::end(ground) - std::begin(ground)); i++)
    {
        int left = i * block_size;
        int right = left + block_size;
        int bottom = 800;
        int top = 800 - generateNumber(70, 100);
        SetRect(&rect, left, top, right, bottom);
        ground[i] = rect;
    }
}

void generateClouds()
{   

    int prev = 40;
    for(int i = 0; i != (std::end(clouds) - std::begin(clouds)); i++)
    {
        if((i == 0) || (i % 2 == 0))//create base of new cloud
        {
            int right = prev + generateNumber(100, 140);
            int top = generateNumber(20, 60);
            int bottom = top + generateNumber(40, 60);
            RECT rect;
            SetRect(&rect, prev, top, right, bottom);
            prev = right + 80;
            clouds[i] = rect;
            //std::cout << "Cloud " + std::to_string(i) + " generated" << std::endl;
        }
        else{
            RECT temprect = clouds[i-1];

            int fourth = (temprect.right - temprect.left)/8;
            int left = fourth+temprect.left;
            int right = temprect.right - fourth;

            int top = temprect.top - 20;
            int bottom = temprect.bottom + 20;
            RECT rect;
            SetRect(&rect, left, top, right, bottom);
            clouds[i] = rect;
        }

        //std::cout << "Cloud " + std::to_string(i) + " generated" << std::endl;
    }
}

void paintClouds(HWND hwnd){
    
    if(!cloudGenerated){
        cloudGenerated = true;
        generateClouds();
        generateGround();
        }
    //std::cout << std::to_string(char_pos) << std::endl;

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
        //std::cout << "ground painted" << std::endl;
    }
    EndPaint(hwnd, &paints);
}

void paintBlueSkyBackground(HWND hwnd)
{

    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);
    
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
    SetRect(&characterRect, char_left, 725 - char_y_pos, char_right, 800 - char_y_pos);

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
        case(SET_POS):
        {
            char_y_pos = i;
            std::cout << "sets position" << std::endl;
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
                std::cout << "dead" << std::endl;
                move_char(0, SET_POS);
                return true; // hit the floor
            }
            std::cout << "checking under" << std::endl;
            for(RECT g : ground)
            {
                if((g.left + char_pos <= char_left) && (g.right + char_pos >= char_right))
                {
                    std::cout << "rect found" << std::endl;
                    if((800 - char_y_pos) < g.top)
                    {
                        std::cout << "False" << std::endl;
                        return false;//ground is foudn and you're above it
                    }
                    else{
                        move_char(800 - g.top, SET_POS);
                        return true; //ground is found but ur on the ground
                    }
                }
            }
            return false; //IF NO GROUND IS FOUND AT ALL
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
