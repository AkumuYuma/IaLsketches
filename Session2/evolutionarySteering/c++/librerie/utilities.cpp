float radToDeg(float radians) {
  // ritorna l'angolo trasformato in gradi 
  return (radians * 180) / M_PI; 
}

std::unique_ptr<sf::CircleShape> creaCibo(sf::RenderWindow &finestra, bool buono, sf::Vector2f posizione = sf::Vector2f(-1, -1)) {
  // Restituisce un puntatore unico a un cibo in una posizione random dello schermo
  // :param: buono, se vero crea un cibo, altrimenti crea un veleno
  // :param: posizione, se viene passato lo usa per creare nella posizione, altrimenti crea random
  std::unique_ptr<sf::CircleShape> cibo{new sf::CircleShape{2}}; 
  
  if (posizione.x >= 0 && posizione.y >= 0) {
    cibo->setPosition(posizione.x, posizione.y);
  } else {
    cibo->setPosition(randomTools::randomFloat(0, finestra.getSize().x), randomTools::randomFloat(0, finestra.getSize().y));
  } 

  if (buono) {
    cibo->setFillColor(sf::Color::Green);
  } else {
    cibo->setFillColor(sf::Color::Red);
  }

  return cibo;
}

sf::Text creaTesto(sf::Font font, std::string testo, unsigned size,  sf::Vector2f Posizione = sf::Vector2f{0, 0}) {
  // :param: font -> font da usare 
  // :param: testo -> stringa da scrivere 
  // :param: size -> dimensione dei caratteri 
  // :param: Posizione -> Posizione nella finestra in cui disegnare
  // :return: -> oggetto testo da disegnare sulla finestra 
  sf::Text nuovoTesto; 
  nuovoTesto.setFont(font); 
  nuovoTesto.setPosition(Posizione); 
  nuovoTesto.setString(testo);
  nuovoTesto.setCharacterSize(size); 
  nuovoTesto.setFillColor(sf::Color::White);
  return nuovoTesto; 
}

