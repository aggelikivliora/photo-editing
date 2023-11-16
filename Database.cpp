#include "Database.hpp"
Database::Database(){}
Database::~Database(){
    std::vector<Token> vec;
    vector<Token>().swap(vec);
}
void Database::add(Token& tkn){
    tokens.push_back(tkn);
}
bool Database::exist(string str){
    for(Token curr : tokens){
        if(curr.getName().compare(str)==0){
            return true;
        }
    }
    return false;
}
bool Database::dlt(string tkn){
    int i=0;
    for(Token curr : tokens){
        if(curr.getName().compare(tkn)==0){
            tokens.erase(tokens.begin()+i);
            return true;
        }
        i++;
    }
    return false;
}
int Database::find(string str){
    int end = tokens.size();
    for(int j=0; j<end; j++){
        if(tokens.at(j).getName().compare(str)==0){
            return j;
        }
    }
    return -1;
}

