#include "MouseEvents.hpp"

LevelLoader *current_level = nullptr;
CreateLevel *current_create_level = nullptr;

void mouse_move(HWND hwnd){

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);

    word_highlighted = 0;

    /*switch(state_of_game){

        case(MAINMENU):
        {
            for(int i = 1; i != std::size(main_menu_objects); i++){
                if(mouseInBox(main_menu_objects[i], p)){
                    word_highlighted = i;
                    break;
                }
            }
            break;
        }
        case(LOADED_LEVEL):
        if(escMenu){
            for(int i = 1; i != std::size(esc_menu_objects); i++){
                if(mouseInBox(esc_menu_objects[i], p)){
                    word_highlighted = i;
                    std::cout << "highlighted";
                    break;
                }
            }
            break;
        }
    }*/

}

void mouse_click(HWND hwnd){
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);

    int box_clicked = -1;

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
                        load_create_level_button(hwnd);
                        break;
                    }
                }
            }
            break;
        }
        case(LOADED_LEVEL):
            if(escMenu == true)
            {
                for(int i = 1; i != std::size(esc_menu_objects); i++)
                {
                    if(mouseInBox(esc_menu_objects[i],p)){
                        box_clicked = i;
                        break;
                    }
                }
                if(box_clicked != -1)
                {
                    switch(box_clicked){
                        case(1):
                        {
                            kill_level_buton(hwnd);
                            break;
                        }
                    }
                }
            }
        case(CREATE_LEVEL):
        {
            current_create_level->mousePress();
            break;
        }
    }
}

void load_level_button(HWND hwnd){
    std::cout << "load level" << std::endl;
    LevelLoader *level = new LevelLoader(hwnd);
    current_level = level;
}

void load_create_level_button(HWND hwnd){
    CreateLevel *level = new CreateLevel(hwnd);
    current_create_level = level;
}

void kill_level_buton(HWND hwnd){
    std::cout << "kill level" << std::endl;
    current_level = nullptr;
    state_of_game = MAINMENU;

    paint_mainmenu(hwnd, true);

    Sleep(300);
}

