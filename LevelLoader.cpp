#include "LevelLoader.hpp"


LevelLoader::LevelLoader(HWND hwnd){
    this->hwnd = hwnd;

    state_of_game = LOADED_LEVEL;


    load_file("levelone", &(this->objects_to_be_painted));

    copy(this->ground.begin(), this->ground.end(), std::back_inserter(this->under_check));
    copy(this->brown_blocks.begin(), this->brown_blocks.end(), std::back_inserter(this->under_check));

    copy(this->brown_blocks.begin(), this->brown_blocks.end(), std::back_inserter(this->side_check));
    copy(this->ground.begin(), this->ground.end(), std::back_inserter(this->side_check));

    paintLevel();
}

void LevelLoader::paintEverything(){
    paintLevel();
    buttonHandler();
}

void LevelLoader::buttonHandler(){
    

    if(isKeyDown(CK_ESC))
    {
        if(esc_menu){
            esc_menu = false;
        }
        else{
            esc_menu = true;
        }
        Sleep(150);
    }
    if(esc_menu){return;}

    if(isKeyDown(CK_W) || isKeyDown(CK_SPACE)){
        move_char(0, JUMP_START);
    }
    if(isKeyDown(CK_A))
    {
        move_char(char_move_speed, WALK);
    }
    else if(isKeyDown(CK_D))
    {
        move_char(char_move_speed * -1, WALK);
    }

}

void LevelLoader::paintLevel(){
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

    paintCharacter();

    if(esc_menu){
        paintMenu();
    }

    DeleteObject(temp_color);

    EndPaint(hwnd, &paints);
}

void LevelLoader::paintCharacter(){
    SetRect(&characterRect, char_left, 750 - char_y_pos, char_right, 800 - char_y_pos);

    InvalidateRect(hwnd, NULL, false);

    PAINTSTRUCT paints;

    BeginPaint(hwnd, &paints);

    FillRect(paints.hdc, &characterRect, black);

    EndPaint(hwnd, &paints);

    if(check_collision(UNDER) == false) {
        move_char(0, FREE_FALL);
    }
}

void LevelLoader::move_char(int i, int movement_type)
{
    switch(movement_type)
    {
        case(WALK):

            char_pos = char_pos + i;
            if(check_collision(SIDE)){
                char_pos = char_pos - i;
            }
            break;
        case(JUMP):
            char_y_pos += i;
            break;
        case(JUMP_START):
            if(isJumping == false){
                std::thread idc (LevelLoader::jumpControl, this, false);
                idc.detach();
            }
            break;
        case(FREE_FALL):
        {
            if(isJumping == false)
            {
                std::thread idc (LevelLoader::jumpControl, this, true);
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

bool LevelLoader::check_collision(int collisiton_type)
{
    //check for ground position
    switch(collisiton_type) {
        case (UNDER):
        {
            if(800 - char_y_pos >= 795){
                move_char(0, SET_POS_Y);
                return true; // hit the floor
            }
            for(RECT g : under_check)
            {
                if((800 - char_y_pos) < g.top)
                {
                    continue;//ground is found and you're above it
                }

                if((g.left + char_pos <= char_left) && (g.right + char_pos >= char_right))
                {
                    if (((800 - char_y_pos) < g.top + 50) && ((800 - char_y_pos) >= g.top) ){ //clips you back up if the bottom of the character is 50 units into the block other wise lets u fall
                        move_char(800 - g.top, SET_POS_Y);
                        return true; //ground is found but ur on the ground
                    }

                }
            }
            return false; //IF NO GROUND IS FOUND AT ALL
        }
        case (SIDE):
        {
            bool output = true;
            for(RECT g : side_check)
            {
                int mid = 800 - (char_y_pos + (char_height/2));

                if((g.top < mid) && (g.bottom > mid))
                {

                    if((g.right + char_pos >= char_left) && (g.right + char_pos <= char_right))
                    {
                        check_collision(UNDER);//helps with clipping
                        if(g.top > (800 - char_y_pos)){
                            continue;
                        }
                        else{
                            return true;
                        }
                        
                    }
                    else if((g.left + char_pos <= char_right) && (g.left + char_pos >= char_left))
                    {
                        check_collision(UNDER); //helps with clipping
                        if(g.top > (800 - char_y_pos)){
                            continue;
                        }
                        else{
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    }
    return false;
}

void LevelLoader::jumpControl(bool skip_jump)
{
    isJumping = true;
    for(int i = 0; i != 15; i++)
    {
        if(skip_jump == true){break;}
        move_char(10, JUMP);
        Sleep(10);
    }

    while(check_collision(UNDER) == false)
    {
        move_char(-10, JUMP);
        Sleep(10);
    }
    isJumping = false;
}

void LevelLoader::paintMenu(){
    paint_escmenu(hwnd);
}