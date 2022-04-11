#ifndef WORDPAIR_H
#define WORDPAIR_H

#include <string.h>

class wordpair
{
private:
  char* key;
  int value;

public:
  wordpair(const char* ky, const int& v):
  value{v}
  {
    key = new char[30];
    strcpy(key, ky);
  }

  void setValue(const int& val) {
    value = val;
  }

  void updatePair(const char* ky, const int val) {
    value = val;
    strcpy(key, ky);
  }

  char* getKey() const {
    return key;
  }

  int getValue() const {
    return value;
  }

  wordpair &operator=( wordpair& pair) {
    strcpy(key, pair.getKey());
    value = pair.getValue();
    return *this;
  }

  ~wordpair()
  {
    delete[] key;
  }

};

#endif WORDPAIR_H