
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


// =============== Edge detection: Filter 10 ================

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


// =============== Old TV: Filter 14 ================

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
