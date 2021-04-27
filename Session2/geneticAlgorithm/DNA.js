
class DNA {
  constructor(l) {
    // Inizializzo a 0 il fitness score dell'elemento
    this.score = 0;
    this.geni = [];
    for (let i = 0; i < l; i++) {
      this.geni[i] = randomChar();
    }
  }

  frase() {
    return this.geni.join("");
  }

  crossOver(other) {
    // Mischio il materiale genetico di this con quello di other, restituisco un nuovo oggetto DNA
    let child = new DNA(this.geni.length);
    // La prima metà dei caratteri viene da this
    let medio = floor(random(this.geni.length));
    for (let i = 0; i < this.geni.length; i++) {
      if (i < medio) child.geni[i] = this.geni[i];
      else child.geni[i] = other.geni[i];
    }
    return child;
  }

  valutaFit(target) {
    // Confronto il materiale genetico con il target
    for (let i = 0; i < this.geni.length; i++) {
      if (this.geni[i] == target[i]) {
        // Per ogni carattere uguale ad uno dei caratteri target aumento lo score dell'elemento
        this.score++;
      }
    }
  }

  muta(mutationRate) {
    for (let i = 0; i < this.geni.length; i++) {
      if (random(1) < mutationRate) {
        this.geni[i] = randomChar();
      }
    }
  }

}


function randomChar() {
  // Da 63 a 122 sono i caratteri che interessano
  let c = String.fromCharCode(floor(random(63, 128)));
  // 63 è punto interrogativo e lo mando allo spazio (32)
  if (c === 63) c = 32;
  // 64 è @ e lo mando al punto (46)
  if (c === 64) c = 46;
  return c;
}
