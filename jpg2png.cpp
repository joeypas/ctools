#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
using namespace std;


char* getCmdOption(char ** begin, char ** end, const string & option){
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end){
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option){
    return std::find(begin, end, option) != end;
}

int main(int argc, char * argv[]) {

    char * filename = getCmdOption(argv, argv + argc, "-f");

    if (filename){
        int width, height, channels;
        unsigned char *img = stbi_load(filename, &width, &height, &channels, 0);
        if (img == NULL) {
            printf("Error in loading the image\n");
            exit(1);
        }

        printf("Loaded image\n");

        string temp(filename);
        stringstream ss;

        for (char c : temp){
            if (c == '.'){
                break;
            } else {
                ss << c;
            }
        }
        temp.clear();
        ss << ".png";
        ss >> temp;
        char const * newFile = temp.c_str();

        printf("Converting ...\n");

        stbi_write_png(newFile, width, height, channels, img, width * channels);

        stbi_image_free(img);

        printf("Done!\n");
    }
    else {
        std::cout << "No Image File provided!" << std::endl;
    }

    return 0;
}