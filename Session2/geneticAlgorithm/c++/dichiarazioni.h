#ifndef DICHIARAZIONI_H 
#define DICHIARAZIONI_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

namespace genAlg {
  
  // Dichiaro le variabili che mi servono 
  const std::string GENI{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890,.'-;:_!"}; 
  
  // Le funzioni 
  int randInt(int start, int end);
  char geneCasuale(); 
  
  // Le classi
  class Individuo {
    public: 
      // Attributi
      std::string geni{}; 
      std::string target{};
      // Se fitness è 0, ho individuato la frase
      int fitness{0}; 
      // Costruttore
      Individuo(int len, std::string target); 
      // Metodi
      void calcolaFitness(std::string target); 
      Individuo generaFiglio(Individuo partner, float mutationRate); 
    
    // Operatori sovrascritti 
    bool operator<(const Individuo &persona2) {
      return (fitness < persona2.fitness); 
    }
    
    bool operator>(const Individuo &persona2) {
      return (fitness > persona2.fitness); 
    }
	  
    bool operator==(const Individuo &persona2) {
      return (fitness == persona2.fitness); 
    } 
  };

  class Popolazione {
    public: 
      // Attributi
      std::vector<Individuo> individui{}; 
      int maxPop{0}; 
      std::string target{};
      float mutationRate{0.}; 
      std::string migliore{}; 
      int generazione{}; 
      bool trovato = false; 
      // Costruttore 
      Popolazione(std::string, int, float);
      // Metodo 
      void nuovaGenerazione(); 
  }; 
}

#endif
