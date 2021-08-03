#include <iostream>
#include "random.h"

using namespace std;

namespace coen79_lab2{

    //constructor puts all args in new object, 4 arguments are needed
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus){
        this->seed = seed;
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }

    //assign a new seed from the arguments
    void rand_gen::set_seed(int newSeed){
        this->seed = newSeed;
    }

    //calculate the next seed using the equation
    int rand_gen::next(){
        int temp;
        temp = (this->multiplier * this->seed + this->increment) % this->modulus;
        this->seed = temp;
        return temp;
    }
    
    //print the seed and the args
    void rand_gen::print_info() const{
        cout << "Seed: " << this->seed;
        cout << " Multiplier:" << this->multiplier;
        cout << " Increment:" << this->increment;
        cout << " Modulus:" << this->modulus << endl << endl;
    }
}
