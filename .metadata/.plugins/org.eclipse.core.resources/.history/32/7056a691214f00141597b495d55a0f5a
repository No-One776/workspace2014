//
//  gvsu_alloc.hpp
//  CS263-HW3
//
//  Created by Hans Dulimarta (Fall 2014)
//

#ifndef CS263_gvsu_alloc_hpp
#define CS263_gvsu_alloc_hpp

#include <iostream>
#include <cstddef>
#include <memory>
#include <typeinfo>
#include <map>

using namespace std;
template<class T>
class GVSU_Allocator : public std::allocator<T> {
private:
    static GVSU_Allocator* _instance;
    static int alloc_count, dealloc_count;
    static map<T*,unsigned long> alloc_map;
    GVSU_Allocator() { /* hide the constructor in the private section */ }
public:
    
    static GVSU_Allocator* get_instance() {
        /* singleton design pattern, allow only a single instance of this object */
        if (_instance == nullptr)
            _instance = new GVSU_Allocator;
        return _instance;
    }
    
    /* Handle memory allocation, keep track of memory address and size
       in a map */
    T* allocate(size_t num, const void* hint = 0) {
        alloc_count++;
        /* determine the required number of bytes */
        unsigned long size = num * sizeof(T);
        
        /* use the "global" new to allocate the storage */
        T* address = static_cast<T*>(::operator new(size));
        
        /* record this request in the map */
        alloc_map[address] = size;
        return address;
    }
    
    /* handle memory deallocation */
    void deallocate (T* ptr) {
        dealloc_count++;
        
        /* remove the record from the map */
        alloc_map.erase(ptr);
        
        /* use the "global" delete to deallocate */
        return ::operator delete(ptr);
    }
    
    static void report (const string& tname) {
        cout << "Allocation summary of " << tname << " data" << endl;
        cout << "Allocation count " << alloc_count << endl;
        cout << "Deallocation count " << dealloc_count << endl;
        int bytes = 0;
        
        /* Print unallocated memory segments */
        for (auto it = alloc_map.begin(); it != alloc_map.end(); ++it) {
            cout << dec << setw(5) << it->second << " bytes at " << hex << it->first << endl;
            bytes += it->second;
        }
        cout << "Total amount of memory leak " << dec << bytes << " bytes" << endl;
    }
    
    static pair<int,int> allocation_status() {
        return make_pair(alloc_count, dealloc_count);
    }
};

#endif
