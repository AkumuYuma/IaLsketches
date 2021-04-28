// Classe popolazione
#ifndef POPOLAZIONE_H
#define POPOLAZIONE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "individuo.h" 

using namespace std;
class Popolazione {
  public: 
    vector<Individuo> individui{}; 
    int maxPop{0}; 
    string target{};
    float mutationRate{0.}; 
    string migliore{}; 
    int generazione{}; 
    bool trovato = false; 
    // Costruttore 
    Popolazione(string target, int maxPop, float mutationRate) : target(target), maxPop(maxPop), mutationRate(mutationRate) {
      // Inizializzo un array di individui 
      for (int i = 0; i < maxPop; i++) {
	individui.push_back(Individuo(target.size(), target)); 
      }

      sort(individui.begin(), individui.end()); 
      migliore = individui[0].geni;
    }
    
    void nuovaGenerazione() {
      vector<Individuo> nuovaGen; 
      // Prendo il miglior 10% della generazione attuale e lo mando nella successiva
      // Per farlo ordino il vettore di popolazione 
      sort(individui.begin(), individui.end());
      // Salvo l'info del migliore
      migliore = individui[0].geni;
      if (migliore == target) trovato = true;
      // Ora il primo 10% dell'array saranno i migliori
      int indiceMigliori = (10 * maxPop)/100;
      for (int i = 0; i < indiceMigliori; i++) {
	nuovaGen.push_back(individui[i]); 
      }

      // Il resto della generazione viene riempita dall'accoppiamento dei migliori 50% 
      int s = (90 * maxPop)/100;
      for (int i = 0; i < s; i++) {
	// Scelgo un indice a caso tra la prima metà della popolazione ordinata
	int indice1 = randInt(0, static_cast<int>(individui.size()/2)); 
	// E questo sarà il genitore 1
   	Individuo genitore1 = individui[indice1];
	int indice2 = randInt(0, static_cast<int>(individui.size()/2));
        Individuo genitore2 = individui[indice2]; 
	// Accoppio i due
	Individuo figlio = genitore1.generaFiglio(genitore2, mutationRate); 
	figlio.calcolaFitness(target); 
	// Inserisco nella nuovaGen il figlio
	nuovaGen.push_back(figlio);
      }
      // Ora la popolazione è aggiornata alla nuova generazione
      individui = nuovaGen; 
      // Aumento il conteggio della generazione
      generazione++; 
    }
}; 



#endif 
