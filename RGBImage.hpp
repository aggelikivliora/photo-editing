#ifndef RGBIMAGE_H
#define RGBIMAGE_H
#include "YUVPixel.hpp"
#include "Image.hpp"
#include "RGBPixel.hpp"
#include <sstream>
#include <fstream>
#include <tgmath.h> 
class RGBImage : public Image {
public:
  RGBPixel **img;
public:
  RGBImage(); 
  RGBImage(int h, int w);
  RGBImage(const RGBImage& img);
  RGBImage(std::istream& stream);
  ~RGBImage();

  RGBImage& operator = (const RGBImage& img);
   
  Image& operator += (int ) override ;
  
  Image& operator *= (double factor) override;
  Image& operator !() override;
  Image& operator ~() override;
  Image& operator *() override;
  
  Pixel& getPixel(int row, int col) const override;
  friend std::ostream& operator << (std::ostream& out, Image& image);
  int binarySearch(int size,float arr[], int lft, int rt, int x, int& f);
};
#endif