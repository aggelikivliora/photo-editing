#include "GSCImage.hpp"
#include "Database.hpp"
Image* readNetpbmImage(const char* filename){
    std::ifstream f(filename);
    if(!f.is_open()){
        std::cout << "[ERROR] Unable to open "<< filename<<std::endl;
    }
    Image* img_ptr = nullptr;
    std::string type;

    if(f.good() && !f.eof()){
        f>>type;
    }
    if(!type.compare("P3")){
        img_ptr = new RGBImage(f);
    }
    else if(!type.compare("P2")){
        img_ptr = new GSCImage(f);
    }
    else if(f.is_open()){
        std::cout <<"[ERROR] Invalid file format" << std::endl; 
    }
    return img_ptr;
}
int main(){
    Database *token = new Database(); 
    while(true){
        std::string command[6];
        std::string line;
        std::getline(std::cin,line);
 
        int num=0;
        istringstream l(line);
        string word;
        while ((l >> word)&&(num<6)){
            command[num]=word;
            num++;
        }
        num = command[0].length();
        if(num>1){
            cout <<"\n --Invalid command!-- "<<endl;
            continue;
        }
        if(command[0]=="i"){
            std::string filename=command[1];
            std::string tkn=command[3];
            if((command[2]!="as") || (tkn[0]!='$')){
                cout <<"\n --Invalid command!-- "<<endl;
                continue;
            }        
            int size = filename.length();
            char file[size];
            for(int i=0; i<size; i++){
                file[i]=filename[i];
            }
            file[size]='\0';
            Image *img = readNetpbmImage(file);
            if(img==nullptr){
                continue;
            }
            if(!token->exist(tkn)){
                Token t(tkn,img);
                token->add(t);
                cout << "[OK] Import $token" << endl;
            }
            else{
                cout << "[ERROR] Token "<<tkn<<" exists" << endl;
            }
            delete img;
            continue;
        }
        else if (command[0] == "e") { // EKSAGWGH ARXEIOU EIKONAS
            std::string filename=command[3];
            std::string tkn=command[1];
            std::string line;
            if((command[2]!="as") || (tkn[0]!='$')){
                cout <<endl <<"-- Inavalid command! --"<<endl;
                continue;
            } 
            int pos = token->find(tkn);
            if(pos==-1){
                cout <<"[ERROR] Token "<<tkn<<" not found!"<<endl;
                continue;
            }
            if(token->tokens.at(pos).getPtr()->getPixel(0,0).isGray()){
                filename.append(".pgm");
            }
            else{
                filename.append(".ppm");
            }
            fstream file(filename.c_str());
            if(!file){
                file.open(filename, ios::out);
                if(!file.is_open()){
                    std::cout << "[ERROR] Unable to open "<<filename<<std::endl;
                    continue;
                }
                else{
                    file << token->tokens.at(pos).getImage();
                    file.close();
                }
            }
            else{
                cout << "[ERROR] File "<<filename<<" exists" << endl;
                continue;

            }
            cout << "[OK] Export "<<tkn<<endl;   
        }
        else if(command[0]=="d"){
            std::string tkn=command[1];
            if((tkn[0]!='$')){
                cout <<endl <<"-- Inavalid command! --"<<endl;
                continue;
            }   
            if(token->dlt(tkn)){
                cout<<"[OK] Delete "<<tkn<<endl;
            }
            else{
                cout <<"[ERROR] Token "<<tkn<<" not found!"<<endl;
            }
        }
        else if(command[0]=="n"){
            std::string tkn=command[1];
            if((tkn[0]!='$')){
                cout <<endl <<"-- Inavalid command! --"<<endl;
                continue;
            } 
            int pos = token->find(tkn);
            if(pos==-1){
                cout <<"[ERROR] Token "<<tkn<<" not found!"<<endl;
                continue;
            }
            token->tokens.at(pos).getImage().operator!();
            cout<<"[OK] Color Inversion "<<tkn<<endl;
        }

        else if(command[0]=="z"){
            std::string tkn=command[1];
            if((tkn[0]!='$')){
                cout <<endl <<"-- Inavalid command! --"<<endl;;
                continue;
            }
            int pos = token->find(tkn);
            if(pos==-1){
                cout <<"[ERROR] Token "<<tkn<<" not found!"<<endl;
                continue;
            }
            token->tokens.at(pos).getPtr()->operator~();
            cout<<"[OK] Color Equalize "<<tkn<<endl;
        }

        else if(command[0]=="m"){
            std::string tkn=command[1];
            if((tkn[0]!='$')){
                cout <<endl <<"-- Inavalid command! --"<<endl;
                continue;
            } 
            int pos = token->find(tkn);
            if(pos==-1){
                cout <<endl <<"-- Inavalid command! --"<<endl;
                continue;
            }
            token->tokens.at(pos).getImage().operator*();
            cout<<"[OK] Mirror "<<tkn<<endl;
        }

        else if(command[0]=="g"){
            std::string tkn=command[1];
            if((tkn[0]!='$')){
                cout <<endl <<"-- Inavalid command! --"<<endl;
                continue;
            }
            int pos = token->find(tkn);
            if(pos==-1){
                cout <<"[ERROR] Token "<<tkn<<" not found!"<<endl;
                continue;
            }
            if(token->tokens.at(pos).getImage().getPixel(0,0).isGray()){
                cout << "[NOP] Already grayscale "<<tkn<<endl;
            }
            else{
                RGBImage* i = dynamic_cast<RGBImage*>(token->tokens.at(pos).getPtr());
                Image* pt=new GSCImage(*i);
                Token t(tkn, pt);
                token->dlt(tkn);
                token->add(t);
                delete pt;
                cout << "[OK] Grayscale "<<tkn<<endl;
            }
        }
        else if(command[0]=="s"){
            std::string tkn=command[1];
            std::string by=command[2];
            std::string factor=command[3];
            if((tkn[0]!='$') || (by.compare("by")!=0)){
                cout <<endl <<"-- Inavalid command! --"<<endl;
                continue;
            }
            int size=factor.size(), flag=1;
            for(int i=0; i<size; i++){
                if(!isdigit(factor[i])){
                    if(factor[0]=='-'){
                        flag =0;
                        cout <<endl <<"-- Inavalid command! --"<<endl;
                        break;
                    }
                    if(factor[i]=='.'){
                        flag=1;
                        continue;
                    }
                }
            }
            if(flag==0){continue;}
            double num = stod(factor);
            if((num>2) || (num<=0)){
                cout <<endl <<"-- Inavalid command! --"<<endl;
                continue;
            }
            int pos = token->find(tkn);
            if(pos==-1){
                cout <<"[ERROR] Token "<<tkn<<" not found!"<<endl;
                continue;
            }
            token->tokens.at(pos).getImage().operator*=(num);
            cout<<"[OK] Scale "<<tkn<<endl; 
        }
        else if(command[0]=="r"){
            std::string tkn=command[1];
            std::string clock=command[2];
            std::string times=command[4];
            std::string num=command[3];
            if((tkn[0]!='$') || (clock.compare("clockwise")!=0) || (times.compare("times")!=0)){
                cout <<endl <<"-- Inavalid command! --"<<endl;
                continue;
            }
            int size=num.size(), flag=1;
            for(int i=0; i<size; i++){
                if(!isdigit(num[i])){
                    if(num[0]=='-'){
                        continue;
                    }
                    flag =0;
                    cout <<endl <<"-- Inavalid command! --"<<endl;
                    break;
                }
            }
            if(flag==0){continue;}
            int pos = token->find(tkn);
            if(pos==-1){
                cout <<"[ERROR] Token "<<tkn<<" not found!"<<endl;
                continue;
            }
            token->tokens.at(pos).getImage().operator+=(stoi(num));
            cout << "[OK] Rotate" << tkn <<endl;
        }
        else if(command[0]=="q"){
            delete token;
            return 0;
        }
    }

}