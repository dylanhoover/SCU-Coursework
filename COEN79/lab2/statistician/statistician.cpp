// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert> //Provides assert
#include <iostream>
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
    //constructor calls reset()
    statistician::statistician(){
        this->reset();
    }

    //takes in the given double and puts it into the class
    void statistician::next(double r){
        this->last = r; //sets last number inputed to new doulbe
        if(this->max < r){ //if max is less than the new number set max to new number
            this->max = r;
        }
        if(this->min > r){ //if min is greater than new number set min to new number
            this->min = r;
        }
        this->len++; //increase the list length
        this->summ += r; //add new number to sum
    }
    
    //returns the last number inputed
    double statistician::lastN() const{
        return this->last;
    }

    //returns the legnth of the array
    int statistician::length() const{
        return this-> len;
    }

    //returns the sum, does not need to check if length > 0
    double statistician::sum() const{
        return this->summ;
    }

    //checks to make sure length > 0, divides the sum by the length to get the mean
    double statistician::mean() const{
        assert(this->len > 0);
        return this->summ/this->len;
    }

    //checks to make sure length > 0, returns the smallest number
    double statistician::minimum() const{
        assert(this->len > 0);
        return this-> min;
    }

    //checks to make sure length > 0, returns the largset number
    double statistician::maximum() const{
        assert(this->len > 0);
        return this->max;
    }

    //rests all the numbers for the object to 0 except min which is set to max int 
    void statistician::reset(){
        this->len = 0;
        this->summ = 0;
        this->min = __INT_MAX__;
        this->max = 0;
        this->last = 0;
    }
    
    //friend function to add two statistician together
    statistician operator + (const statistician &s1, const statistician &s2){
        statistician temp(s1); //creates a temp object from s1
        temp.len += s2.len; //add the length of s1 and s2
        temp.summ += s2.summ; //add the sum of s1 and s2
        if(temp.min < s2.min){ //checks to see which one has the smaller min #
            temp.min = temp.min; //if it's s1 temp keeps its min
        }
        else{
            temp.min = s2.min; //else temp gets s2's min
        }
        if(temp.max > s2.max){ //same as previous 
            temp.max = temp.max;
        }
        else{
            temp.max = s2.max;
        }
        temp.last += s2.last; //add the last numbers added together
        return temp;
    }

    //friend function to multiply a statistician by a scale
     statistician operator * (double scale, const statistician &s) {
        statistician temp(s);
        double swap;
        temp.summ *= scale;
        temp.min *= scale;
        temp.max *= scale;
        temp.last *= scale;
        swap = temp.min; //need to swap min and max when making the numbers negative
        temp.min = temp.max;
        temp.max = swap;
        return temp;
    }

    //friend function to compare two statisticians
     bool operator == (const statistician &s1, const statistician &s2) {
        if (s1.length() == 0 && s2.length() == 0) //if both lengths are 0 then the two objects have to be equal to eachother
            return true;
        else if (s1.length() == s2.length() && s1.sum() == s2.sum() && s1.minimum() == s2.minimum() && s1.maximum() == s2.maximum()) { //if length != 0, must compare the length, sum, min & max and all must be true
            return true;
        }
        else { 
            return false;
        }
    }

} // namespace coen79_lab2
