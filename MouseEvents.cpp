#include "MouseEvents.hpp"

LevelLoader *current_level = nullptr;

void mouse_move(HWND hwnd){

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);


    switch(state_of_game){

        case(MAINMENU):
        {
            for(int i = 1; i != std::size(main_menu_objects); i++){
                if(mouseInBox(main_menu_objects[i], p)){
                    word_highlighted = i;
                    break;
                }
                word_highlighted = 0;
            }
            break;
        }
    }

}

void mouse_click(HWND hwnd){
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);

    int box_clicked;

    switch(state_of_game){

        case(MAINMENU):
        {
            for(int i = 1; i != std::size(main_menu_objects); i++){
                if(mouseInBox(main_menu_objects[i], p)){
                    box_clicked = i;
                    break;
                }
                word_highlighted = -1;
            }

            if(box_clicked != -1){
                switch(box_clicked){
                    case(1)://LOAD LEVEL
                    {
                        load_level_button(hwnd);
                        break;
                    }
                    case(2)://CREAT LEVEL
                    {
                        std::cout << "create level 2" << std::endl;
                        break;
                    }
                }
            }
            break;
        }
    }
}

void load_level_button(HWND hwnd){
    std::cout << "load level" << std::endl;
    LevelLoader *level = new LevelLoader(hwnd);
    current_level = level;
}

