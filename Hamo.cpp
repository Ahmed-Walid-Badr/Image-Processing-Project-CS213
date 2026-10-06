#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;

void applyInfraredFilter(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            
            img(i, j, 0) = 255;
            
            img(i, j, 1) = 255 - img(i, j, 1);
            
            img(i, j, 2) = 255 - img(i, j, 2);
        }
    }
}

int main() {
    string filename;
    cout << "Enter input image name: ";
    cin >> filename;

    Image img(filename);

    applyInfraredFilter(img);

    string saveName;
    cout << "Enter output image name to save: ";
    cin >> saveName;
    img.saveImage(saveName);

    cout << "Filter applied and image saved successfully!" << endl;

    return 0;
}