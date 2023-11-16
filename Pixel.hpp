#ifndef PIXEL_H
#define PIXEL_H
#include <iostream>
#include <string.h>
using namespace std;
class Pixel{
public:
  virtual int getPixVal()=0;
  virtual bool isGray()=0;
};
#endif