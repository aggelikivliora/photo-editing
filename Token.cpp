#include "Token.hpp"
Token::Token(const Token& t){
    if(t.ptr->getPixel(0,0).isGray()){
        GSCImage *g=dynamic_cast< GSCImage*>(t.ptr);
        ptr = new GSCImage(*g);
        //delete g;
    }
    else{
        RGBImage *g=dynamic_cast< RGBImage*>(t.ptr);
        ptr = new RGBImage(*g);
        //delete t.getPtr();
    }
    //ptr = t.ptr;
    name=t.name;
}
Token::Token(){
    ptr=nullptr;
    name="";
}
Token::Token(const string& str, Image* img){
    if(img->getPixel(0,0).isGray()){
        GSCImage *g=dynamic_cast< GSCImage*>(img);
        ptr = new GSCImage(*g);
        //delete img;
    }
    else{
        RGBImage *g=dynamic_cast< RGBImage*>(img);
        ptr = new RGBImage(*g);
       // delete img;
    }
    //ptr = img;
    name = str;
}
Token::~Token(){
    delete ptr;
}

string Token::getName() const{
    return name;
}
Image& Token::getImage() const{
    return *ptr;
}
Image* Token::getPtr() const{
    return ptr;
}
void Token::setName(const string& str){
    name = str;
}
