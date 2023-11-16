#include "GSCImage.hpp"
GSCImage::GSCImage(){
    max_luminocity=255;
    this->img = new (nothrow) GSCPixel*[height];
    for(int i=0; i<height; i++){
        this->img[i] = new (nothrow) GSCPixel[width];
        for (int j=0; j<width; j++){
            GSCPixel curr_pix(0) ;
            this->img[i][j] = curr_pix;
        }
    }
}
GSCImage::GSCImage(int h, int w){
    max_luminocity=255;
    width = w;
    height = h;
    this->img = new GSCPixel*[height];
    for(int i=0; i<height; i++){
        this->img[i] = new GSCPixel[width];
        for (int j=0; j<width; j++){
            this->img[i][j].setValue(0);
        }
    }
}
GSCImage::GSCImage(const GSCImage& img){
    width = img.getWidth();
    height = img.getHeight();
    max_luminocity = img.getMaxLuminocity();
    this->img = new  GSCPixel*[height];
    for(int i=0; i<height; i++){
        this->img[i] = new GSCPixel[width];
        for(int j=0; j<width; j++){
            Pixel *i_p= &img.getPixel(i,j);
            int myint = i_p->getPixVal();
            unsigned char pixel = myint;
            GSCPixel newpix(pixel);
            this->img[i][j]=newpix;
        }
    }
}
GSCImage::GSCImage(const RGBImage& grayscaled){
    width = grayscaled.getWidth();
    height = grayscaled.getHeight();
    max_luminocity = grayscaled.getMaxLuminocity();

    this->img = new GSCPixel*[height];
    for(int i=0; i<height; i++){
        this->img[i] = new GSCPixel[width];
        for(int j=0; j<width; j++){ 
            Pixel *i_p= &grayscaled.getPixel(i,j);
            int MyInt = i_p->getPixVal();
            unsigned char buffer[4];
	        memcpy(buffer, (char*)&MyInt, 4); //copy 4 bytes from integer to our char buffer
	        int r = static_cast<int>(buffer[0]);
	        int g = static_cast<int>(buffer[1]);
	        int b = static_cast<int>(buffer[2]);
            int curr = ((r*0.3)
                    +(g*0.59)
                    +(b*0.11));
            this->img[i][j].setValue(curr);
        }
    }
}
GSCImage::GSCImage(std::istream& stream){
    std::string line;
    getline(stream, line);
    getline(stream, line);
    stringstream in;
    in.clear();
    in.str(line);
    in>>width;
    in>>height;
    in >>max_luminocity;
    int row=0, col=0;
    std::string curr;
    this->img = new GSCPixel*[height];
    this->img[row] =  new GSCPixel[width];
    while(getline(stream, line)){
        stringstream in;
        in.clear();
        in.str(line);
        while(in >> curr){
            if((col==width)){
                col=0;
                row++;
                this->img[row] = new  GSCPixel[width];
            }
            int num = stoi(curr);
            unsigned char pixel = num;
            this->img[row][col].setValue(pixel);
            col++;
        }
    }
}

GSCImage::~GSCImage(){
    for(int i=0; i<height; i++){
        delete[] img[i];
    }
    delete[] img;
} 

Pixel& GSCImage::getPixel(int row, int col) const {
    Pixel &p=img[row][col];
    return p;
}
GSCImage& GSCImage::operator = (const GSCImage& img){
    for(int i=0; i<height; i++){
        delete[] this->img[i];
    }
    delete[] this->img;
    
    this->width=img.getWidth();
    this->height=img.getHeight();

    this->img = new GSCPixel*[height];
    for(int i=0; i<img.getHeight(); i++){
        this->img[i] = new GSCPixel[width];
        for (int j=0; j<img.getWidth(); j++){
            this->img[i][j].setValue(img.img[i][j].getValue());
        }
    }
    return *this;
}
   
Image& GSCImage::operator += (int times) {
    if (times%4==0){
        return *this;
    }
    GSCImage *im;
    if(times%2==0){
        im = new GSCImage{height,width};
    }
    else{
        im = new GSCImage{width,height};
    }
    if( (times%4==1) || (times%4==-3)){
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                int num = static_cast<int>(img[i][j].getValue());
                im->img[j][height-i-1].setValue(num);
            }
        }
    }
    else if((times%4==2)||(times%4==-2)){
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                int num = static_cast<int>(img[i][j].getValue());
                im->img[height-i-1][width-j-1].setValue(num);
            }
        }
    }
    else if ( (times%4==3) || (times%4==-1)){
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                int num = static_cast<int>(img[i][j].getValue());
                im->img[width-j-1][i].setValue(num);
            }
        }
    }
    this->operator=(*im);
    delete im;
    return *this;
}
Image& GSCImage::operator *= (double factor) {
    int nHeight=height*factor;
    int nWidth = width*factor;
    GSCImage *im = new GSCImage{nHeight,nWidth};

    for(int i=0; i<nHeight; i++){
        for(int j=0; j<nWidth; j++){
            int temp=floor(i/factor);
            int r1 = min(temp,height-1);
            temp=ceil(i/factor);
            int r2 = min(temp,height-1);
                
            temp =floor(j/factor);
            int c1 = min(temp,width-1);
            temp=ceil(j/factor);
            int c2 = min(temp,width-1);

            int n11 = static_cast<int>(img[r1][c1].getValue());
            int n12 = static_cast<int>(img[r1][c2].getValue());
            int n21 = static_cast<int>(img[r2][c1].getValue());
            int n22 = static_cast<int>(img[r2][c2].getValue());

            int lum = (n11 + n22 + n12 + n21)/4;        
            im->img[i][j].setValue(lum);
        }
    }
    this->operator=(*im);
    delete im;
    return *this;
}

Image& GSCImage::operator !() {
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            int num = static_cast<int>(img[i][j].getValue());
            img[i][j].setValue(255-num);
        }
    }
    return *this;
}

Image& GSCImage::operator ~() { 
    RGBImage image(height,width);
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            unsigned char val = img[i][j].getValue();
            image.img[i][j].setRed(val);
            image.img[i][j].setGreen(val);
            image.img[i][j].setBlue(val);
        }
    }
    image.operator~();
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            int r = static_cast<int>(image.img[i][j].getRed());
            int g = static_cast<int>(image.img[i][j].getGreen());
            int b = static_cast<int>(image.img[i][j].getBlue());
            int curr = ((r*0.3)+(g*0.59)+(b*0.11));
            this->img[i][j].setValue(curr);
        }
    }
    return *this;
}
Image& GSCImage::operator *() {
    for(int i=0; i<height; i++){
        for(int j=0; j<width/2; j++){
            int temp;
            temp = static_cast<int>(img[i][width-1-j].getValue());
            img[i][width-1-j].setValue( img[i][j].getValue() );
            img[i][j].setValue(temp);
        }
    }
    return *this;
}
