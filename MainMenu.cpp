#include "MainMenu.hpp"

bool main_menu_created = false;

int word_highlighted = false;

const std::string main_menu_words[3] = {"blank","Load Level", "Create Level"};

const std::string esc_menu_words[1] = {"Return To Main Menu"};


std::vector<RECT> main_menu_objects;
std::vector<RECT> esc_menu_objects;



void init_mainmenu(){
    RECT windowRect;
    windowRect.top = 0;
    windowRect.bottom = 800;
    windowRect.left = 0;
    windowRect.right = 1200;

    RECT mainMenuRect = createRectUsingCords(windowRect, 300, 500);
    main_menu_objects.push_back(mainMenuRect);
    esc_menu_objects.push_back(mainMenuRect);

    RECT firstWord = createRectUsingCords(mainMenuRect, mainMenuRect.right-mainMenuRect.left, 50);
    firstWord.bottom -= 200;
    firstWord.top -= 200;
    main_menu_objects.push_back(firstWord);
    esc_menu_objects.push_back(firstWord);


    RECT secondWord = firstWord;
    secondWord.bottom += 200;
    secondWord.top += 200;
    main_menu_objects.push_back(secondWord);


    main_menu_created = true;

}

void paint_mainmenu(HWND hwnd, bool isMainMenu){

    if(!main_menu_created){
        init_mainmenu();
    }

    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);

    if(isMainMenu){
        FillRect(paints.hdc, &paints.rcPaint, white);
    }

    FillRect(paints.hdc, &main_menu_objects[0], white);

    if(word_highlighted == 1){
        SelectObject(paints.hdc, menuFontBig);
    }
    else{
        SelectObject(paints.hdc, menuFontNormal);
    }

    SetBkMode(paints.hdc, TRANSPARENT);
    for(int i = 1; i != std::size(main_menu_words); i++){
        if(word_highlighted == i){
            SelectObject(paints.hdc, menuFontBig);
        }else{
            SelectObject(paints.hdc, menuFontNormal);
        }

        DrawText(paints.hdc, main_menu_words[i].c_str(), std::size(main_menu_words[i]), &main_menu_objects[i],DT_CENTER);
    }
    
    EndPaint(hwnd, &paints);
}
