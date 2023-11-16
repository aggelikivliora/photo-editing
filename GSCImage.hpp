#ifndef GSCIMAGE_H
#define GSCIMAGE_H
#include "RGBImage.hpp"
#include "GSCPixel.hpp"
class GSCImage : public Image {
public:
  GSCPixel** img;
public:
  GSCImage();
  GSCImage(int h, int w);
  GSCImage(const GSCImage& img);
  GSCImage(const RGBImage& grayscaled);
  GSCImage(std::istream& stream);
  ~GSCImage();

  GSCImage& operator = (const GSCImage& img);  
    
  Image& operator += (int times) override ;
  
  Image& operator *= (double factor) override;
  Image& operator !  () override;
  Image& operator ~  () override;
  Image& operator *  () override;

  Pixel& getPixel(int row, int col) const override;
  friend std::ostream& operator << (std::ostream& out, Image& image) ;
};
#endif