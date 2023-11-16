#include "GSCPixel.hpp"
GSCPixel::GSCPixel(){
    pix = 0;
}
GSCPixel::GSCPixel(const GSCPixel& p){
    pix = p.pix;
}
GSCPixel::GSCPixel(unsigned char value){
    pix = value;
}
int GSCPixel::getPixVal(){
    int num = static_cast<int>(pix);
    return num;
}
unsigned char GSCPixel::getValue(){return pix;}
void GSCPixel::setValue(unsigned char value){pix=value;}
bool GSCPixel::isGray(){
    return true;
}