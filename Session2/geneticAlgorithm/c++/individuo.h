#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <string>
#include <iostream>
#include <cstdlib> 

using namespace std;

const std::string GENI{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890,.'-;:_!"}; 

int randInt(int start, int end) {
  // Genera un numero casuale tra start ed end - 1
  int range = (end - start); 
  int randomInt = start + (rand()%range);
  return randomInt;
}

char geneCasuale() {
  // Genera un gene casuale dalla lista di geni
  int r = randInt(0, GENI.size());
  return GENI[r]; 
}

class Individuo {
  public: 
    // Attributi
    string geni{}; 
    string target{};
    // Se fitness è 0, ho individuato la frase
    int fitness{0}; 
    // Metodi 
    void calcolaFitness(string target); 
    Individuo generaFiglio(Individuo partner, float mutationRate); 
    
    // Costruttore 
    Individuo(int len, string target) {
      // Inizializzo con una serie casuale di geni di lunghezza len
      for (int i = 0; i < len; i++) {
	geni += geneCasuale();
      }
      // Calcolo il fitness alla creazione
      calcolaFitness(target);
    } 
    
  bool operator<( const Individuo &persona2) {
    return (fitness < persona2.fitness); 
  }
  
  bool operator>( const Individuo &persona2) {
    return (fitness > persona2.fitness); 
  }
	
  bool operator==(const Individuo &persona2) {
    return (fitness == persona2.fitness); 
  } 

};

void Individuo::calcolaFitness(string target) {
  // Calcola il fitness di un individuo e lo scrive nell'attributo fitness
  fitness = 0; 
  for (int i = 0; i < target.size(); i++) {
    if (geni[i] != target[i]) fitness++; 
  }
} 

Individuo Individuo::generaFiglio(Individuo partner, float mutationRate) {
  // Genero un individuo figlio tra l'individuo attuale e un partner.
  Individuo child(geni.size(), partner.target); 
  for (int i = 0; i < geni.size(); i++) {
    // Calcolo un valore di probabilià che mi dirà se il gene verrà assegnato dal primo partner, dal secondo o casualmente
    float n = static_cast<float>(randInt(0, 100))/100;
     
    float limite = 1 - mutationRate; 
    float midPoint = limite/2; 
    
    if (n < midPoint) {
      // Nel primo caso prendo dal primo genitore
      child.geni[i] = geni[i]; 
    } else if (n >= midPoint && n < limite) {
      // Nel secondo caso prendo dal secondo genitore
      child.geni[i] = partner.geni[i]; 
    } else {
      // Nel terzo caso prendo il gene casuale perchè è mutato 
      child.geni[i] = geneCasuale();
    }
  } 
  return child;
}


#endif
