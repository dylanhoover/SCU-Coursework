/***************************************/
/* Dylan Hoover Santa Clara University */
/*       COEN 79 Lab 1 Program 3       */
/***************************************/

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char* argv[]){

    //check for file
    if(argc != 2){
        cout << "No file entered! Please enter a file\n";
        return 1;
    }

    //create and initialize variables
    string temp;
    string word = "";
    string filename(argv[1]);

    //creates the file pointer and opens it
    ifstream myFile;
    myFile.open(filename);

    while(!myFile.eof()){
        word = "";
        myFile >> temp;
        for(int i = 0; i< temp.length(); i++){
            if(isalpha(temp[i])){
                word += toupper(temp[i]);
            }
        }
        if(word.length() >= 10){
            cout << word << endl;
        }
    }

    return 0;
}