
/*
Project Discription:
This project was required by Dr.Mohammed EL-Ramly for assignment one for Object Oriented Programming course (CS213).
It is for image processing which the user can upload any image using its file name with extensions like :(.jpg, .bmp, .png, ....etc)
and the user can save the image filtered with a customized file name and extension.
The available filters are:
1 --> Greyscale
2 --> Black & White
3 --> Invert Image
4 --> Frame
5 --> Flip
6 --> Rotate
7 --> Darken / Lighten
8 --> Resize




=========================================================
This project is made by:
Mahmoud Waleed Saad => ID:20250807 => Filters 1, 5

Ahmed Ismail Omran => ID:20251006 => Filters 2, 6, 10, 14

Ahmed Walid Badr => ID:20251035 => Filters 3, 7

Mohammed Mokhtar Mohammed => ID:20251350 => Filters 4, 8
==========================================================

Section name: Monday Library lab S15
============================================

*/





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

void Invert_filter(Image &image_to_filter)
{
    for (int i=0;i<image_to_filter.width;i++)
    {
        for (int j=0;j<image_to_filter.height;j++)
        {
            for (int k=0;k<3;k++)
            {
                image_to_filter(i,j,k)=255-image_to_filter(i,j,k);
            }
        }
    }
}
// ============= Frame: Filter 4 =============

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

void Frame_Filter(Image &img)
{
    cout << "Choose Frame Type:" <<'\n' ;
    cout << "1. Simple Frame" << '\n' ;
    cout << "2. Fancy/Decorative Frame" << '\n' ;
    cout << "Enter choice (1 or 2): ";

    Frame_Choice:
    int choice;
    cin >> choice;

    if (choice == 1) {
        addSimpleFrame(img);
    } else if (choice == 2) {
        addFancyFrame(img);
    } else {
        cout << "Invalid choice!" << '\n' ;
        goto Frame_Choice;
    }
}

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


    int degree;
    cout << "Enter the degree of rotation (90, 180, 270):" <<'\n';
    cin >> degree;

    if (degree == 180) {
        for (int i=0;i<image.width;i++)
        {
            for (int j=0;j<image.height/2;j++)
            {
                int tempR = image.getPixel(i, j, 0);
                int tempG = image.getPixel(i, j, 1);
                int tempB = image.getPixel(i, j, 2);

                for (int k=0;k<3;k++) {
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
                image_to_filter(i,j,k)*=1-(level/100.0f);
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
                float changes_to_lighten=image_to_filter(i,j,k)*(1+(level/100.0f));
                image_to_filter(i,j,k)=min(255.0f,changes_to_lighten);
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


// ============ Resize: Filter 8 ============

void resizeFilter(Image& image) {
    int Width, Height;
    cout << "Enter new width: ";
    cin >> Width;
    cout << "Enter new height: ";
    cin >> Height;

    if (Width <= 0 || Height <= 0) {
        cout << "Fail!" << endl;
        return;
    }

    Image resizedImage(Width, Height);

    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {

            int oldX = x * image.width / Width;
            int oldY = y * image.height / Height;

            resizedImage(x, y, 0) = image(oldX, oldY, 0);
            resizedImage(x, y, 1) = image(oldX, oldY, 1);
            resizedImage(x, y, 2) = image(oldX, oldY, 2);
        }
    }

    image = resizedImage;
    cout << "Image resized successfully!" << endl;
}





void EdgeDetection(Image &image) {
    // applyGreyscale(image);

    Image temp(image.width, image.height);

    // Initialize the temp image all pixels= white
    for (int i=0; i<temp.width; i++) {
        for (int j=0; j<temp.height; j++) {
            for (int k=0; k<3; k++) {
                temp(i, j, k) = 255;
            }
        }
    }


    // Detect the edge in the original image:
    for (int i=0; i<image.width-1; i++ ) {
        for (int j=0; j<image.height-1; j++) {

            int tempR = image.getPixel(i, j, 0);
            int tempG = image.getPixel(i, j, 1);
            int tempB = image.getPixel(i, j, 2);

            int pixel_avg = (tempR + tempB + tempG) /3;

            int tempR2 = image.getPixel(i+1, j, 0);
            int tempG2 = image.getPixel(i+1, j, 1);
            int tempB2 = image.getPixel(i+1, j, 2);


            int pixel_avg2 = (tempR2 + tempB2 + tempG2) /3;


            int tempR3 = image.getPixel(i, j+1, 0);
            int tempG3 = image.getPixel(i, j+1, 1);
            int tempB3 = image.getPixel(i, j+1, 2);

            int pixel_avg3 = (tempR3 + tempB3 + tempG3) /3;


            int threshold = 40;

            if (abs(pixel_avg2 - pixel_avg) >= threshold || abs(pixel_avg3 - pixel_avg) >= threshold) {
                for (int k=0; k<3; k++) {
                    temp(i, j, k)  = 0;
                }
            }
        }
    }


    image = temp;
}


void OldTV(Image &image) {

    for (int i=0; i<image.width; i++) {
        for (int j=0; j<image.height; j++) {
            if (j%2) {
                for (int k=0; k<3; k++) {
                    image(i, j, k) = 0;
                }
            }
        }
    }

}



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
    // Filter 9
    cout << "10 --> Edge detection\n";
    // Filters 11 -> 13
    cout << "14 --> Old TV\n";
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
        goto Enter_Image;
    }
// ============ Selecting Filter ============

    int choice;
    while (true) {
        Menu();
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 0) {
            cout << "Exiting the program... Goodbye!\n";
            break;
        }


        switch (choice) {
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
                Frame_Filter(image);
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
                resizeFilter(image);
                break;

            // case 9

            case 10:
                EdgeDetection(image);
                break;

            // cases 11 -> 13 ..........

            case 14:
                OldTV(image);
                break;

            default:
                cout << "Invalid choice! Enter a number from 0 to 16.\n";
                continue;
        }

// ============ Saving Filtered Image ============

        cout << "Enter the output image filename & Specify extension: ";
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