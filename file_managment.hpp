#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

typedef enum type_of_object{
    CLOUD,
    GROUND
}type_of_object;


std::vector<RECT> generateGround(int num_of_ground, int block_size);

std::vector<RECT> generateClouds(int num_of_clouds);

void save_file(std::string path, std::vector<std::vector<RECT>*> objects);

void load_file(std::string path, std::vector<std::vector<RECT>*>* objects);