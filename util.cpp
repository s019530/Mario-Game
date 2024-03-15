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

std::vector<std::string> split(std::string input, char delim)
{
    std::vector<std::string> output;
    std::string temp;
    for(char c : input)
    {
        if(c == delim)
        {
            output.push_back(temp);
            temp.clear();
        }
        else{
            temp.push_back(c);
        }
    }

    output.push_back(temp);
    
    return output;
}