#include "dichiarazioni.h"
#include "individuo.cpp" 
#include "popolazione.cpp" 
#include "utilities.cpp" 

using namespace std; 

const string target{"To be or not to be this is the question"};

int main() {
  srand(static_cast<unsigned>(time(0)));
   
  genAlg::Popolazione pop(target, 1000, 0.01); 
  
  while (!pop.trovato) {
    pop.nuovaGenerazione(); 
    // Stampo il migliore 
    cout << "Migliore: " << pop.migliore << " Fitness: " << pop.individui[0].fitness << endl;
    cout << "Generazione n: " << pop.generazione << endl; 
  }
}

