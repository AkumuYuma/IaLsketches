class Popolazione {
  constructor(popMax, target, mutationRate) {
    this.popMax = popMax;
    this.target = target;
    this.mutationRate = mutationRate;
    // Array di oggetti DNA
    this.population = [];
    // Tengo il conto delle generazioni
    this.generazione = 0;
    this.best = "";
    this.perfectScore = 1;
    this.finito = false;

    for (let i = 0; i < popMax; i++) {
      this.population[i] = new DNA(this.target.length);
    }

    this.matingPool = [];
    this.valutaFit();

  }
  // Private

  valutaFit() {
    // Valuto il fit di ogni elemento della popolazione
    for (let i = 0; i < this.population.length; i++) {
      this.population[i].valutaFit(this.target);
    }
  }

  makePool() {
    // Costruisco la pool di estrazione a partire dalla probabilità di ciascun elemento della popolazione
    this.matingPool = [];
    // Trovo l'elemento migliore
    let massimoFit = 0;
    for (let i = 0; i < this.population.length; i++) {
      if (this.population[i].score > massimoFit) {
        massimoFit = this.population[i].score;
      }
    }


    // Per ogni elemento
    for (let i = 0; i < this.population.length; i++ ) {
      // Mappo lo score di ognuno
      let prob = map(this.population[i].score, 0, massimoFit, 0, 1);
      let n = floor(prob * 100);
      // Lo inserisco tante volte quante sono le probabilità
      for (let j = 0; j < n; j++ ) {
        this.matingPool.push(this.population[i]);
      }
    }
  }

  nuovaGenerazione() {
    // Estraggo (due) elementi dalla popolazione in base alla loro probabilità.
    // Estraggo due indici a caso dalla Pool
    if (this.matingPool.length > 0) {
      for (let i = 0; i < this.population.length; i++) {
        let genitore1 = this.matingPool[floor(random(this.matingPool.length))];
        let genitore2 = this.matingPool[floor(random(this.matingPool.length))];
        let figlio = genitore1.crossOver(genitore2);
        figlio.muta(this.mutationRate);
        this.population[i] = figlio;
      }
    } else {
      this.inizializza();
    }
    this.generazione++;
  }

  ottieniMigliore() {
    return this.best;
  }

  valutaGenerazione() {
    let record = 0.0;
    let index = 0;
    for (let i = 0; i < this.population.length; i++) {
      if (this.population[i].score > record) {
        index = i;
        record = this.population[i].score;
      }
    }

    this.best = this.population[index].frase();
    if (this.best == this.target) {
      this.finito = true;
    }
  }


  // Public

  stampa() {
    for (let element of this.population) {
      console.log(element.stringa());
    }
  }
}
