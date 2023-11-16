#include "Token.hpp"
#include <iostream>
#ifndef VECTOR1_H
#define VECTOR1_H
#include <vector>
#endif
class Database {
public:
    std::vector<Token> tokens;
public:
  Database();
  ~Database();
  void add(Token& tkn);
  bool dlt(string tkn);
  bool exist(string str);
  int find(string str);
};