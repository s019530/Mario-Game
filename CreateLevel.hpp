#ifndef CreateLevel_H_

#define CreateLevel_H_

#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <string>
#include <vector>
#include "util.hpp"

class CreateLevel{
    public:
        CreateLevel(HWND hwnd);
        void paintEverything();
        void mousePress();
    private:
        HWND hwnd;

        bool drawing = false;

        int char_pos = 0;

        POINT firstPoint;
        std::vector<RECT> rect_being_drawn;

        RECT saved_selected_rect;

        std::vector<RECT> skyBlue_blocks;
        std::vector<RECT> white_blocks;
        std::vector<RECT> green_blocks;
        std::vector<RECT> brown_blocks;
        std::vector<RECT> gray_blocks;
        std::vector<RECT> yellow_blocks;

        std::vector<std::vector<RECT>*> objects_to_be_painted = {&skyBlue_blocks, &white_blocks, &green_blocks, &brown_blocks, &gray_blocks, &yellow_blocks, &rect_being_drawn};

        void buttonHandler();
        void paint_selected_rectangle_menu();
        void Create_Selected_Box_Menu();

        std::vector<RECT> selected_box_menu_objects;

        bool selected_menu = false;




};



#endif