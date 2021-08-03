/***************************************/
/* Dylan Hoover Santa Clara University */
/*       COEN 79 Lab 5 String class    */
/***************************************/

#include <iostream>
#include <cassert>
#include <string.h>
#include <cctype>
#include "mystring.h"

using namespace std;

namespace coen79_lab5
{
    //constructor from string
    string::string(const char str[ ]){
        current_length = strlen(str);                   //length is determined from str length
        allocated = current_length + 1;                 //alloacte the memory + 1
        characters = new char[allocated];               //create the dynamic memory
        strncpy(characters, str, allocated);            //copy the str into charcters with the allocated length
    }

    //constructor from char
    string::string(char c){
        current_length = 1;                             //length is 1 because there is only a character
        allocated = current_length + 1;                 //allocated length + 1
        characters = new char[allocated];               //create the dynamic memory
        characters[0] = c;                              //put c into character
        characters[1] = '\0';                           //end with NULL CHAR
    }

    //copy constructor from source string
    string::string(const string& source){
        current_length = source.current_length;         //length is from source
        allocated = source.allocated;                   //allocation is from source
        characters = new char[allocated];               //dynamic memory is the same as before
        strncpy(characters, source.characters, source.current_length);

    }

    //destructor
    string::~string(){
        current_length = 0;
        allocated = 0;
        delete[] characters;
    }

    //MODIFICATION MEMBER FUNCTIONS

    //addend (string obj) has been catenated to the end of the string.
    void string::operator+=(const string& addend){
        current_length = current_length + addend.current_length;
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend.characters, addend.current_length);
    }

    //addend (array of chars) has been catenated to the end of the string.
    void string::operator+=(const char addend[]){
        current_length = current_length + strlen(addend);
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend, strlen(addend));
    }
    
    //The single character addend has been catenated to the end of the string.
    void string::operator+=(char addend){
        allocated = current_length + 1;
        reserve(allocated);
        characters[current_length] = addend;
        current_length +=1;
        characters[current_length] = '\0';

    }

    //All functions will now work efficiently (without allocating new memory) until n characters are in the string.
    void string::reserve(size_t n){
        char* temp = new char[n + 1];
        if(characters != NULL){
            strncpy(temp, characters, current_length);
            delete[] characters;
        }
        characters = temp;
    }

    // Assigned source to a pointer of changed string 'this'
    string& string::operator=(const string& source){
        this->dlt(0, current_length);
        if(current_length != source.current_length){
            allocated = source.allocated;
            reserve(allocated);
        }
        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;
        return *this;
    }

    //The source string is inserted into this string before the character at the given index.
    void string::insert(const string& source, unsigned int position){
        assert(position <= length());
        size_t totalLength = current_length + source.current_length;
        if(allocated < totalLength)
            reserve(totalLength);
        for(int i = length(); i > position; i--)
            characters[i] = characters[i-1];
        for(int i = 0; i < source.length(); i++)
            characters[position + i] = source.characters[i];
        current_length = totalLength;
    }

    //num characters are deleted from the sequence, starting at index position.
    void string::dlt(unsigned int position, unsigned int num){
        assert((position + num) <= length());
        for(int i = position; i < length(); i++)
            characters[i] = characters[i+num];
        current_length = current_length - num;
    }

    //the character at the given position in the string is replaced with c
    void string::replace(char c, unsigned int position){
        assert(position <= length());
        characters[position] = c;
    }

    //the characters in this string starting at position are replaced with those in the source srting.
    void string::replace(const string& source, unsigned int position){
        assert((position + source.length()) <= length());
        int i,j;
        for(i = position, j = 0; i < (position + source.length()); i++, j++)
            characters[i] = source[j];
    }

    //CONSTANT MEMBER FUNCTIONS

    //returns the character at the specified position
    char string::operator[](size_t position) const{
        assert(position < length());
        return characters[position];
    }

    //location of first occurance of c is returned
    int string::search(char c) const{
        for(int i = 0; i < length(); i++){
            if(characters[i] == c)
            return i;
        }
        return -1;
    }

    //returns the index of the start of the given string inside of this string
    int string::search(const string& substring) const{
        char* temp = strstr(characters, substring.characters);
        if(temp != NULL){
            return temp[0] - characters[0];
        }
        return -1;
    }

    //returns the number of occurances of c
    unsigned int string::count(char c) const{
        unsigned int counter = 0;
        for(int i = 0; i < length(); i++){
            if(characters[i] == c)
                counter++;
        }
        return counter;
    }

    //NON-MEMBER FUNCTIONS

    //returns concatenation of string s1 and s2
    string operator +(const string& s1, const string& s2){
        string temp;
        temp.reserve(s1.length() + s2.length() + 1);
        temp += s1;
        temp += s2;
        return temp; 
    }

    //return concatenation of string s1 and char array addend
    string operator +(const string& s1, const char addend[ ]){
        string temp;
        temp.reserve(s1.length() + strlen(addend) + 1);
        temp += s1;
        temp += addend;
        return temp;
    }

    //
    std::istream& operator >> (std::istream& ins, string& target){
        char* buffer = new char[100];
        while(ins && isspace(ins.peek()))
            ins.ignore();
        ins >> buffer;
        target = string(buffer);
        return ins;
    }

    //FRIEND FUNCTIONS

    //returns the sequence of characters in the source
    std::ostream& operator <<(std::ostream& outs, const string& source){
        outs << source.characters;
        return outs;
    }

    bool operator ==(const string& s1, const string& s2){
        return (strcmp(s1.characters, s2.characters) == 0);
    }

    bool operator !=(const string& s1, const string& s2){
        return (strcmp(s1.characters, s2.characters) != 0);
    }

    bool operator > (const string& s1, const string& s2){
        return (strcmp(s1.characters, s2.characters) > 0);
    }

    bool operator < (const string& s1, const string& s2){
        return (strcmp(s1.characters, s2.characters) < 0);
    }

    bool operator >=(const string& s1, const string& s2){
        return( (s1 > s2) || (s1 == s2));
    }

    bool operator <=(const string& s1, const string& s2){
        return ( (s1 < s2) || (s1 == s2));
    }
        
    
    

}