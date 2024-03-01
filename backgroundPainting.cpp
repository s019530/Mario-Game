#include "backgroundPainting.hpp"


HBRUSH skyBlue = CreateSolidBrush(RGB(68,243, 255));
HBRUSH white = CreateSolidBrush(RGB(250,250,250));
HBRUSH black = CreateSolidBrush(RGB(0,0,0));

bool cloudGenerated = false;
bool initialCharacter = false;

RECT clouds[24];

RECT characterRect;

int char_pos = 0;// 590 from the border
int char_y_pos = 0;



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
            std::cout << "Cloud " + std::to_string(i) + " generated" << std::endl;
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

        std::cout << "Cloud " + std::to_string(i) + " generated" << std::endl;
    }
}

void paintClouds(HWND hwnd){
    
    if(!cloudGenerated){
        cloudGenerated = true;
        generateClouds();
        }
    std::cout << std::to_string(char_pos) << std::endl;

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

}

int generateNumber(int offset, int max){
    return offset + (rand() % max);
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
    SetRect(&characterRect, 590, 725 - char_y_pos, 610, 800 - char_y_pos);

    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);

    FillRect(paints.hdc, &characterRect, black);

    EndPaint(hwnd, &paints);
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
                std::thread idc (jumpControl);
                idc.detach();
            }
            break;
    }
}

void jumpControl()
{
    isJumping = true;
    for(int i = 0; i != 15; i++)
    {
        move_char(10, JUMP);
        Sleep(10);
    }
    for(int i = 0; i != 15; i++)
    {
        move_char(-10, JUMP);
        Sleep(10);
    }
    isJumping = false;
}
