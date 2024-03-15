#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <string>
#include <vector>

typedef enum CUSTOM_KEY{
    CK_A = 65,
    CK_W = 87,
    CK_D = 68,
    CK_ONE = 49
}CUSTOM_KEY;

bool isKeyDown(CUSTOM_KEY key);

int generateNumber(int offset, int max);

std::vector<std::string> split(std::string input, char delim);