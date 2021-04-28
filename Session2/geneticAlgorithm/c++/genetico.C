#include <string> 
#include <iostream>
#include <cstdlib>
#include "popolazione.h"

using namespace std; 


const string target{"To be or not to be this is the question"};




int main() {
  srand(static_cast<unsigned>(time(0)));
   
  Popolazione pop(target, 1000, 0.01); 
  
  while (!pop.trovato) {
    pop.nuovaGenerazione(); 
    // Stampo il migliore 
    cout << "Migliore: " << pop.migliore << " Fitness: " << pop.individui[0].fitness << endl;
    cout << "Generazione n: " << pop.generazione << endl; 
  }
}

