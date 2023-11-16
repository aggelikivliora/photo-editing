#include "YUVPixel.hpp"
YUVPixel::YUVPixel(const YUVPixel& p){
    yuv = p.yuv;
}
YUVPixel::YUVPixel(unsigned char r, unsigned char g, unsigned char b){
    yuv = 0;
	unsigned char Padding = 0;
	unsigned char buffer[4];
	buffer[0] = ((66*r + 129*g + 25*b + 128)>>8) + 16;
	buffer[1] = ((-38*r - 74*g + 112*b + 128)>>8) + 128;
	buffer[2] = ((112*r + -94*g + -18*b + 128)>>8) + 128;
	buffer[3] = Padding;
	memcpy((char*)&yuv, buffer, 4); //Copy 4 bytes from our char buffer to our ReturnInteger
}
YUVPixel::YUVPixel(){
    yuv = 0;
	unsigned char Padding = 0;
	unsigned char buffer[4];
	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = Padding;
	memcpy((char*)&yuv, buffer, 4); //Copy 4 bytes from our char buffer to our ReturnInteger
}

///////////////////////////////////////////////////////////////////////////
int YUVPixel::getR() const{
    unsigned char buffer[4];
    memcpy(buffer, (char*)&yuv, 4); //copy 4 bytes from our integer to our char buffer
	int y = static_cast<int>(buffer[0]);
    int v = static_cast<int>(buffer[2]);
    int C = y - 16;
    int E = v - 128;
    
    int r = clip((298*C + 409*E + 128)>>8);
    return r;
}
int YUVPixel::getG() const{
    unsigned char buffer[4];
    memcpy(buffer, (char*)&yuv, 4); //copy 4 bytes from our integer to our char buffer
	int y = static_cast<int>(buffer[0]);
    int u = static_cast<int>(buffer[1]);
    int v = static_cast<int>(buffer[2]);
    int C = y - 16;
    int D = u - 128;
    int E = v - 128;
    
    int g = clip((298*C -100*D -208*E + 128)>>8);
    return g;
}
int YUVPixel::getB() const{
    unsigned char buffer[4];
    memcpy(buffer, (char*)&yuv, 4); //copy 4 bytes from our integer to our char buffer
	int y = static_cast<int>(buffer[0]);
    int u = static_cast<int>(buffer[1]);
    int C = y - 16;
    int D = u - 128;
    int b = clip((298*C + 516*D + 128)>>8);
    return b;
}
int YUVPixel::clip(int num) const{
    if(num<0){
        return 0;
    }
    if(num>255){
        return 255;
    }
    return num;
}
///////////////////////////////////////////////////////////////////////////
unsigned char YUVPixel::getY() const{
    unsigned char buffer[4];
    memcpy(buffer, (char*)&yuv, 4); //copy 4 bytes from our integer to our char buffer
	unsigned char y = buffer[0];
    return y;
}
unsigned char YUVPixel::getU() const{
    unsigned char buffer[4];
    memcpy(buffer, (char*)&yuv, 4); //copy 4 bytes from our integer to our char buffer
    unsigned char u = buffer[1];
    return u;
}
unsigned char YUVPixel::getV() const{
    unsigned char buffer[4];
    memcpy(buffer, (char*)&yuv, 4); //copy 4 bytes from our integer to our char buffer
    unsigned char v = buffer[2];
    return v;
}
void YUVPixel::setY(int y){
    unsigned char Padding = 0;
	unsigned char buffer[4];
	buffer[0] = static_cast<unsigned char>(y);
	buffer[1] = getU();
	buffer[2] = getV();
	buffer[3] = Padding;
	memcpy((char*)&yuv, buffer, 4); 
}
void YUVPixel::setYUV(int r,int g,int b){
    unsigned char Padding = 0;
	unsigned char buffer[4];
	buffer[0] = ((66*r + 129*g + 25*b + 128)>>8) + 16;
	buffer[1] = ((-38*r - 74*g + 112*b + 128)>>8) + 128;
	buffer[2] = ((112*r + -94*g + -18*b + 128)>>8) + 128;
	buffer[3] = Padding;
	memcpy((char*)&yuv, buffer, 4); 
}
int YUVPixel::getPixVal(){
	return yuv;
}
bool YUVPixel::isGray(){ 
    return false; 
}