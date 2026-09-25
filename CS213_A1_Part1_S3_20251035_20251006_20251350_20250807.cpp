#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;                                     // اتمنى لو حد لقى حاجة غلط مش عارفها او مش عارف يعمل فيها اي يقولي



// ============= Grey_Scale: Filter 1 =============
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


// ============= Invert: Filter 3 =============

void Invert_filter(Image &image_to_filter)
{
    for (int i=0;i<image_to_filter.width;i++)
    {
        for (int j=0;j<image_to_filter.height;j++)
        {
            for (int k=0;k<3;k++)
            {
                image_to_filter(i,j,k)=255-image_to_filter(i,j,k); //Inverting colors is getting their 255's complement
            }
        }
    }
}


// ============= Darken/Lighten: Filter 7 =============

void Darkening_filter(Image &image_to_filter)
{
    cout<<"Enter Darkening Level from 0 to 100: ";
    int level;
    cin>>level;
    cout<<'\n';

    for (int i=0;i<image_to_filter.width;i++)
    {
        for (int j=0;j<image_to_filter.height;j++)
        {
            for (int k=0;k<3;k++)
            {
                image_to_filter(i,j,k)*=1-(level/100.0f);//Decrease intensity of color, and so brightness of pixel, by [level%] times
                //100.0f---> 100 treated as float, to save memory & keep precision during the arithmetic operations
            }
        }
    }
}


void Lightening_filter(Image &image_to_filter)
{
    cout<<"Enter Lightening Level from 0 to 100: ";
    int level;
    cin>>level;
    cout<<'\n';

    for (int i=0;i<image_to_filter.width;i++)
    {
        for (int j=0;j<image_to_filter.height;j++)
        {
            for (int k=0;k<3;k++)
            {
                float changes_to_lighten=image_to_filter(i,j,k)*(1+(level/100.0f)); //Increase intensity of colors, and so brightness of pixel, by [level%] times
                //100.0f---> 100 treated as float, and float to save memory & keep precision during the arithmetic operations
                image_to_filter(i,j,k)=min(255.0f,changes_to_lighten);
                // the maximum possible value for an unsigned char is 255
            }
        }
    }
}


void Darken_Lighten_filter(Image &image_to_filter)
{
    dark_or_light:
    cout<<"Type D to Darken & L to Lighten: ";
    string Brightness_Type;
    cin>>Brightness_Type;
    cout<<'\n';

    if (Brightness_Type[0] == 'D' || Brightness_Type[0] == 'd') Darkening_filter(image_to_filter);
    else if (Brightness_Type[0] == 'L' || Brightness_Type[0] == 'l') Lightening_filter(image_to_filter);
    else goto dark_or_light;

}


// ============= Crop: Filter 11 =============

// void Crop_filter(Image &image_to_filter)
// {
//     cout<<"Enter Crop starting point (x,y) respectively: ";
//     starting_point:
//     int x,y;
//     cin>>x>>y;
//     cout<<'\n';
//     if (x<=0 || y<=0 || x > image_to_filter.width || y > image_to_filter.height)
//     {
//         cout<<"Enter valid starting coordinate: ";
//         goto starting_point;
//     }
//
//     cout<<"Enter the width & height of the rectangle to crop: ";
//     cropping_rectangle:
//     int w,h;
//     cin>>w>>h;
//     cout<<'\n';
//     if (w<=0 || h<=0) // w=0 & h=0 means there is no pixels ---> no image
//     {
//         cout<<"Enter valid width and height: ";
//         goto cropping_rectangle;
//     }
//     if (x+(w-1) > image_to_filter.width) // We have the width w = (pixel x) + (w-1 pixels)
//     {
//         w=image_to_filter.width-x; // [---------x--------------TotalWidth-----w] so make w the distance between x & TotalWidth
//     }
//     if (y+(h-1) > image_to_filter.height) // We have the height h = (pixel y) + (h-1 pixels)
//     {
//         h=image_to_filter.height-y; // [------y---------TotalHeight----h] so make h the distance between y & TotalHeight
//     }
//
//
//     Image cropped_image(w,h);
//     for (int i=x;i<x+w;i++) // x here is 1 based
//     {
//         for (int j=y;j<y+h;j++) // y here is 1 based
//         {
//             for (int k=0;k<3;k++) cropped_image(i-x,j-y,k)=image_to_filter(i-1,j-1,k);
//         }
//     }
//     image_to_filter=cropped_image;
// }


// ============= Purple: Filter 15 =============

// void Purple_Filter(Image &image_to_filter) {
//     for (int i=0;i<image_to_filter.width;i++)
//     {
//         for (int j=0;j<image_to_filter.height;j++)
//         {
//             image_to_filter(i,j,1)=0; //Purple is the combination of Red and Blue so keep Green zero and the degrees of purple would form
//         }
//     }
// }


// ============ Menu ============
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
    // تحميل الصورة
    string filename;
    Enter_Image:
    cout << "Enter the image filename - No Spaces: ";
    getline(cin, filename);
    Image image_to_filter(filename);

    if (image_to_filter.channels < 3) {
        cout << "The image must be a colored RGB image.\n";
        goto Enter_Image;  // نرجع للمنيو بدل ما نقفل البرنامج
    }

    int choice;
    while (true) {      // عملناها عشان الدكتور قال كل ما نقفل ال menu comes again
        Menu();
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 0) {
            cout << "Exiting the program... Goodbye!\n";
            break;
        }

// لو الاختيار مش من 1 لـ 8 نرجع نطبع المنيو

        switch (choice) {      // كل case هنضيف ال function اللي عملناها
            case 1:
                applyGreyscale(image_to_filter);
                break;
            case 2:
                // DO: فلتر Black & White
                break;
            case 3:
                Invert_filter(image_to_filter);
                break;
            case 4:
                // DO: فلتر Frame
                break;
            case 5:
                // DO: فلتر Flip
                break;
            case 6:
                // DO: فلتر Rotate
                break;
            case 7:
                Darken_Lighten_filter(image_to_filter);
                break;
            case 8:
                // DO: فلتر Resize
                break;
            default:
                cout << "Invalid choice! Enter a number from 0 to 8.\n";
                continue;
        }

// حفظ الصورة (بعد أي فلتر)
        cout << "Enter the output image filename & Specify extension: ";  // الجزء ده خاص بكل الفلاتر محدش هيعدل عليه لحد السطر 116
        cin.ignore();
        string filtered_filename;
        getline(cin, filtered_filename);
        if (image_to_filter.saveImage(filtered_filename)) {
            cout << "Image saved successfully.\n";
        }
        else {
            cout << "Failed to save the image.\n";
        }
    }
    return 0;
}
