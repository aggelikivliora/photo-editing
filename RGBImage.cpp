#include "RGBImage.hpp"
RGBImage::RGBImage(){
    max_luminocity = 255;
    this->img = new (nothrow) RGBPixel*[height];
    for(int i=0; i<height; i++){
        this->img[i] = new (nothrow) RGBPixel[width];
        for (int j=0; j<width; j++){
            RGBPixel curr_pix(0,0,0) ;
            this->img[i][j] = curr_pix;
        }
    }
}
RGBImage::RGBImage(int h, int w){
    max_luminocity=255;
    width = w;
    height = h;
    this->img = new (nothrow) RGBPixel*[height];
    for(int i=0; i<height; i++){
        //cout<<"i:"<<i<<endl;
        this->img[i] = new (nothrow) RGBPixel[width];
        //this->img[row] = new GSCPixel[width];
        for (int j=0; j<width; j++){
            this->img[i][j].setRed(0);
            this->img[i][j].setGreen(0);
            this->img[i][j].setBlue(0);
        }
    }
}
RGBImage::RGBImage(const RGBImage& img){
    width = img.getWidth();
    height = img.getHeight();
    max_luminocity = img.getMaxLuminocity();
    this->img = new (nothrow) RGBPixel*[height];
    for(int i=0; i<height; i++){
        this->img[i] = new (nothrow) RGBPixel[width];
        for(int j=0; j<width; j++){  // gemizei thn ka8e sthlH
            this->img[i][j].setRed(img.img[i][j].getRed()) ;
            this->img[i][j].setGreen(img.img[i][j].getGreen()) ;
            this->img[i][j].setBlue(img.img[i][j].getBlue());
        }
    }
}
RGBImage::~RGBImage(){
    for(int i=0; i<height; i++){
        delete[] img[i];
    }
    delete[] img;
} 
RGBImage::RGBImage(std::istream& stream){
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
    this->img = new (nothrow) RGBPixel*[height];
    this->img[row] = new RGBPixel[width];
    while(getline(stream, line)){
        stringstream in;
        in.clear();
        in.str(line);
        while(in >> curr){
            unsigned char r = stoi(curr);
            in>>curr;
            unsigned char g = stoi(curr);
            in>>curr;
            unsigned char b = stoi(curr);
            if(col==width){
                col=0;
                row++;
                this->img[row] = new RGBPixel[width];
            }
            if(col==0){

            }
            RGBPixel curr_pix(r,g,b) ;
            this->img[row][col] = curr_pix;
            col++;
        }
    }
} 

Pixel& RGBImage::getPixel(int row, int col) const{
    Pixel &p=img[row][col];
    return p;
}
RGBImage& RGBImage::operator = (const RGBImage& img){
    for(int i=0; i<height; i++){
        delete[] this->img[i];
    }
    delete[] this->img;

    this->width=img.getWidth();
    this->height=img.getHeight();

    this->img = new RGBPixel*[height];
    for(int i=0; i<img.getHeight(); i++){
        this->img[i] = new RGBPixel[width];
        for (int j=0; j<img.getWidth(); j++){
            this->img[i][j].setRed( img.img[i][j].getRed() );
            this->img[i][j].setGreen( img.img[i][j].getGreen() );
            this->img[i][j].setBlue( img.img[i][j].getBlue() );
        }
    }
    return *this;
}
   
Image& RGBImage::operator += (int times) {
    if (times%4==0){
        return *this;
    }
    RGBImage *im;
    if(times%2==0){
        im = new RGBImage{height,width};
    }
    else{
        im = new RGBImage{width,height};
    }
    if( (times%4==1) || (times%4==-3)){
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                im->img[j][height-i-1].setRed( img[i][j].getRed() );
                im->img[j][height-i-1].setGreen( img[i][j].getGreen() );
                im->img[j][height-i-1].setBlue( img[i][j].getBlue() );
            }
        }
    }
    else if((times%4==2)||(times%4==-2)){
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                im->img[j][height-i-1].setRed( img[i][j].getRed() );
                im->img[j][height-i-1].setGreen( img[i][j].getGreen() );
                im->img[j][height-i-1].setBlue( img[i][j].getBlue() );
            }
        }
    }
    else if ( (times%4==3) || (times%4==-1)){
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                im->img[j][height-i-1].setRed( img[i][j].getRed() );
                im->img[j][height-i-1].setGreen( img[i][j].getGreen() );
                im->img[j][height-i-1].setBlue( img[i][j].getBlue() );
            }
        }
    }
    this->operator=(*im);
    delete im;
    return *this;
}
  
Image& RGBImage::operator *= (double factor) {
    int nHeight=height*factor;
    int nWidth = width*factor;
    RGBImage *im = new RGBImage{nHeight,nWidth};

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

            int n11 = static_cast<int>(img[r1][c1].getRed());
            int n12 = static_cast<int>(img[r1][c2].getRed());
            int n21 = static_cast<int>(img[r2][c1].getRed());
            int n22 = static_cast<int>(img[r2][c2].getRed());
            int lum = (n11 + n22 + n12 + n21)/4;        
            im->img[i][j].setRed(lum);

            n11 = static_cast<int>(img[r1][c1].getGreen());
            n12 = static_cast<int>(img[r1][c2].getGreen());
            n21 = static_cast<int>(img[r2][c1].getGreen());
            n22 = static_cast<int>(img[r2][c2].getGreen());
            lum = (n11 + n22 + n12 + n21)/4;        
            im->img[i][j].setGreen(lum);

            n11 = static_cast<int>(img[r1][c1].getBlue());
            n12 = static_cast<int>(img[r1][c2].getBlue());
            n21 = static_cast<int>(img[r2][c1].getBlue());
            n22 = static_cast<int>(img[r2][c2].getBlue());
            lum = (n11 + n22 + n12 + n21)/4;        
            im->img[i][j].setBlue(lum);
        }
    }
    this->operator=(*im);
    delete im;
    return *this;
}
Image& RGBImage::operator !() {
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            int r = static_cast<int>(img[i][j].getRed());
            int g = static_cast<int>(img[i][j].getGreen());
            int b = static_cast<int>(img[i][j].getBlue());
            img[i][j].setRed(255-r);
            img[i][j].setGreen(255-g);
            img[i][j].setBlue(255-b);
        }
    }
    return *this;
}
Image& RGBImage::operator ~() { // EKSISORROPHSH ISTOGRAMATOS
    int arraysize = height*width;
    float array[3][arraysize];
    YUVPixel lumArr[height][width];
    int size=0;
    for(int i=0; i<(arraysize); i++){
        array[0][i] = 0;
        array[1][i] = 0;
        array[2][i] = 0;
    }
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if((i==0)&&(j==0)){
                YUVPixel pix(img[i][j].getRed(), img[i][j].getGreen(), img[i][j].getBlue());
                lumArr[i][j]=pix;
                float num = static_cast<float>(pix.getY());
                array[0][size]=num;
                array[1][size]++;
                size++;
                continue;
            }
            YUVPixel pix(img[i][j].getRed(), img[i][j].getGreen(), img[i][j].getBlue());
            lumArr[i][j]=pix;
            float num = static_cast<float>(pix.getY());
            int f=0;
            int pos = binarySearch(size,array[0],0,size-1,num,f);
            if((f==1)){
                if(pos<0){pos=abs(pos);}
                size++;
                for(int k=size; k>pos; k--){
                    array[0][k]=array[0][k-1];
                    array[1][k]=array[1][k-1];
                }
                array[0][pos]=num;
                array[1][pos]=1;
            }
            else{
                array[1][pos]++;
            }
        }
    }
    for(int i=0; i<size; i++){
        float temp=0;
        temp = (((float)array[1][i])/((float)arraysize)); //katanomh pi8anothtas
        array[1][i]=temp;
        int j=0;
        while(j<i){ //ar8roistikh katanomh pi8anothtas
            temp = temp +array[1][j];
            j++;
        }
        array[2][i] = temp;
    }
    for(int i=0; i<size; i++){
        array[2][i] = floor(array[2][i]*235);
    }
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            int flag=0;
            int temp = static_cast<int>(lumArr[i][j].getY());
            int pos = binarySearch(size,array[0],0,size,temp,flag);
            lumArr[i][j].setY(array[2][pos]);
            img[i][j].setRed(lumArr[i][j].getR());
            img[i][j].setGreen(lumArr[i][j].getG());
            img[i][j].setBlue(lumArr[i][j].getB());
        }
    }
    return *this;
}
int RGBImage::binarySearch(int size,float arr[], int lft, int rt, int x, int& f)
{   int mid=0;
    f=0;
    while (lft <= rt) {
        mid = lft + (rt - lft) / 2;
        if (arr[mid] == x){
            f=0;
            return mid;
        }
        if(lft==rt){
            if(arr[rt] == x){f=0;return rt;}
            else if(arr[rt] < x){f=1; return (rt+1);}
            else if(arr[rt] > x){f=1; return rt;}
        }
        if (arr[mid] < x){
            lft = mid + 1;
        }else{
            rt = mid - 1;
        }
    }
    if(lft>size){
        f=1;
        return size;
    }
    if(rt<0){
        f=1;
        return 0;
    }
    if(arr[lft] > x){ f=1; return (lft); }
    else if(arr[lft] < x){ f=1; return lft-1; }
    return 0;
}
Image& RGBImage::operator *() {
    for(int i=0; i<height; i++){
        for(int j=0; j<width/2; j++){
            int r = static_cast<int>(img[i][width-1-j].getRed());
            int g = static_cast<int>(img[i][width-1-j].getGreen());
            int b = static_cast<int>(img[i][width-1-j].getBlue());
            img[i][width-1-j].setRed( img[i][j].getRed() );
            img[i][j].setRed(r);

            img[i][width-1-j].setGreen( img[i][j].getGreen() );
            img[i][j].setGreen(g);

            img[i][width-1-j].setBlue( img[i][j].getBlue() );
            img[i][j].setBlue(b);
        }
    }
    return *this;
}