#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;

// ============ فلتر 1: Greyscale ============
void applyGreyscale(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int average = 0;

            for (int k = 0; k < 3; ++k) {
                average += image(i, j, k);
            }

average /= 3;

image(i, j, 0) = average;
            image(i, j, 1) = average;
            image(i, j, 2) = average;
        }
    }
}



// ============ المنيو ============
void Menu() {
    cout << "========================================\n";
    cout << "         Image Filters Menu            \n";
    cout << "========================================\n";
    cout << "1 --> Greyscale\n";
    cout << "2 --> Black & White\n";
    cout << "3 --> Invert Image\n";
    cout << "4 --> Frame\n";
    cout << "5 --> Flip\n";
    cout << "6 --> Rotate\n";
    cout << "7 --> Darken / Lighten\n";
    cout << "8 --> Resize\n";
    cout << "0 --> Exit\n";
    cout << "========================================\n";
}

int main() {
    int choice;

while (true) {
        Menu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // تنظيف الـ buffer قبل getline

if (choice == 0) {
            cout << "Exiting the program... Goodbye!\n";
            break;
        }

// لو الاختيار مش من 1 لـ 8 نرجع نطبع المنيو
        if (choice < 1 || choice > 8) {
            cout << "Invalid choice! Enter a number from 0 to 8.\n";
            continue;
        }

// تحميل الصورة
        string filename;
        cout << "Enter the image filename: ";
        getline(cin, filename);

Image image(filename);

if (image.channels < 3) {
            cout << "The image must be a colored RGB image.\n";
            continue;  // نرجع للمنيو بدل ما نقفل البرنامج
        }

switch (choice) {
            case 1:
                applyGreyscale(image);
                break;
            case 2:
                // TODO: فلتر Black & White
                break;
            case 3:
                // TODO: فلتر Invert Image
                break;
            case 4:
                // TODO: فلتر Frame
                break;
            case 5:
                // TODO: فلتر Flip
                break;
            case 6:
                // TODO: فلتر Rotate
                break;
            case 7:
                // TODO: فلتر Darken / Lighten
                break;
            case 8:
                // TODO: فلتر Resize
                break;
        }

// حفظ الصورة (بعد أي فلتر)
        cout << "Enter the output image filename with extension: ";
        getline(cin, filename);

if (image.saveImage(filename)) {
            cout << "Image saved successfully.\n";
        } else {
            cout << "Failed to save the image.\n";
        }
    }

return 0;
}