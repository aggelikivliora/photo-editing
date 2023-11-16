#include "RGBPixel.hpp"
RGBPixel::RGBPixel(const RGBPixel& p){
    r = p.r;
    g = p.g;
    b = p.b;
}
RGBPixel::RGBPixel(unsigned char r, unsigned char g, unsigned char b){
    this->r = r;
    this->g = g;
    this->b = b;
}
RGBPixel::RGBPixel(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
}
unsigned char RGBPixel::getRed() const{
    return r;
}
unsigned char RGBPixel::getGreen() const{
    return g;
}
unsigned char RGBPixel::getBlue() const{
    return b;
}
void RGBPixel::setRed(unsigned char r){
    this->r=r;
}
void RGBPixel::setGreen(unsigned char g){
    this->g=g;
}
void RGBPixel::setBlue(unsigned char b){
    this->b=b;
}
int RGBPixel::getPixVal(){
    int ReturnInt = 0;
	unsigned char Padding = 0;
	unsigned char buffer[4];
	buffer[0] = r;
	buffer[1] = g;
	buffer[2] = b;
	buffer[3] = Padding;
	memcpy((char*)&ReturnInt, buffer, 4);
	return ReturnInt;
}
bool RGBPixel::isGray(){ 
    return false; 
}