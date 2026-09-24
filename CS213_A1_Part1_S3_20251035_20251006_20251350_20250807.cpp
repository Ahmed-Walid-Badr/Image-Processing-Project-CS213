#include "Image_Class.h"
#include<string>
using namespace std;


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
    cout<<"Enter Crop starting points x & y respectively: ";
    int x,y;
    cin>>x>>y;
    cout<<'\n';
    cout<<"Enter Width & height from the starting point respectively: ";
    int w,h;
    cin>>w>>h;
    cout<<'\n';
    Image cropped_image(w,h);
    for (int i=0;i<w;i++)
    {
        for (int j=0;j<h;j++)
        {
            for (int k=0;k<3;k++) cropped_image(i,j,k)=image_to_filter(i+x,j+y,k);
        }
    }
    image_to_filter=cropped_image;
}




int main()
{
    Image image_to_filter("toy1.jpg");
    Crop_filter(image_to_filter);
    image_to_filter.saveImage("new.png");
}