#include "file_managment.hpp"
#include "util.hpp"

std::vector<RECT> generateGround(int num_of_ground, int block_size)
{
    std::vector<RECT> ground;
    RECT rect;
    for(int i = 0; i != num_of_ground; i++)
    {
        int left = i * block_size;
        int right = left + block_size;
        int bottom = 800;
        int top = 800 - generateNumber(70, 100);
        SetRect(&rect, left, top, right, bottom);
        ground.push_back(rect);
    }
    return ground;
}

std::vector<RECT> generateClouds(int num_of_clouds)
{   
    std::vector<RECT> clouds;
    int prev = 40;
    for(int i = 0; i != num_of_clouds*2; i++)
    {
        if((i == 0) || (i % 2 == 0))//create base of new cloud
        {
            int right = prev + generateNumber(100, 140);
            int top = generateNumber(20, 60);
            int bottom = top + generateNumber(40, 60);
            RECT rect;
            SetRect(&rect, prev, top, right, bottom);
            prev = right + 80;
            clouds.push_back(rect);
        }
        else{
            RECT temprect = clouds[i-1];

            int fourth = (temprect.right - temprect.left)/8;
            int left = fourth+temprect.left;
            int right = temprect.right - fourth;

            int top = temprect.top - 20;
            int bottom = temprect.bottom + 20;
            RECT rect;
            SetRect(&rect, left, top, right, bottom);
            clouds.push_back(rect);
        }

    }
    return clouds;
}

void save_file(std::string path, std::vector<std::vector<RECT>*> objects){
    std::ofstream file(path + ".umg");


    //CLOUDS, GROUND
    //order - BOTTOM, TOP, RIGHT, LEFT
    int x = 0;
    for(auto c : objects){
        for(int i = 0; i != c->size(); i++){
            file << "CLOUD,";
            switch(x)
            {
                case(CLOUD):
                    file << "CLOUD,";
                    break;
                case(GROUND):
                    file << "GROUND,";
                    break;
                case(BROWN_BLOCK):
                    file<<"BROWNBLOCK,";
                    break;
            }
            file << std::to_string(c->at(i).bottom);
            file << ",";
            file << std::to_string(c->at(i).top);
            file << ",";
            file << std::to_string(c->at(i).right);
            file << ",";
            file << std::to_string(c->at(i).left);
            file << "\n";
        }  
        x++;
    }
    file.close();
}

void load_file(std::string path, std::vector<std::vector<RECT>*>* objects){
    std::ifstream file(path + ".umg");
    std::string temp_string;

    RECT rect;

    while(file >> temp_string)
    {
        std::vector temp = split(temp_string, ',');
        rect.bottom = std::stoi(temp[1]);
        rect.top = std::stoi(temp[2]);
        rect.right = std::stoi(temp[3]);
        rect.left = std::stoi(temp[4]);

        if(temp[0] == "CLOUD"){
            objects->at(CLOUD)->push_back(rect);
        }
        else if(temp[0] == "GROUND"){
            objects->at(GROUND)->push_back(rect);
        }
        else if(temp[0] == "BROWNBLOCK")
        {
            objects->at(BROWN_BLOCK)->push_back(rect);
        }
    }
}