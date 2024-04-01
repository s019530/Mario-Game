#ifndef LevelLoader_H_

#define LevelLoader_H_

#include <windows.h>
#include <winuser.h>
#include <string>
#include <vector>
#include "util.hpp"
#include "file_managment.hpp"
#include "MainMenu.hpp"
#include <thread>

class LevelLoader{


    public:
        LevelLoader(HWND hwnd);
        void paintEverything();

    private:
        HWND hwnd; 
        
        typedef enum type_of_movement{
            WALK,
            JUMP,
            JUMP_START,
            FREE_FALL,
            SET_POS_Y,
            SET_POS_X
        }type_of_movement;

        typedef enum type_of_collision{
            UNDER,
            SIDE,
            TOP,
            ALL
        }type_of_collision;
        std::vector<RECT> clouds;
        std::vector<RECT> ground;
        std::vector<RECT> brown_blocks;

        const int block_size = 250;
        const int char_width = 20;
        const int window_width = 1200;
        const int char_move_speed = 10;
        const int char_height = 50;

        const int char_right = (window_width / 2) + (char_width/2);
        const int char_left = (window_width / 2) - (char_width/2);  

        bool isJumping = false;

        //0 - clouds, 1 - ground, 2 - brown blocks
        std::vector<std::vector<RECT>*> objects_to_be_painted = {&clouds, &ground, &brown_blocks};
        
        std::vector<RECT> under_check;//things that need to be checked for collision under
        std::vector<RECT> side_check;//things that need to be checked for collision to the side

        RECT characterRect;

        int char_pos = 0;// 590 from the border
        int char_y_pos = 150;

        bool esc_menu = false;

        void paintCharacter();
        void paintLevel();
        void move_char(int i, int movement_type);
        bool check_collision(int collisiton_type);
        void jumpControl(bool skip_jump);
        void restartGame();
        void buttonHandler();
        void paintMenu();

    
};






#endif