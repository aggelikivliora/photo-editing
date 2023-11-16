#ifndef TOKEN_H
#define TOKEN_H
#include "GSCImage.hpp"
#include "RGBImage.hpp"
using namespace std;
class Token {
private:
  string name;
  Image* ptr;
public:
  Token(const Token& t);
  Token();
  Token(const string& , Image*);
  ~Token();
  string getName() const;
  Image& getImage() const;
  Image* getPtr() const;
  void setName(const string& );
};
#endif