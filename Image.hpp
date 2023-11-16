#ifndef IMAGE_H
#define IMAGE_H
#include "Pixel.hpp"
#include <cstdlib>
#include <algorithm>
class Image{
protected:
    int width;
    int height;
    int max_luminocity;
public:
    virtual ~Image(){}
    Image(int width, int height, int max_luminocity){
        this->width = width;
        this->height = height;
        this->max_luminocity = max_luminocity;
    }
    Image(){width=0; height=0; max_luminocity=0;}
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMaxLuminocity() const { return max_luminocity; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
    void setMaxLuminocity(int lum) { this->max_luminocity = lum; }

    virtual Image& operator += (int times) = 0;
    virtual Image& operator *= (double factor) = 0;
    virtual Image& operator ! () = 0;
    virtual Image& operator ~ () = 0;
    virtual Image& operator * () = 0;
    virtual Pixel& getPixel(int row, int col) const = 0;

    friend std::ostream& operator << (std::ostream& out, Image& image){
        if(image.getPixel(0,0).isGray()){
            out<<"P2\n";
            out<<image.getWidth()<<" "<<image.getHeight()<<" "<<image.getMaxLuminocity()<<"\n";
            for(int i=0; i<image.getHeight(); i++){
                for (int j=0; j<image.getHeight(); j++){
                    int num = static_cast<int>(image.getPixel(i,j).getPixVal());
                    out<<num;
                    if((i==image.getHeight()-1)&&(i==image.getWidth()-1)){
                        break;
                    }
                    out<<"\n";
                }
            }
            return out;
        }
        else{
            out<<"P3\n";
            out<<image.getWidth()<<" "<<image.getHeight()<<" "<<image.getMaxLuminocity()<<"\n";
            for(int i=0; i<image.getHeight(); i++){
                for (int j=0; j<image.getWidth(); j++){
                    unsigned char buffer[4];
                    int num = static_cast<int>(image.getPixel(i,j).getPixVal());
                    memcpy(buffer,(char*)&num,4);
                    num = static_cast<int>(buffer[0]);
                    out<<num<<" ";
                    num = static_cast<int>(buffer[1]);
                    out<<num<<" ";
                    num = static_cast<int>(buffer[2]);
                    out<<num;
                    if((i==image.getHeight()-1)&&(i==image.getWidth()-1)){
                        break;
                    }
                    out<<"\n";
                }
            }
            return out;
        }
    }
};
#endif