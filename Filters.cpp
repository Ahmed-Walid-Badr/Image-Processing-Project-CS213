
#include <iostream>
using namespace std;
#include "Image_Class.h"

// ========================= Filter 1 : Greyscale Filter =========================

void applyGreyscale(Image &image) {
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            unsigned avg = 0;

            for (int k = 0; k < 3;k++) {
                avg += image(x, y, k);
            }
            avg /= 3;
            image(x, y, 0) = avg;
            image(x, y, 1) = avg;
            image(x, y, 2) = avg;
        }
    }
}

// ========================= Filter 5 : Flip Filter =========================

void applyFlip(Image &image) {
    int choice;
    cout << "pls enter 1 for horizontal flip or 2 for vertical flip: ";
    cin >> choice;

    if (choice == 1) {
        for (int x = 0; x < image.width / 2; x++) {
            for (int y = 0 ; y < image.height; y++) {
                for (int k = 0; k < 3; k++) {
                    // int temp = image(x, y, k);
                    // image(x, y, k) = image(image.width - 1 - x, y, k);
                    // image(image.width - 1 - x, y, k) = temp;
                    swap(image(x,y,k), image(image.width - 1- x,y,k));
                }
            }
        }
    } else if (choice == 2) {
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height / 2; y++) {
                for (int k = 0 ;k < 3 ; k++) {
                    int FL = image(x, y ,k);
                    image(x,y,k) = image(x , image.height - 1 - y, k);
                    image(x , image.height - 1 - y, k) = FL;
                }
            }
        }
    }
}

// ========================= Filter 9 : merge =========================

void merge(Image &image) {

    string filename2;
    cout << "Pls enter the second image name to merge with the first image: ";
    cin >> filename2;

    Image image2(filename2);

    if (image2.channels < 3) {
        cout << "The second image must have at least 3 channels (RGB) to merge." << endl;
        return;
    }

    int choice;
    cout << "1 --> Merge Using the biggest dimensions\n";
    cout << "2 --> Merge Using the smallest dimensions\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int newWidth = max(image.width,image2.width);
        int newHeight = max(image.height,image2.height);

        Image result(newWidth, newHeight);
        
        for (int i = 0; i< newWidth;i++) {
            for (int j = 0; j < newHeight; j++) {
                bool inImage1 = (i < image.width && j < image.height);
                bool inImage2 = (i < image2.width && j < image2.height);

                if (inImage1 && inImage2) {
                    for (int k = 0; k < 3; k++) {
                        result(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
                    }
                } else if (inImage1) {
                    for (int k = 0; k < 3; k++) {
                        result(i, j, k) = image(i, j, k);
                    }
                } else if (inImage2) {
                    for (int k = 0; k < 3; k++) {
                        result(i, j, k) = image2(i, j, k);
                    }
                }
            }
        }
        image = result;
    } else if (choice == 2) {
        int newWidth = min(image.width,image2.width);
        int newHeight = min(image.height,image2.height);

        Image result(newWidth, newHeight);
        
        for (int i = 0; i< newWidth;i++) {
            for (int j = 0; j < newHeight; j++) {
                for (int k = 0; k < 3; k++) {
                    result(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
                }
            }
        }
        image = result;
    } else {
        cout << "Invalid choice. Please select either 1 or 2." << endl;
    }
}


// ========================== Filter 13 : Sunlight Filter =========================

void Sunlight(Image &image) {
    for (int i = 0; i < image.width ;i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3 ; k++) {
                
                int Red = image(i,j,k) + 20;
                int Green = image(i,j,k) + 10;
                int Blue = image(i,j,k) - 10;

                Red = min(255, Red);
                Green = min(255, Green);
                Blue = max(0, Blue);

                image(i,j,0) = Red;
                image(i,j,1) = Green;
                image(i,j,2) = Blue;
            }
        }
    }
} 




// =================================== Filter 17 : Skewing ======================================

void Skewing(Image &image,Image &result ,double angel) {
    double radian = angel * M_PI / 180.0;

    int width = image.width;
    int height = image.height;

    int newHeight = height + abs(radian * (width - 1));

    Image Skewing(width, newHeight);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < newHeight; y++) {
            for (int k = 0; k < 3; k++) {
                Skewing(x, y, k) = 255; // Initialize to White
            }
        }
    }

    for (int x = 0 ;x < width;x++) {
        for (int y = 0; y < height; y++) {
            int newY = y + (radian * x);
            if (newY >= 0 && newY < newHeight) {
                for (int k = 0; k < 3; k++) {
                    Skewing(x, newY, k) = image(x, y, k);
                }
            }
        }
    }

    result = Skewing;
}


int main() {
    string filename;
    cout << "Pls enter colored image name to turn to gray scale: ";
    cin >> filename;

    Image image(filename);
    applyGreyscale(image);

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);

    return 0;
}

// ======================================== Filter 18 : Oil painting ======================================

void oilPainting(Image &image, Image &result) {
    int radius = 4;    
    int levels = 20;

    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {

            int count[20] = {0};
            int sumR[20] = {0};
            int sumG[20] = {0};
            int sumB[20] = {0};

            for (int dx = -radius; dx <= radius; dx++) {
                for (int dy = -radius; dy <= radius; dy++) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0 || nx >= image.width || ny < 0 || ny >= image.height)
                        continue;

                    int r = image.getPixel(nx, ny, 0);
                    int g = image.getPixel(nx, ny, 1);
                    int b = image.getPixel(nx, ny, 2);

                    int intensity = (r + g + b) / 3;     
                    int bin = intensity * levels / 256;  

                    count[bin]++;
                    sumR[bin] += r;
                    sumG[bin] += g;
                    sumB[bin] += b;
                }
            }

            int best = 0;
            for (int i = 1; i < levels; i++) {
                if (count[i] > count[best])
                    best = i;
            }

            result.setPixel(x, y, 0, sumR[best] / count[best]);
            result.setPixel(x, y, 1, sumG[best] / count[best]);
            result.setPixel(x, y, 2, sumB[best] / count[best]);
        }
    }
}   
