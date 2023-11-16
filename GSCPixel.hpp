#ifndef GSCPIXEL_H
#define GSCPIXEL_H
#include "Pixel.hpp"
class GSCPixel : public Pixel {
private:
  unsigned char pix;
public:
  GSCPixel();
  GSCPixel(const GSCPixel& p);
  GSCPixel(unsigned char value);
  unsigned char getValue();
  void setValue(unsigned char value);
  int getPixVal();
  bool isGray();
};
#endif
