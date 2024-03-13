#include "util.hpp"

bool isKeyDown(CUSTOM_KEY key){
    if(GetKeyState(key) & 0x8000)
    {
        return true;
    }
    return false;
}


int generateNumber(int offset, int max){
    return offset + (rand() % max);
}
