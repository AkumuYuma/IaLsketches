#include "dichiarazioni.h"

// Definisco i metodi della classe individuo

genAlg::Individuo::Individuo(int len, std::string target) {
  // Inizializzo con una serie casuale di geni di lunghezza len
  for (int i = 0; i < len; i++) {
    geni += geneCasuale();
  }
  // Calcolo il fitness alla creazione
  calcolaFitness(target);
} 

void genAlg::Individuo::calcolaFitness(std::string target) {
  // Calcola il fitness di un individuo e lo scrive nell'attributo fitness
  fitness = 0; 
  for (int i = 0; i < target.size(); i++) {
    if (geni[i] != target[i]) fitness++; 
  }
} 

genAlg::Individuo genAlg::Individuo::generaFiglio(genAlg::Individuo partner, float mutationRate) {
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
