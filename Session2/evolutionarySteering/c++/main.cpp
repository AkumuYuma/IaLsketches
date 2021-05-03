#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream> 
#include "veichle.cpp"
#include <memory>
#include <vector>

std::unique_ptr<sf::CircleShape> ciboRandom(sf::RenderWindow &finestra) {
  // Restituisce un puntatore unico a un cibo in una posizione random dello schermo
  std::unique_ptr<sf::CircleShape> cibo{new sf::CircleShape{2}}; 
  cibo->setPosition(randomTools::randomFloat(0, finestra.getSize().x), randomTools::randomFloat(0, finestra.getSize().y));
  cibo->setFillColor(sf::Color::Green);
  return cibo;
}

int main() {
  sf::RenderWindow finestra(sf::VideoMode(900, 900), "Evolution", sf::Style::Close | sf::Style::Titlebar); 
  
  // Array di veicoli 
  std::vector<std::unique_ptr<Veichle>> veicoli; 
  for (int i = 0; i < 30; ++i) {
    // Creo un unique_ptr, che punta a un oggetto veicolo. Essendo un puntatore intelligente quando elimino il riferimento, viene liberata la memoria
    veicoli.push_back(std::unique_ptr<Veichle>{new Veichle(300, 300)}); 
  }


  // Array di cibo 
  std::vector<std::unique_ptr<sf::CircleShape>> cibi;
  
  for (int i = 0; i < 50; ++i) {
    // Inserisco cibo in giro come cerchi di raggio 2
    cibi.push_back(ciboRandom(finestra));
  } 
  
  // Array di veleno  
  std::vector<std::unique_ptr<sf::CircleShape>> veleno;
  
  for (int i = 0; i < 20; ++i) {
    // Inserisco il veleno in giro come cerchi di raggio 2
    veleno.push_back(std::unique_ptr<sf::CircleShape>{new sf::CircleShape{2}});
    veleno[i]->setPosition(randomTools::randomFloat(0, finestra.getSize().x), randomTools::randomFloat(0, finestra.getSize().y));
    veleno[i]->setFillColor(sf::Color::Red);
  } 
  
  // Main loop
  while (finestra.isOpen()) {
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
    
    // Bassa probabilità di generare cibo in posizione random sullo schermo 
    if (randomTools::randomFloat() < 0.01) {
      cibi.push_back(ciboRandom(finestra)); 
    }

    finestra.clear(); 
    
    // Loop sui veicoli 
    // Devo usare gli iteratori per eliminare un elemento della lista 
    for (auto i = veicoli.begin() ; i != veicoli.end(); ++i) {
      // l'oggetto *i rappresenta veicoli[i]
      (*i)->edges(finestra);
      (*i)->vivi(cibi, veleno);
      (*i)->update();
      (*i)->show(finestra); 
      // Se il vettore di cibi non è vuoto 

      if ((*i)->dead()) {
	// Se l'elemento i-simo è morto, lo elimino.
       	// i-- restituisce i a erase e poi decrementa. Così elimino l'elemento ma non salto niente
	// Questo è l'algoritmo per togliere un elemento da una lista eliminandolo
	veicoli.erase(i--);
      }
    }

    // Loop sui cibi
    for (auto &cibo : cibi) {
      finestra.draw(*cibo);
    }
    
    // Loop sui veleni
    for (auto &vel : veleno) {
      finestra.draw(*vel); 
    }

    finestra.display();
  }
}
