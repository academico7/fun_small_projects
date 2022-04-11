#include <iostream>
#include <string.h>
#include <fstream> 
#include <errno.h>
#include <chrono>

const char remov_chars[5] = {',','.','"','!','?'};

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

  void updatePair(const char* ky, const int val)
  {
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


class wordcounter
{
private:
  wordpair **arrPair;
  const int MAX = 20000;
  
  int arrSize = 0 ;

public:
  wordcounter()
  {
        arrPair = new wordpair *[MAX]();
  }

  bool update(const char* key)
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

  int findKey(const char* key) 
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

  void flush_20()
  {
    for ( int i = 0; i < 20 ; i++)
    {
      std::cout << "word : " << arrPair[i]->getKey() << " - " << arrPair[i]->getValue() << std::endl;
    }
  }

  int size()
  {
    return arrSize;
  }

  ~wordcounter() {
      for (int i = 0; i < arrSize; ++i)
      {
          delete arrPair[i];
      }

      delete [] arrPair;
  }
};

// 65-90 upper case 97-122 lower case
bool is_valid_char (char c) 
{  
  return (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '\'' ;
}

bool is_removable(char c)
{
  for(int i = 0; remov_chars[i] != '\0'; i++)
  {
    if ( c == remov_chars[i] )
      return true;
  }
  return false;
}

char* process_word(char *word)
{
    // Check if character is valid and change to lower case
    for ( int i=0; word[i] != '\0'; i++ ) {

      if ( !is_valid_char(word[i]) )
      {
        return (char*)"_invalid_";
      }
      word[i] = (char)tolower(word[i]);
    }

    return word;
}

int main() {
  // Performance Check
  using namespace std::chrono;  
  auto start = high_resolution_clock::now();


  std::ifstream f_in("/mnt/c/repo/file_word_counter/src/moby_dick_novel.txt", std::ios::in | std::ios::binary);
  wordcounter wordmap;
  char wrd[30];

  if ( !f_in )
    std::cout << "Unable to open file, reason: " << strerror(errno) << std::endl;

	while (f_in >> wrd) 
	{
    char* proc_w = process_word(wrd);
    if ( proc_w != "_invalid_" )
    {
      bool res = wordmap.update(proc_w);

      if ( !res )
      {
        std::cout << "Something went wrong, cannot add word : " << proc_w << std::endl;
      }
    }
  }

  wordmap.flush_20();
  std::cout << "Map size : " << wordmap.size() << std::endl;  

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;
  //Performance of 1.2 seconds
}




