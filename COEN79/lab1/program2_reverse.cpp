/***************************************/
/* Dylan Hoover Santa Clara University */
/*       COEN 79 Lab 1 Program 2       */
/***************************************/

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

//reverse function using reverse algorithm from <algorithm>
string reverse(string const &str){
    string rev(str.rbegin(), str.rend());
    return rev;
}

int main(int argc, const char * argv[]){

    //initialize variablesq
    string first = "";
    string second = "";
    int gInput = 0;
    int count = 0;
    //ask for string
    cout << "Input string of 10 numbers with no spaces.\n";
    //get the only the first string
    do{
        getline(cin, first);
        if(first.length() != 10){
            cout << "Type 10 numbers" << endl;
        }
        else if(first.length() == 10){
            for(int i = 0; i< 10; i++){
                if(isdigit(first[i]) == true && first[i] != ' '){
                    count ++;
                     if(count == 10){
                        gInput = 1;
                     }
                }
                else{
                    cout << "Number only and no spaces" << endl;
                }
            }
        }
    }while(gInput == 0);
    //set second the reverse of first
    second = reverse(first);

    //first line
    cout << first;
    cout << setw(15) << second << endl;

    //second line
    cout << setw(11) << first;
    cout << setw(15) << second << endl;

    //third line
    cout << setw(12) << first;
    cout << setw(15) << second << endl;

    //fourth line
    cout << setw(13) << first;
    cout << setw(15) << second << endl;

    //fifth line
    cout << setw(14) << first;
    cout << setw(15) << second << endl;


    return 0;
}