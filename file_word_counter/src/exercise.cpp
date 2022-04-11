

/*requirements
In memory cache design

Cache
std::string key
std::string data
int delete_time

Read(), write() and delete() (< O(n)) from different threads ( based on key )

1 threads is responsible for deleting ( last modified time )

whenever we write (create new or update existing) to cache, delete_time = current time + 10secs.

read and write are random access

delete is called periodically, and check if current time is bigger than delete_time,
if it is then we delete the struct

*/

struct memCache {


std::string key;
std::string data;
int delete_time;

std::string operator[](std:string &key) {
    return 
}

};

class memCacheManagement {

   std::unorderedmap<std::string, std::string> m_cache; 
   std::unorderedmap<std::string, int> d_time;
   std::mutex m_mutex;

    memCacheManagement() {}
    std::string Read(std::string &key) const { // O(1) worst O(n*log(O))
        m_mutex.lock();


        return m_cache[key];
    }

    bool write(std::string &key, std::string &data)  { // O(1) worst O(n*log(O))
        m_mutex.lock();

        m_cache[key] = data;
        d_time[key] = update_time();
    }

    delete() {
        // loop through data strcuture O(n2)
        //  databse implementation, where deletion should be TTL based
        if ( d_time[key] > current_time ) {
            delete(m_cache[key]);
        }
    }

    



 write() and delete()


}

