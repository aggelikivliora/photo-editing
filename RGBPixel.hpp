#ifndef RGBPIXEL_H
#define RGBPIXEL_H
#include "Pixel.hpp"
class RGBPixel : public Pixel {
private:
  unsigned char r;
  unsigned char g;
  unsigned char b;
public:
  RGBPixel();
  RGBPixel(const RGBPixel& p);
  RGBPixel(unsigned char r, unsigned char g, unsigned char b);
  unsigned char getRed() const;
  unsigned char getGreen() const;
  unsigned char getBlue() const;
  void setRed(unsigned char r);
  void setGreen(unsigned char g);
  void setBlue(unsigned char b);
  int getPixVal();
  bool isGray();
};
#endif
