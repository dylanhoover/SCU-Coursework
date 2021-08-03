/***************************************/
/* Dylan Hoover Santa Clara University */
/*       COEN 79 Lab 1 Program 1       */
/***************************************/

#include <iostream> 
using namespace std;

int main(int argc, const char * argv[]) {

    // initialize variables
    string sentence = "";
    int alphacount = 0;
    int nonalphacount = 0;

    // promt the user for a string
    cout << "Enter a string\n";
    //get the string and put it in sentence
    getline(cin, sentence);

    for(int i = 0; i < sentence.length(); i++){
        if(sentence[i] != ' '){ //checks for spaces and ignores them
            if(isalpha(sentence[i])){ //determin if alphanumeric and alphacount++
                alphacount++;
            }
            else{
                nonalphacount++; //if not alphanumeric nonalphacount++
            }
        }
    }

    cout << "The sentence: " << sentence << " has " << alphacount << " alphanumeric characters and " << nonalphacount << " non-alphanumeric characters\n";

    return 0;
}