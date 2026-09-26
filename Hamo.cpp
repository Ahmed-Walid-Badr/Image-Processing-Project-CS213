#include <iostream>
#include "Image_Class.h"

using namespace std;

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

int main() {
    string filename;
    cout << "Enter image filename to load: ";
    cin >> filename;

    Image img(filename);

    resizeFilter(img);

    cout << "Enter filename to save resized image: ";
    cin >> filename;
    img.saveImage(filename);

    return 0;
}