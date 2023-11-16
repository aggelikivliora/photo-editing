#ifndef YUVPIXEL_H
#define YUVPIXEL_H
#include "Pixel.hpp"
class YUVPixel : public Pixel {
private:
  int yuv;
public:
  YUVPixel();
  YUVPixel(const YUVPixel& p);
  YUVPixel(unsigned char r, unsigned char g, unsigned char b);
  int getR() const;
  int getG() const;
  int getB() const;
  unsigned char getY() const;
  unsigned char getU() const;
  unsigned char getV() const;
  void setYUV(int y,int u,int v);
  void setY(int y);
  int getPixVal();
  bool isGray();
  int clip(int num) const;
};
#endif