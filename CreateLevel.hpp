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

        std::vector<RECT> clouds;
        std::vector<RECT> ground;
        std::vector<RECT> brown_blocks;

        std::vector<std::vector<RECT>*> objects_to_be_painted = {&clouds, &ground, &brown_blocks, &rect_being_drawn};

        void buttonHandler();


};



#endif