#include <iostream>
#include <string.h>
#include <fstream> 
#include <errno.h>
#include <chrono>
#include <string>
#include <unordered_map>

const short int NRCOMMONWORDS = 20;

class wordpair
{
private:
    char* key;
    int value;

    // same key (hashed) element(s)
    wordpair *next;

public:
  wordpair(const char* ky, const int& v):
  value{v}  
  {
    key = new char[30];
    strcpy(key, ky);
  }

  void incrmValue() {
      value++;
  }

  char* getKey() const {
    return key;
  }

  int getValue() const {
    return value;
  }

  void setNext(wordpair *nxt) {
      next = nxt;
  }

  wordpair *getNext() const {
      return next;
  }

  ~wordpair() {
    delete[] key;
  }

};

struct HashFunc {
    unsigned long operator()(const char* &key, const int &table_size) const {
        long h = 19937;

        for(unsigned i=0; key[i] != '\0'; ++i)  {
            h = (h << 6) ^ (h >> 26) ^ key[i];
        }

        return abs(h % table_size);
    }
};

class wordcounter
{
private:
  wordpair **arrPair;
  HashFunc hfunc;
  const int TABLE_SIZE;
  
  int arrSize = 0 ;

public:
  wordcounter(const int &table_size):
  TABLE_SIZE{table_size}
  {
        arrPair = new wordpair *[TABLE_SIZE]();
  }

  int get(const char* key) {
      unsigned long hValue = hfunc(key, TABLE_SIZE);
      wordpair *current = arrPair[hValue];

      while (current != NULL) {

          // Check if key matches otherwise check for common hashed elements
          if (strcmp(current->getKey(), key) == 0) {
              return current->getValue();
          }
          current = current->getNext();
      }
      return NULL;
  }

  void update(const char* key)  {
        unsigned long hValue = hfunc(key, TABLE_SIZE);
        wordpair *previous = NULL;
        wordpair *current = arrPair[hValue];

        // check if the first found element matches the key
        while (current != NULL && (strcmp(current->getKey(), key) != 0)) {
            previous = current;
            current = current->getNext();
        }

        // Insert or increment depending if the element already exists
        if (current == NULL) {
            current = new wordpair(key, 1);

            if (previous == NULL) {
                // insert first element
                arrPair[hValue] = current;

            } else {
                previous->setNext(current);
            }
        } else {
            // increment value
            current->incrmValue();
        }
  }

  ~wordcounter() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            wordpair *entry = arrPair[i];
            while (entry != NULL) {
                wordpair *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            arrPair[i] = NULL;
        }
      delete [] arrPair;
  }
};

// 65-90 upper case 97-122 lower case
bool is_valid_char (char c) 
{  
  return (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '\'' ;
}

char* process_word(char *word)
{
    // Check if character is valid and change to lower case
    for ( int i=0; word[i] != '\0'; i++ ) {
      if ( !is_valid_char(word[i]) )  {
        return (char*)"_invalid_";
      }
      word[i] = (char)tolower(word[i]);
    }

    return word;
}

bool word_exist( char **wordsArray, const char* wordMatch , int size) {

    for ( int i = 0; i < size ; i++) {
        if ( strcmp(wordMatch, wordsArray[ i ]) == 0 ) {
          return true;
        }
    }
    return false;
}

int partition (char **arr, std::unordered_map<std::string, int> &wc, int lowLimit, int high)
{
    char* pivot = arr[high];    // pivot
    int i = (lowLimit - 1);  // Index of smaller element

    for (int j = lowLimit; j <= high- 1; j++) {
        // If current element is smaller than or  
        // equal to pivot
        if (wc[arr[j]] <= wc[pivot])  {
            i++;    // increment index of smaller element
            std::swap(arr[i], arr[j]);       
        }   
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Average time complexity O(n*log(n))
void quickSort(char **arr, std::unordered_map<std::string, int> &wc, int lowLimit, int highLimit)
{
    if (lowLimit < highLimit) {
        // Pick a pivor and order the other elements
        int pi = partition(arr, wc, lowLimit, highLimit);
 
        // Call the algorithm recursevly until the sorting is done
        quickSort(arr, wc, lowLimit, pi - 1);
        quickSort(arr, wc, pi + 1, highLimit);
    }
}

int main() {
  // Performance Check
  using namespace std::chrono;  
  auto start = high_resolution_clock::now();


  std::ifstream f_in("/mnt/c/repo/file_word_counter/src/moby_dick_novel.txt", std::ios::in | std::ios::binary);

  // word table size is set when instantiating the object, it could come from user input.
  //wordcounter wordmap(20000);
  char wrd[30];
  std::unordered_map<std::string, int> wordmap;
  char ** mostCommon = new char *[NRCOMMONWORDS];
  short int m_size = 0;
  bool is_new;

  if ( !f_in )  {
    std::cout << "Unable to open file, reason: " << strerror(errno) << std::endl;
    std::exit(1);
  }

	while (f_in >> wrd) {
    char* proc_w = process_word(wrd);

    //std::cout << " access " << wordmap["dsadsa"] << std::endl;

    if ( proc_w != "_invalid_" )  {
      wordmap[std::string(proc_w)] = ++wordmap[proc_w] ;

      //** Sorting **
      // The sorting part could be put within the wordcounter class but I just thought it would polute the data structure
      // The decision about where to place the functionality would be made depending on the requirements

      // check if word already exists 
      if ( word_exist(mostCommon, proc_w, m_size) ) {
        quickSort(mostCommon, wordmap, 0, m_size - 1);
        continue;
      }

      if ( m_size < NRCOMMONWORDS ) {
        mostCommon[ m_size ] = new char[30];
        strcpy(mostCommon[ m_size++ ],  proc_w);
      }
      else if (wordmap[proc_w] > wordmap[mostCommon[ 0 ]])  {
        strcpy(mostCommon[ 0 ], proc_w);
      }
    }    
  }

  // Print 20 most common words
  for( int i = m_size-1; i >= 0 ; i--)  {
    std::cout << wordmap[mostCommon[i]] << " - " << mostCommon[i]  << std::endl;
  }

  // Memory clean-up
  delete [] mostCommon; 

  // Performance of 0.727 seconds
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;
}




