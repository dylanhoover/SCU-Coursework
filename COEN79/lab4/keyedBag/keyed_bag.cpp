/***************************************/
/* Dylan Hoover Santa Clara University */
/*       COEN 79 Lab 4 Keyed bag       */
/***************************************/


#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4{

    //constructor
    keyed_bag::keyed_bag(){
        for(int i = 0; i < CAPACITY; i++){
            keys[i] = '\0';
            data[i] = NULL;
        }
        used = 0;
    }

    void keyed_bag::erase(){
        for(int i = 0; i < CAPACITY; i++){
            keys[i] = '\0';
            data[i] = NULL;
        }
        used = 0;
    }

     bool keyed_bag::erase(const key_type& key) {
         assert(used > 0);                          //make sure there are items
         for(int i = 0; i < used; i++) {             //loop through the array
            if(keys[i] == key) {                   //check for the key  
                for(int j = i; j < used-1; j++) {   //go through and shift the array down 
                    keys[j] = keys[j+1];
                    data[j] = data[j+1];
                }

                used--;                            //decrement used
                return true;                       //return true to exit
             }
         }
         return false;                              //if not found return false
     }

    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        assert((size() < CAPACITY) && (has_key(key) == false));
        keys[used] = key;                           
        data[used] = entry;                        
        used++;
    }

    void keyed_bag::operator+=(const keyed_bag& addend) {
        assert(size() + addend.size() <= CAPACITY);                 // Check if both bags don't exceed CAPACITY
        for(int i = 0; i < addend.used; i++) {      // Iterate through addend
            if( !has_key(addend.keys[i]) ) {        // Check if key in addend doesn't exist in `this` bag
                keys[used] = addend.keys[i];        // If doesn't exist, then add the data from addend
                data[used] = addend.data[i];        //     to end of `this` bag's data[] and key[]
                used++;
            }
        }
    }

    bool keyed_bag::has_key(const key_type& key) const {
        for(int i = 0; i < used; i++) {             // Iterate through 0 to used
            if(keys[i] == key) {                    // If we find a match in keys
                return true;                        // Return true
            }
        }
        return false;                               // If we don't find, return false
    }
    
    // Returns data value corresponding to given key
    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
        assert(has_key(key));                       // First check if key exists
        for(int i = 0; i < used; i++) {             // Iterate through 0 to used  
            if(keys[i] == key) {                    // If we find the key
                return data[i];                     // Return the data at i
            }
        }
        return NULL;                                
    }

    keyed_bag::size_type keyed_bag::size( ) const{
        return used;
    }

    keyed_bag::size_type keyed_bag::count(const value_type& target) const{
        size_type count = 0;
        for(int i = 0; i < used; i++){
            if(data[i] == target){
                count++;
            }
        }
        return count;
    }

   // Checks if there is any duplicate key in another bag `otherBag`
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        for(int i = 0; i < otherBag.used; ++i) {    // Iterate from 0 to otherBag.used
            if( has_key(otherBag.keys[i]) ) {       // call has_key on otherBag's key[] per i
                return true;                        // return true on first time we find match
            }
        }
        return false;
    }
    

     keyed_bag operator+(const keyed_bag& b1, const keyed_bag& b2) {
        assert((b1.size()+b2.size()) <= keyed_bag::CAPACITY);       // Check if b1 + b2 sizes is smaller than CAP
        keyed_bag temp;                             // Make temporary bag
        temp += b1;                                 // Call += operator overloaded function on b1
        temp += b2;                                 // Call += operator overloaded function on b2
        return temp;                                // Return new bag object
    }
}

