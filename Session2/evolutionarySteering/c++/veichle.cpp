#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <memory>
#include "/home/emanuele/informatica/c++/librerie/randomTools.cpp"
// La libreria dei vettori include la libreria matematica e le costanti matematiche
#include "/home/emanuele/informatica/c++/librerie/sfml/vectorTools.cpp"
 
using namespace vectorTools;

float radToDeg(float radians) {
  // ritorna l'angolo trasformato in gradi 
  return (radians * 180) / M_PI; 
}


// Classe veichle 
class Veichle {
  private:
    // Angolo rispetto a x a cui punta il veicolo 
    float angle{0.};
    // Figura che rappresenta il veicolo
    sf::ConvexShape triangolo; 
    // velocità
    sf::Vector2f vel{randomTools::randomFloat(-5, 5), randomTools::randomFloat(-5, 5)}; 
    float velocitalimite{5};
    // Accelerazione
    sf::Vector2f acc{0, 0}; 
    // Dimensione
    float raggio{7.}; 
    // DNA 
    // dna[1] rappresenta l'affinità al cibo 
    // dna[2] rappresenta l'affinità al veleno 
    // dna[3] rappresenta la percezione al cibo
    // dna[4] rappresenta la percezione al veleno 
    std::vector<float> dna{0, 0, 0, 0};
    // Il veicolo può reagire solo ad oggetti all'interno di un cerchio di raggio "visuale" 
    float visuale{100}; 
    // Vita
    float health{1};

  public: 
    static bool debug;
    Veichle(float x, float y); 
    void show(sf::RenderWindow &finestra);
    void update(); 
    void applyForce(sf::Vector2f force);
    sf::Vector2f seek(sf::Vector2f oggetto);
    bool dead(); 
    sf::Vector2f cercaVicino(std::vector<std::unique_ptr<sf::CircleShape>> & lista, float valoreNutrizionale, float percezione); 
    void vivi(std::vector<std::unique_ptr<sf::CircleShape>> & cibo, std::vector<std::unique_ptr<sf::CircleShape>> & veleno);
    void edges(sf::RenderWindow &finestra);
    // Metodi di debug
    sf::Vector2f getorigin(); 
    sf::Vector2f getposition(); 
    sf::Vector2f getvelocity();
    float getrotation(); 

}; 

// Variabile di debug
bool Veichle::debug{false}; 

Veichle::Veichle(float x, float y) {
  // Costruttore. 
  // :Param: x,y -> Posizione iniziale
  
  // Inizializzo il dna con pesi a caso   
  dna[0] = randomTools::randomFloat(-5, 5);
  dna[1] = randomTools::randomFloat(-5, 5); 
  dna[2] = randomTools::randomFloat(1, 100); 
  dna[3] = randomTools::randomFloat(1, 100); 
  // La figura deve essere un triangolo quindi setto 3 punti 
  triangolo.setPointCount(3); 
  // Setto l'origine al centro del triangolo 
  triangolo.setOrigin(raggio, raggio/2); 
  // Setto la posizione ai parametri dati
  triangolo.setPosition(x, y); 
  triangolo.setOutlineThickness(1); 
  // Setto i vertici (in senso orario) 
  triangolo.setPoint(0, sf::Vector2f(raggio, 0)); 
  triangolo.setPoint(1, sf::Vector2f(-raggio, raggio/2)); 
  triangolo.setPoint(2, sf::Vector2f(-raggio, -raggio/2));
}

void Veichle::show(sf::RenderWindow &finestra) {
  finestra.draw(triangolo); 
  if (debug) {
    // DEBUG
    // Disegno intorno al triangolo un cerchio di raggio pari alla visuale 
    // Disegno una linea di lunghezza proporzionale all'affinità al cibo o al veleno
    sf::RectangleShape rectCibo{sf::Vector2f(dna[0] * 10, 1)}; 
    rectCibo.setPosition(triangolo.getPosition());
    rectCibo.setFillColor(sf::Color::Green); 
    finestra.draw(rectCibo); 
    
    sf::RectangleShape rectVeleno{sf::Vector2f(dna[1] * 10, 1)}; 
    rectVeleno.setPosition(triangolo.getPosition());
    rectVeleno.setFillColor(sf::Color::Red); 
    finestra.draw(rectVeleno); 

    sf::CircleShape cerchioCibo{}; 
    cerchioCibo.setRadius(dna[2]); 
    cerchioCibo.setOrigin(dna[2], dna[2]); 
    cerchioCibo.setPosition(triangolo.getPosition()); 
    cerchioCibo.setFillColor(sf::Color(0, 0, 0, 0)); 
    cerchioCibo.setOutlineThickness(2); 
    cerchioCibo.setOutlineColor(sf::Color::Green);
    finestra.draw(cerchioCibo); 

    sf::CircleShape cerchioVeleno{}; 
    cerchioVeleno.setRadius(dna[3]); 
    cerchioVeleno.setOrigin(dna[3], dna[3]); 
    cerchioVeleno.setPosition(triangolo.getPosition()); 
    cerchioVeleno.setFillColor(sf::Color(0, 0, 0, 0)); 
    cerchioVeleno.setOutlineThickness(2); 
    cerchioVeleno.setOutlineColor(sf::Color::Red);
    finestra.draw(cerchioVeleno); 
  }
} 

void Veichle::update() {
  // Aggiornamento da fare ad ogni ciclo
  

  // Riduco la vita a ogni ciclo
  health -= 0.001; 
  // I veicoli scompaiono al calare della vita
  triangolo.setFillColor(sf::Color(255, 255, 255, 255 * health));
  triangolo.setOutlineColor(sf::Color(255, 255, 255, 255 * health));
  // Setto l'origine delle rotazioni  
  triangolo.setOrigin(0, 0); 
  // Ruoto nella direzionde di movimento
  float angle = heading(vel); 
  triangolo.setRotation(radToDeg(angle));
  // Applico l'accelerazione
  vel += acc;
  // Limito la velocità
  limitVector(vel, velocitalimite); 
  // Muovo l'oggetto 
  triangolo.move(vel); 
  // Resetto l'accelerazione a 0
  multVector(acc, 0);
}

void Veichle::applyForce(sf::Vector2f force) {
  // Aggiunge la forza passata in input all'accelerazione
  // :param: force -> forza da applicare
  acc += force;  
}

sf::Vector2f Veichle::seek(sf::Vector2f oggetto) {
  // Restituisce una forza che generata con un algoritmo di steering 
  // :param: oggetto -> da cercare 
  // :return: vettore che rappresenta la forza di attrazione verso l'oggetto 
  
  // La velocità desiderata è un vettore che punta verso l'oggetto 
  sf::Vector2f velIdeale = oggetto - triangolo.getPosition(); 
  // Limito anche la velocià ideale a quella limite
  limitVector(velIdeale, velocitalimite);
  // Genero una forza di attrazione come velocità attuale - velocità desiderata
  sf::Vector2f attrazione = velIdeale - vel;
  // Limito il modulo della forza 
  float limiteForza = 0.1; 
  limitVector(attrazione, limiteForza); 
  return attrazione; 
}

bool Veichle::dead() {
  // Verifica che la vita del veicolo sia finita
  // :return: booleano, vero se il veicolo è morto 
  return (health <= 0); 
}

sf::Vector2f Veichle::cercaVicino(std::vector<std::unique_ptr<sf::CircleShape>> & lista, float valoreNutrizionale, float percezione) {
  // Cerca l'oggetto più vicino nella lista passata e lo mangia. 
  // :param: lista -> cibi o veleno
  // :param: valoreNutrizionale -> indica l'aumento o diminuzione della vita
  // :param: percezione -> indica la distanza massima a cui il veicolo percepisce l'elemento della lista
  // :return: vettore che indica la forza di attrazione verso l'elemento più vicino nella lista
  // :return: vettore nullo se ha mangiato
  // :return: vettore nullo se la lista è vuota
  
  // Controllo che la lista non sia vuota 
  if (lista.size() > 0) {
    // Cerco il più vicino nella visuale del veicolo 
    float distanzaMinima = 1e4; 
    auto closest = lista.begin(); 
    for (auto it = lista.begin(); it != lista.end(); ++it) {
      float distanza = dist(triangolo.getPosition(), (*it)->getPosition());
      if (distanza < distanzaMinima) {
	// Se l'oggetto più vicino non è nella visuale non aggiorno la distanza minima
	closest = it; 
	distanzaMinima = distanza;
      }
    }

    // Se sono dentro la visuale, mangio il cibo oppure creo l'attrazione 
    if (distanzaMinima < percezione) {
      sf::Vector2f posizioneVicino = (*closest)->getPosition();
      // Mangio l'oggetto se sono abbastanza vicino e lo rimuovo dalla lista
      if (dist(triangolo.getPosition(), posizioneVicino) < 5) {
	lista.erase(closest); 
	// Aggiungo il valore nutrizionale alla vita
	health += valoreNutrizionale; 
      } else {
	// Restituisco la forza di attrazione
	return seek(posizioneVicino); 
      }
    }
  }
  
  // Se la lista in input è vuota, oppure il più vicino è fuori dalla visuale restituisco il vettore nullo 
  return sf::Vector2f(0,0);
}

void Veichle::vivi(std::vector<std::unique_ptr<sf::CircleShape>> & cibo, std::vector<std::unique_ptr<sf::CircleShape>> & veleno) {
  // Applica la forza di attrazione generata dal metodo mangia, pesandola in base al dna del veicolo. 
  // :param: cibo -> lista di cibo
  // :param: veleno -> lista di veleno 
  
  sf::Vector2f forzaBuona = cercaVicino(cibo, 0.2, dna[2]);  
  sf::Vector2f forzaMale = cercaVicino(veleno, -0.5, dna[3]); 
  multVector(forzaBuona, dna[0]); 
  multVector(forzaMale, dna[1]); 
  applyForce(forzaBuona); 
  applyForce(forzaMale); 
}

void Veichle::edges(sf::RenderWindow &finestra) {
  // Se il veicolo va sui bordi dello schermo, setto la velocità desiderata verso il centro 
  // :param: finestra -> finestra su cui disegnare il veicolo
  sf::Vector2f pos = triangolo.getPosition(); 
  sf::Vector2f sizeFinestra = static_cast<sf::Vector2f>(finestra.getSize()); 
  float margine = 20.;  
  if (pos.x < margine || pos.x > sizeFinestra.x - margine || pos.y < margine || pos.y > sizeFinestra.y - margine) {
    applyForce(seek(sf::Vector2f(sizeFinestra.x/2, sizeFinestra.y/2))); 
  }

}

// Metodi di debug
sf::Vector2f Veichle::getorigin() {
  return triangolo.getOrigin();
} sf::Vector2f Veichle::getposition() {
  return triangolo.getPosition();
}

sf::Vector2f Veichle::getvelocity() {
  return vel;
}

float Veichle::getrotation() {
  return triangolo.getRotation();
}

