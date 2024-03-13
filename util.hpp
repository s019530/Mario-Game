#include <iostream>
#include <windows.h>
#include <winuser.h>


typedef enum CUSTOM_KEY{
    CK_A = 65,
    CK_W = 87,
    CK_D = 68
}CUSTOM_KEY;

bool isKeyDown(CUSTOM_KEY key);

int generateNumber(int offset, int max);