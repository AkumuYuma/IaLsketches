#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream> 
#include <memory>
#include <string>
#include <vector>
#include <chrono>

#include "veichle.cpp"

int main() {
  // ---------------------------------- Operazioni preparatorie al main loop -------------------------------------

  sf::RenderWindow finestra(sf::VideoMode(900, 900), "Evolution", sf::Style::Close | sf::Style::Titlebar); 
  
  // Creo array di veicoli 
  std::vector<std::unique_ptr<Veichle>> veicoli; 
  for (int i = 0; i < 100; ++i) {
    veicoli.push_back(std::unique_ptr<Veichle>{new Veichle(300, 300)}); 
  }


  // Creo array di cibo e veleno 
  std::vector<std::unique_ptr<sf::CircleShape>> cibi;
  for (int i = 0; i < 300; ++i) {
    cibi.push_back(creaCibo(finestra, true));
  } 
  std::vector<std::unique_ptr<sf::CircleShape>> veleno;
  for (int i = 0; i < 300; ++i) {
    veleno.push_back(creaCibo(finestra, false));
  } 
  
  // Inizio a misurare il tempo 
  std::chrono::steady_clock::time_point timeStart = std::chrono::steady_clock::now();
  // Variabile bool per fine simulazione
  bool finito{false}; 
  std::string tempoFinale = ""; 
  // Conto i loop
  int loopCounter{0}; 



  // ------------------------------------------------- Main loop ------------------------------------------------
  while (finestra.isOpen()) {
    
    // Misuro il tempo a ogni loop
    std::chrono::steady_clock::time_point timeEnd = std::chrono::steady_clock::now();
    std::string tempo = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(timeEnd - timeStart).count());
   

    finestra.setFramerateLimit(60);
    // Gestione eventi
    sf::Event ev; 
    while (finestra.pollEvent(ev)) {
      switch (ev.type) {
	case sf::Event::Closed:
	  finestra.close();
	  break; 

	case sf::Event::KeyPressed:
	  // Se premo d sulla tastiera attivo o disattivo la debug mode dei veicoli 
	  if (ev.key.code == sf::Keyboard::D) {
            Veichle::debug = !Veichle::debug;
	  }
	  break; 
      }
    }
    
    // Bassa probabilit?? di generare cibo o veleno in posizione random sullo schermo 
    if (randomTools::randomFloat() < 0.08) {
      cibi.push_back(creaCibo(finestra, true)); 
    }  
    if (randomTools::randomFloat() < 0.01) {
      veleno.push_back(creaCibo(finestra, false)); 
    }
    

    // --------------------------------------------- Operazioni di disegno -------------------------------------
    
    finestra.clear(); 
    
    // --------------------------------------------- Loop sui veicoli -------------------------------------------
    
    for (auto i = veicoli.begin() ; i != veicoli.end(); ++i) {
      // l'oggetto *i rappresenta veicoli[i]
      (*i)->edges(finestra);
      (*i)->vivi(cibi, veleno);
      (*i)->update();
      (*i)->show(finestra); 
       
      // Probabili?? di clonare
      if (randomTools::randomFloat() < 0.003) {
	i = veicoli.insert(i, (*i)->clona()); 
	i++;
      }

      if ((*i)->dead()) {
	// Se l'elemento i-simo ?? morto, lo elimino.
	// Inoltre creo un cibo nella posizione 
       	// i-- restituisce i a erase e poi decrementa. Cos?? elimino l'elemento ma non salto niente
	cibi.push_back(creaCibo(finestra, true, (*i)->getposition())); 
	veicoli.erase(i--); 
      }
    }
   
    // ---------------------------------------------- Disegno info, veleni e cibi --------------------------------

    // Definisco il font per testo a schermo 
    sf::Font font; 
    if (!font.loadFromFile("font/arial.ttf")) {
      throw("Errore nel caricare il font"); 
    }
    
    // Scrivo le info sullo schermo
    finestra.draw(creaTesto(font, "Alive: " + std::to_string(veicoli.size()), 24)); 
    finestra.draw(creaTesto(font, "Elapsed time: " + tempo + "s", 15, sf::Vector2f{0, 30})); 
    finestra.draw(creaTesto(font, "Loops elapsed: " + std::to_string(loopCounter), 15, sf::Vector2f{0, 50}));
    finestra.draw(creaTesto(font,"Food: " + std::to_string(cibi.size()), 15, sf::Vector2f{0, 70})); 
    finestra.draw(creaTesto(font,"Poison: " + std::to_string(veleno.size()), 15, sf::Vector2f{0, 90})); 
    finestra.draw(creaTesto(font, "D to show debug info", 15, sf::Vector2f{static_cast<float>(finestra.getSize().x - 200), static_cast<float>(finestra.getSize().y - 30)}));
   
     
    // Se la simulazione ?? finita scrivo a schermo il tempo di sopravvivenza della specie 
    if (veicoli.size() == 0 && !finito) {
      tempoFinale = tempo;
      finito = true; 
    }
    if (tempoFinale != "") {
      finestra.draw(creaTesto(font, "They lived for: " + tempoFinale + "s", 15, sf::Vector2f{0, 110})); 
    }

    // Disegno i cibi
    for (auto &cibo : cibi) {
      finestra.draw(*cibo);
    }
    
    // Disegno i veleni 
    for (auto &vel : veleno) {
      finestra.draw(*vel); 
    }

   
    finestra.display();
   
    ++loopCounter; 
  }
}
