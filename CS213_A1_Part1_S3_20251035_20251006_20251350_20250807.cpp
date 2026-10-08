//                 ================================= Notes =================================

// Note: The iteration of the image's pixels is vertical so each row is passed by then we go to the other column
//       i.e. The image pixels are in a reversed array
//
// Note: Since goto is used (Arbitrary jumps in code occur) ----> Not Structured Programming


//                 ================================= Filters =================================

// Exclaimer: This version of file IS NOT a proper executable
//            and is stripped of any functions or headers but the filter functions

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




void Crop_filter(Image &image_to_filter)
{
    cout<<"Enter Crop starting point (x,y) respectively: ";
    starting_point:
    int x,y;
    cin>>x>>y;
    cout<<'\n';
    if (x<=0 || y<=0 || x > image_to_filter.width || y > image_to_filter.height)
    {
        cout<<"Enter valid starting coordinate: ";
        goto starting_point;
    }

    cout<<"Enter the width & height of the rectangle to crop: ";
    cropping_rectangle:
    int w,h;
    cin>>w>>h;
    cout<<'\n';
    if (w<=0 || h<=0) // w=0 & h=0 means there is no pixels ---> no image
    {
        cout<<"Enter valid width and height: ";
        goto cropping_rectangle;
    }
    if (x+(w-1) > image_to_filter.width) // We have the width w = (pixel x) + (w-1 pixels)
    {
        w=image_to_filter.width-x; // [---------x--------------TotalWidth-----w] so make w the distance between x & TotalWidth
    }
    if (y+(h-1) > image_to_filter.height) // We have the height h = (pixel y) + (h-1 pixels)
    {
        h=image_to_filter.height-y; // [------y---------TotalHeight----h] so make h the distance between y & TotalHeight
    }


    Image cropped_image(w,h);
    for (int i=x;i<x+w;i++) // x here is 1 based
    {
        for (int j=y;j<y+h;j++) // y here is 1 based
        {
            for (int k=0;k<3;k++) cropped_image(i-x,j-y,k)=image_to_filter(i-1,j-1,k);
        }
    }
    image_to_filter=cropped_image;
}




void Purple_Filter(Image &image_to_filter)
{
    for (int i=0;i<image_to_filter.width;i++)
    {
        for (int j=0;j<image_to_filter.height;j++)
        {
            image_to_filter(i,j,1)*=0.64; //Purple is the combination of Red and Blue so keep Green zero and the degrees of purple would form
        }
    }
}
