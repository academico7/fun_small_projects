#include <iostream>
#include <string.h>
#include <fstream> 
#include <errno.h>

#include <string>
#include <sstream>

const char remov_chars[5] = {',','.','"','!','?'};

const unsigned long int TABLE_SIZE = 20000;

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

// Hash node class template
template <typename K, typename V>
class HashNode {
public:
    HashNode(const K &ky, const V &value) :
    value(value), next(NULL) {
    key = new char[30];
    strcpy(key, ky);
    }

    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    void setValue(V value) {
        HashNode::value = value;
    }

    void incrmValue() {
        ++HashNode::value;
    }

    HashNode *getNext() const {
        return next;
    }

    void setNext(HashNode *next) {
        HashNode::next = next;
    }

    ~HashNode()
    {
      delete[] key;
    }

private:
    // key-value pair
    K key;
    V value;
    // next bucket with the same key
    HashNode *next;
};

// Default hash function class
template <typename K>
struct KeyHash {
    unsigned long operator()(const K& key) const
    {
        long h = 19937;
        // std::stringstream convert;
    
        // // convert the parameter to a string using "stringstream" which is done
        // // so we can hash multiple datatypes using only one function
        // convert << key;
        
        // std::string temp = convert.str();

        for(unsigned x=0; key[x] != '\0'; ++x)
        {
            h = (h << 6) ^ (h >> 26) ^ key[x];
        }

        return abs(h % TABLE_SIZE);

        //return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

// Hash map class template
template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
public:
    HashMap() {
        // construct zero initialized hash table of size
        table = new HashNode<K, V> *[TABLE_SIZE]();
    }

    ~HashMap() {
        // destroy all buckets one by one
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode<K, V> *entry = table[i];
            while (entry != NULL) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = NULL;
        }
        // destroy the hash table
        delete [] table;
    }

    void flush() {
        //unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[0];
        std::cout << " ola " << entry->getKey() << std::endl;
        while (entry != NULL) {
            std::cout << "Key : " <<  entry->getKey() << " Value: " << entry->getValue() << std::endl;
            entry = entry->getNext();
        }
    }

    V get(const K &key) {
        unsigned long hashValue = hashFunc(key);
        //std::cout << "GET key " << key << " hashvalue " << hashValue << std::endl;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL) {
                         //   std::cout << "GET2 key " << entry->getKey() << " addr " << entry->getKeyaddr() << " value " << entry->getValue() << std::endl;

            if (strcmp(entry->getKey(), key) == 0) {

                return entry->getValue();
            }
            entry = entry->getNext();
        }
        return NULL;
    }

    void put(const K &key) {

        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];



        while (entry != NULL && (strcmp(entry->getKey(), key) != 0)) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            entry = new HashNode<K, V>(key, 1);
       // std::cout << "PUT2 key  " << entry->getKey() << " addr " << entry->getKeyaddr() << " value  " << entry->getValue() << std::endl;

            if (prev == NULL) {
                // insert as first bucket
                table[hashValue] = entry;

            } else {
                prev->setNext(entry);
            }
        } else {
            // increment value
            entry->incrmValue();
            //std::cout << "PUT3 key  " << entry->getKey() << " value  " << entry->getValue() << std::endl;
        }

      // if ( hashValue == 9431 ){
      // HashNode<K, V> *immm = table[9431];
      // HashNode<K, V> *lol = table[9484];
      // std::cout << "PUT5 key "  << " hello " << immm->getKey() << " imm " << lol->getKey() << std::endl;
      // }
    }

    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            // key not found
            return;
        }
        else {
            if (prev == NULL) {
                // remove first bucket of the list
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }

private:
    // hash table
    HashNode<K, V> **table;
    F hashFunc;
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

  std::ifstream f_in("/mnt/c/repo/file_word_counter/src/moby_dick_novel.txt", std::ios::in | std::ios::binary);
  HashMap<char*, int> wordmap;
  char wrd[30];

  if ( !f_in )
    std::cout << "Unable to open file, reason: " << strerror(errno) << std::endl;

	while (f_in >> wrd) 
	{
    char* proc_w = process_word(wrd);
    if ( proc_w != "_invalid_" )
    {
      //std::cout <<"before put " <<  wordmap.get("imm") << std::endl;

      wordmap.put(proc_w);
      //std::cout << "after put " << wordmap.get("imm") << std::endl;
      // if ( !res )
      // {
      //   std::cout << "Something went wrong, cannot add word : " << proc_w << std::endl;
      // }
    }
  }



  char* aux = "the";
  auto res = wordmap.get(aux);
  std::cout << aux << " apperances: " << res << std::endl;  

  // TODO
  // remove specific characters from word terminations - , . " !
  // Take care of hifened words e.g. jaw-bone
  // https://github.com/aozturk/HashMap/blob/master/hashmap/HashMap.h
  // https://aozturk.medium.com/simple-hash-map-hash-table-implementation-in-c-931965904250
  //https://www.programmingnotes.org/3399/c-custom-template-hash-map-with-iterator-using-separate-chaining/
}




