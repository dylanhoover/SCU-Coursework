/***************************************/
/* Dylan Hoover Santa Clara University */
/*       COEN 79 Lab 1 Program 4       */
/***************************************/

#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;


int main(int argc, const char* argv[]){

    srand(time(NULL));
    //set up variables
    string userInput = "";
    int numGuess = 0;
    int guesses[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int i = 0;

    cout << "Choose a number between 1 and 20, press enter to start\n";
    cin.ignore(); //waits till enter is pressed

    random_shuffle(&guesses[0], &guesses[20]); //randomly shuffles the array of 1 - 20 to emulate random guesses from 1 - 20
    do{
        
        cout << "Was your number: " << guesses[i] <<  " Y or N\n";
        getline(cin, userInput); // get user input
        if(userInput == "Y" || userInput == "y" || userInput == "yes"){ //this will exit the do while loop
        numGuess++;
        cout << "I found the number in " << numGuess << " steps\n";
            
        }
        else if(userInput == "N" || userInput == "n" || userInput == "no"){ //this will go to the next number
            cout << "I'll try again\n";
            i++; //goes to next number in shuffled array
            numGuess++; //increase number of guesses
        }
        else{ 
            cout << "Only enter 'Y' or 'N'\n";
        }
        
    }while(userInput != "Y" && userInput != "y" && userInput != "yes");
    return 0;
}