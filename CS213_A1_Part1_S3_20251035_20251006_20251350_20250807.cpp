#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;



// ============= GreyScale: Filter 1 =============

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
            // Grey is obtained when all RGB values for a pixel are equal and the degree differs according to the average obtained by ~ (R+G+B)/3
        }
    }
}


// =============== Black and White: Filter 2 ================

void applyBlackandWhite(Image& image) {
    for (int i=0; i<image.width; i++) {

        for (int j=0; j<image.height; j++ ) {

            unsigned int avg = 0;
            unsigned int x;
            for (int k=0; k<3; k++) {
                avg += image(i, j, k);
                x = image(i, j, k)>=128;
            }
            avg/=3;

            for (int k=0; k<3;k++) {
                image(i, j, k)=avg;
            }

            for (int k=0; k<3; k++) {
                if (x==1) {
                    image.setPixel(i, j, k, 255);
                }
                else {
                    image.setPixel(i, j, k, 0);
                }
            }
        }
    }
}


// ============= Invert: Filter 3 =============

void Invert_filter(Image &image_to_filter) // image_to_filter is a variable created on the same memory address of image (alias to image) so different name won't matter here or in other functions
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
// ============= Frame: Filter 4 =============




// ============= Flip: Filter 5 =============
void applyFlip(Image &image) {
    int flip_choice;
    cout << "Enter 1 for horizontal flip or 2 for vertical flip: ";
    cin >> flip_choice;

    if (flip_choice == 1) { // Horizontal Flip
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    swap(image(i, j, k), image(image.width - 1 - i, j, k));
                }
            }
        }
    } else if (flip_choice == 2) { // Vertical Flip
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    swap(image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }
    } else {
        cout << "Invalid choice! Please enter either 1 or 2.\n";
    }
}

// ============= Rotate Filter: Filter 6 =============

void applyRotation(Image &image) {

    // Take the degree input from the user:
    int degree;
    cout << "Enter the degree of rotation (90, 180, 270):" <<'\n';
    cin >> degree;

    // Rotation 180 degree
    if (degree == 180) {
        for (int i=0;i<image.width;i++)
        {
            for (int j=0;j<image.height/2;j++)
            {
                int tempR = image.getPixel(i, j, 0);
                int tempG = image.getPixel(i, j, 1);
                int tempB = image.getPixel(i, j, 2);

                for (int k=0;k<3;k++) {
                    // الفكرة انك تطرح من ال pixel  الي بتوازيها الناحية التانية في الناحية التانية
                    image(i, j, k) = image(image.width-1-i, image.height-1-j, k);
                }

                image(image.width-1-i, image.height-1-j, 0) = tempR;
                image(image.width-1-i, image.height-1-j, 1) = tempG;
                image(image.width-1-i, image.height-1-j, 2) = tempB;

            }
        }
    }


    else if (degree == 90) {
        Image image2(image.height, image.width);

        for (int i=0;i<image.width;i++)
        {
            for (int j=0;j<image.height;j++)
            {

                int new_i = image.height-1-j ;
                int new_j = i;

                for (int k=0; k<3; k++) {
                    image2(new_i, new_j, k) = image(i, j, k);
                }

            }
        }

        image = image2;

    }
    else if (degree == 270) {
        Image image2 (image.height, image.width);

        for (int i=0 ; i<image.width; i++) {
            for (int j=0; j<image.height; j++) {

                int new_i = j;
                int new_j = image.width-1-i;

                for (int k=0; k<3; k++) {
                    image2(new_i, new_j, k) = image(i, j, k);
                }

            }

        }


        image = image2;

    }
    else {
        cout << "Error! please choose one of these degrees (90, 180, 270)" << '\n';
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


//============== Filter 9 : merge images =====


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
// ============ Inputting Image File ============
    string filename;
    Enter_Image:
    cout << "Enter the image filename - No Spaces: ";
    getline(cin, filename);
    Image image(filename);

    if (image.channels < 3) {
        cout << "The image must be a colored RGB image.\n";
        goto Enter_Image;  // نرجع لإدخال الصورة بدل ما نقفل البرنامج
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


        switch (choice) {      // كل case هنضيف ال function اللي عملناها
            case 1:
                applyGreyscale(image);
                break;
            case 2:
                applyBlackandWhite(image);
                break;
            case 3:
                Invert_filter(image);
                break;
            case 4:
                // DO: فلتر Frame
                break;
            case 5:
                applyFlip(image);
                break;
            case 6:
                 applyRotation(image);
                break;
            case 7:
                Darken_Lighten_filter(image);
                break;
            case 8:
                // DO: فلتر Resize
                break;
            default:
                cout << "Invalid choice! Enter a number from 0 to 8.\n";
                continue; // لو الاختيار مش من 1 لـ 8 نرجع نطبع المنيو بدل ما نقفل ال برنامج
        }

// ============ Saving Filtered Image ============
        cout << "Enter the output image filename & Specify extension: ";  // الجزء ده خاص بكل الفلاتر محدش هيعدل عليه
        cin.ignore();
        string filtered_filename;
        getline(cin, filtered_filename);
        if (image.saveImage(filtered_filename)) {
            cout << "Image saved successfully.\n";
        }
        else {
            cout << "Failed to save the image.\n";
        }
    }
    return 0;
}
