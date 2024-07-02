#include "CreateLevel.hpp"


CreateLevel::CreateLevel(HWND hwnd){
    std::cout << "create level" << std::endl;
    this->hwnd = hwnd;
    state_of_game = CREATE_LEVEL;
    Create_Selected_Box_Menu();

}

void CreateLevel::paintEverything(){
    buttonHandler();
    if(selected_menu == true){
        //paint_selected_rectangle_menu();
        return;
    }
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
            case(0):
                temp_color = &skyBlue;
                break;
            case(1):
                temp_color = &white;
                break;
            case(2):
                temp_color = &green;
                break;
            case(3):
                temp_color = &brown;
                break;
            case(4):
                temp_color = &gray;
                break;
            case(5):
                temp_color = &yellow;
                break;
            case(6):
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

void CreateLevel::Create_Selected_Box_Menu(){
    POINT one;
    POINT two;
    one.x = 350;
    one.y = 200;
    two.x = 750;
    two.y = 400;
    RECT backgroundbox = pointsToRect(one, two);
    selected_box_menu_objects.push_back(backgroundbox);

    int size_of_all_colors = all_colors.size();

    int space = 400 / size_of_all_colors - 2; 

    std::cout << std::to_string(space) << std::endl;

    one.x = 352;

    for(auto elements : all_colors){
        one.y = 240;
        two.y = 290;
        two.x = one.x + space;

        RECT rect = pointsToRect(one, two);
        selected_box_menu_objects.push_back(rect);
        
        one.x = two.x + 1;
    }

    one.x = 450;
    one.y = 330;
    two.y = 380;
    two.x = 650;
    RECT del = pointsToRect(one, two);
    selected_box_menu_objects.push_back(del);

}


void CreateLevel::paint_selected_rectangle_menu(){
    PAINTSTRUCT paints;
    InvalidateRect(hwnd, NULL, false);

    BeginPaint(hwnd, &paints);

    FillRect(paints.hdc, &selected_box_menu_objects.at(0), gray);
    
    for(int i = 1; i != selected_box_menu_objects.size()-1; i++){
        std::cout << "paint " + std::to_string(i) << std::endl;
        FillRect(paints.hdc, &selected_box_menu_objects.at(i), all_colors[i-1]);
    }

    std::string text = "Delete Box";
    SelectObject(paints.hdc, menuFontNormal);
    SetBkMode(paints.hdc, TRANSPARENT);
    DrawText(paints.hdc, text.c_str(), std::size(text), &selected_box_menu_objects.at(selected_box_menu_objects.size()-1), DT_CENTER);

    EndPaint(hwnd, &paints);

}

void CreateLevel::mousePress(){

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);
    pt.x = pt.x - char_pos;
    
    if(selected_menu == true) {
        for(int i = 1; i != selected_box_menu_objects.size(); i++){
            if(mouseInBox(selected_box_menu_objects.at(i), pt)){
                selected_menu = false;
                switch(i){
                    case(1):
                        std::cout << "block 1 " << std::endl;
                        skyBlue_blocks.push_back(saved_selected_rect);
                        return;
                    case(2):
                        white_blocks.push_back(saved_selected_rect);
                        std::cout << "block 2" << std::endl;
                        return;
                    case(3):
                        green_blocks.push_back(saved_selected_rect);
                        return;
                    case(4):
                        brown_blocks.push_back(saved_selected_rect);
                        return;
                    case(5):
                        gray_blocks.push_back(saved_selected_rect);
                        return;
                    case(6):
                        yellow_blocks.push_back(saved_selected_rect);
                        return;
                    case(7):
                        rect_being_drawn.push_back(saved_selected_rect);
                        return;
                    case(8):
                        return;//delete the box
                }
            }
        }
    }

    if(selected_menu){return;}

    if(drawing == false){

        firstPoint = pt;

        for(auto elements : objects_to_be_painted)
        {
            for(int i = 0; i != elements->size(); i++){
                if(mouseInBox(elements->at(i),firstPoint)){
                    std::cout << "mouse in this box" << std::endl;
                    saved_selected_rect = elements->at(i);
                    elements->erase(elements->begin() + i);
                    paint_selected_rectangle_menu();
                    selected_menu = true;
                    return;
                }
            }
        }
        drawing = true;
        std::cout << "start drawing" << std::endl;
    }
    else{
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