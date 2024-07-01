#include "CreateLevel.hpp"


CreateLevel::CreateLevel(HWND hwnd){
    std::cout << "create level" << std::endl;
    this->hwnd = hwnd;
    state_of_game = CREATE_LEVEL;
}

void CreateLevel::paintEverything(){
    buttonHandler();
    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);

    HBRUSH *temp_color = &green;

    int count = 0;
    FillRect(paints.hdc, &paints.rcPaint, skyBlue);


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
            case(3):
                temp_color = &black;
                break;
        }

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
        }

        count = count + 1;
    }


    DeleteObject(temp_color);

    EndPaint(hwnd, &paints);

    return;
}

void CreateLevel::mousePress(){
    if(drawing == false){
        GetCursorPos(&firstPoint);
        ScreenToClient(hwnd, &firstPoint);
        firstPoint.x = firstPoint.x - char_pos;
        drawing = true;
        std::cout << "start drawing";
    }
    else{
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);
        pt.x = pt.x - char_pos;
        drawing = false;

        rect_being_drawn.push_back(pointsToRect(firstPoint, pt));
        
        drawing = false;
        std::cout << "end drawing";
    }

    return;
}

void CreateLevel::buttonHandler(){
    if(isKeyDown(CK_A))
    {
        std::cout << "moved right" << std::endl;
        char_pos += 10;
    }
    else if(isKeyDown(CK_D))
    {
        char_pos -= 10;
    }
}