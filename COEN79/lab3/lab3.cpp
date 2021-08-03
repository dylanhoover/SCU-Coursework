//Dylan Hoover COEN 79
//Lab 3
//4/1/2020

//CAPACITY = 50

#include <cassert>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "sequence1.h"


using namespace std;

namespace coen79_lab3{

    //constructor
    //initialize code
    sequence::sequence(){
        this->length = 0;
        this->cur = 0;
    }

    //go to the start of the sequence
    void sequence::start(){
        cur = 0;
    }

    //go to the end of the sequence
    void sequence::end(){
        cur = length-1;
    }
    //go to the last possible space
    void sequence::last(){
        cur = CAPACITY-1;
    }

    //move forward one space
    void sequence::advance(){
        assert(is_item());
        if(cur < length)
            cur++;
    }

    //move back one space
    void sequence::retreat(){
        if(cur > 0){
            cur--;
        }
    }

    void sequence::insert(const value_type& entry){
        assert(size() < CAPACITY);
        if(length == 0){ //if there are no elements insert at the first element
            data[length] = entry;
            cur = 0;
        }
        else { //if there are elements insert at the front
            for(int i = length; i >=cur+1; --i){
                data[i] = data[i-1];
            }
            data[cur] = entry; //set the current space to entry
        }
        length++; //increase length of list
    }

    void sequence::attach(const value_type& entry){
        assert(size() < CAPACITY); //size has to be less than the maximum capacity
        if(!is_item()){ //if there is no current item
            data[length] = entry; //adds item to end of the list
        }
        else{
            for(int i = length; i > cur+1; --i){ //if there is a current item
                data[i] = data[i-1];
            }
            data[cur+1] = entry; //place entry after current
            cur++;
        }
        length++;
    }

    void sequence::remove_current(){
        assert(is_item()); //makes sure there is a current item
        for(int i = cur+1; i <length; ++i){ 
            data[i-1] = data[i]; //shifts the numbers down in the list
        }
        length--;
    }

    void sequence::insert_front(const value_type& entry){
        assert(size() < CAPACITY); //makes sure the sequence isn't full
        cur = 0; //sets current to the first spot
        insert(entry); //insert
        length++;
    }

    void sequence::attach_back(const value_type& entry){
        assert(size() < CAPACITY);
        data[length] = entry; //insert at the end of the list
        length++; //increase length
    }

    void sequence::remove_front(){
        assert(is_item()); 
        for(int i = 0; i < length-1; ++i) 
            data[i] = data[i+1]; //shift everything down to remove the front
        length--; //decrase length
    }

    void sequence::operator +=(const sequence& rhs){
        assert((length + rhs.length) < CAPACITY); //makes sure the capacity hasn't been reached
        size_type tmp = rhs.length; //temp list from rhs for size
        for(int i = 0; i < tmp; i++) { //goes from 0 to the end of the rhs length
            data[length++] = rhs.data[i]; //copy and add the numbers
        }
    }

    sequence::size_type sequence::size() const {
        return length;
    }


    bool sequence::is_item() const{
        if(cur < length) //if current is less than length than there is a current
            return true;
        return false;
    }

    //returns current item
    sequence::value_type sequence::current() const {
        assert(is_item());
        return data[cur];
    }
    
    
    sequence::value_type sequence::operator[](int index) const {
        assert(index < length); //makes sure index is within the length
        return data[index]; //return the number at that index
    }
    
    double sequence::mean() const {
        double sum=0.0; //initialize sum
        for(int i = 0; i < length; ++i) { //go through the numbers
            sum += data[i];
        }
        return sum/size(); //find the mean
    }

    double sequence::standardDeviation() const {    
        double stdev = 0.0;
        for(int i = 0; i < length; ++i) {
            stdev += pow(data[i] - mean(), 2);
        }
        return sqrt(stdev/length); 
    }
    
    sequence operator+(const sequence& lhs, const sequence& rhs){
        assert((lhs.size() + rhs.size()) <= sequence::CAPACITY); //makes sure capacity isn't reached
        sequence(tmp); //create new sequence
        tmp += lhs; //add the lhs
        tmp += rhs; //add rhs
        return tmp; //return the sequence
    }
    
    sequence::value_type summation(const sequence& s) {
        sequence temp = s;
        sequence::value_type sum = 0;
        temp.start();
        for(sequence::size_type i = 0; i<temp.size(); i++){
            sum += temp.current();
            temp.advance();
        }
        return sum;
    }   
}