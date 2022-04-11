#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <iostream>
#include <string.h>
#include "wordpair.h"

class wordcounter
{
private:
  wordpair **arrPair;
  const int MAX = 20000;
  
  int arrSize = 0 ;

public:
  wordcounter() { arrPair = new wordpair *[MAX](); }

  bool update(const char* key);

  int findKey(const char* key);

  void flush();

  int size() { return arrSize; };

  ~wordcounter();

};

#endif WORDCOUNTER_H
