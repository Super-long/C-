#include <map>
#include <string>
#include <mutex> //mutex
#include <thread>
#include <iostream>
#include <boost/thread/shared_mutex.hpp> // shared_mutex

using namespace std;

class dns_cache{
    private:
        std::map<string, string> entrise;
        mutable boost::shared_mutex entry_mutex;
    public:
        string find_entry(const string& key) const {
            boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
            auto entry = entrise.find(key);
            if(entry == entrise.end()) return string();
            return entry->second;
        }

        void update_entry(const string& key, const string& value){
            std::lock_guard<boost::shared_mutex> guard(entry_mutex);
            entrise[key] = value;
        }

        size_t size() const {
            return entrise.size();
        }
};

int main(){
    vector<std::thread> vec(100);
    vector<std::thread> vec_(100);
    dns_cache cache;
    for(int i = 0; i < 100; i++){
        string str(10,i);
        vec[i] = std::thread(&dns_cache::update_entry, &cache,str, "two");
    }
    for(int i = 0; i < 100; i++)
    {
        string str(10,i);
        vec_[i] = std::thread(&dns_cache::find_entry, &cache,str);
    }
    for_each(vec_.begin(), vec_.end(), std::mem_fn(&std::thread::join));    
    for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));
    cout << cache.size() << endl;
}

// g++ boost_share_mutex.cpp -pthread -lboost_system -lboost_thread