#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;

void BlurFilter(Image& img) {
    for (int pass = 0; pass < 6; pass++) {
        Image blurred = img;

        for (int i = 1; i < img.width - 1; i++) {
            for (int j = 1; j < img.height - 1; j++) {
                for (int k = 0; k < 3; k++) {
                    int sum = img(i - 1, j - 1, k) + img(i - 1, j, k) + img(i - 1, j + 1, k) +
                              img(i,     j - 1, k) + img(i,     j, k) + img(i,     j + 1, k) +
                              img(i + 1, j - 1, k) + img(i + 1, j, k) + img(i + 1, j + 1, k);

                    blurred(i, j, k) = sum / 9;
                }
            }
        }
        img = blurred  ; 
    }
}

int main() {
    string filename;
    cout << "Enter input image name: ";
    cin >> filename;

    Image img(filename);

    BlurFilter(img);

    string saveName;
    cout << "Enter output image name to save: ";
    cin >> saveName;
    
    img.saveImage(saveName);
    return 0;
}