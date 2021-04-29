#include "dichiarazioni.h"

// Funzioni utili
int genAlg::randInt(int start, int end) {
  // Genera un numero casuale tra start ed end - 1
  int range = (end - start); 
  int randomInt = start + (rand()%range);
  return randomInt;
}

char genAlg::geneCasuale() {
  // Genera un gene casuale dalla lista di geni
  int r = randInt(0, genAlg::GENI.size());
  return genAlg::GENI[r]; 
}
