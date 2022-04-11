
#include "wordcounter.h"

bool wordcounter::update(const char* key)
{
      // check if key already exists
      int keyIndex = this->findKey(key);
      if (  keyIndex != -1 )
      {
          // if key exists, increment its value
          int incrementedValue = arrPair[keyIndex]->getValue() + 1; // 
          int sortIndex = keyIndex - 1;
          while ( sortIndex >= 0 && incrementedValue > arrPair[sortIndex]->getValue() )
          {
            sortIndex--;
          }

          // Switch elements, move the incremented element up
          *arrPair[keyIndex] = *arrPair[sortIndex + 1];
          arrPair[sortIndex + 1]->updatePair( key, incrementedValue );
          return true;
      }
      else
      {
          // If it does not exist, create a new entry
          arrPair[arrSize++] = new wordpair( key, 1 );

          return true;
      }
      return false;
}

int wordcounter::findKey(const char* key) 
{
    for ( int i = 0; i < arrSize; i++)
    { 
        if ( strcmp(arrPair[i]->getKey(), key ) == 0 )
        {
        return i;
        }
    }

    // if we can't find anything
    return -1;
}

void wordcounter::flush()
{
    for ( int i = 0; i < arrSize; i++)
    {
        std::cout << "word : " << arrPair[i]->getKey() << " - " << arrPair[i]->getValue() << std::endl;
    }
}

wordcounter::~wordcounter() {
    for (int i = 0; i < arrSize; ++i)
    {
        delete arrPair[i];
    }

    delete [] arrPair;
}
