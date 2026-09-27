#include <iostream>
#include <algorithm>
#include <string>
#include "Image_Class.h"

using namespace std;

void addSimpleFrame(Image& img) {
    int thickness;
    cout << "Enter frame thickness: ";
    cin >> thickness;

    int r, g, b;
    cin >> r >> g >> b;

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            
            if (i < thickness || i >= img.width - thickness || 
                j < thickness || j >= img.height - thickness) {
                
                img(i, j, 0) = r;
                img(i, j, 1) = g;
                img(i, j, 2) = b;
            }
        }
    }
}

void addFancyFrame(Image& img) {
    int thickness;
    cout << "Enter frame thickness: ";
    cin >> thickness;

    int r, g, b;
    cin >> r >> g >> b;

    int gap = thickness / 2;        
    int innerThickness = 2;         

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
             
              if (i < thickness || i >= img.width - thickness || 
                j < thickness || j >= img.height - thickness) {
                
                img(i, j, 0) = r;
                img(i, j, 1) = g;
                img(i, j, 2) = b;
            }
            
            int start = thickness + gap;
            int endW = img.width - (thickness + gap);
            int endH = img.height - (thickness + gap);

            if ((i >= start && i < start + innerThickness) || (i < endW && i >= endW - innerThickness) ||
                (j >= start && j < start + innerThickness) || (j < endH && j >= endH - innerThickness)) {
                
                if (i >= start && i < endW && j >= start && j < endH) {
                    img(i, j, 0) = 255;
                    img(i, j, 1) = 255;
                    img(i, j, 2) = 255;
                }
            }
        }
    }
}

int main() {
    string filename;
    cout << "Enter image filename to open: ";
    cin >> filename;

    Image img(filename);

    cout << "Choose Frame Type:" <<'\n' ;
    cout << "1. Simple Frame" << '\n' ;
    cout << "2. Fancy/Decorative Frame" << '\n' ;
    cout << "Enter choice (1 or 2): ";
    
    int choice;
    cin >> choice;

    if (choice == 1) {
        addSimpleFrame(img);
    } else if (choice == 2) {
        addFancyFrame(img);
    } else {
        cout << "Invalid choice!" << '\n' ;
        return 0;
    }

    string outputFilename;
    cout << "Enter output filename to save (e.g., output.jpg): ";
    cin >> outputFilename;

    img.saveImage(outputFilename);
    cout << "Image saved successfully!\n";

    return 0;
}