class Cell {
  constructor(x, y) {
    // Posizione
    this.x = x;
    this.y = y;
    // Muri
    this.walls = [true, true, true, true] // Top, right, bottom, left walls
    // Visitata
    this.visited = false;

    // Indica se la cella è la cella corrente
    this.currentCell = false;
  }

  setCurrent(value) {
    this.currentCell = value;
  }

  visit() {
    // Visita la cella
    this.visited = true;
  }

  show() {
    // Disegna la cella con i suoi muri. Di un colore diverso se visitata
    noFill();
    stroke(255);
    strokeWeight(2);
    let x = this.x * scale;
    let y = this.y * scale;
    if (this.walls[0]) line(x, y, x + scale, y);
    if (this.walls[1]) line(x + scale, y, x + scale, y + scale);
    if (this.walls[2]) line(x + scale, y + scale, x, y + scale);
    if (this.walls[3]) line(x, y + scale, x, y);
    // Se la cella è visitata la contrassegno di un colore diverso
    if (this.visited) {
      noStroke();
      fill(136, 193, 215);
      rect(x, y, scale, scale);
    }
    if (this.currentCell) {
      noStroke();
      fill(255, 123, 44);
      rect(x, y, scale, scale);
    }
  }

  vicini() {
    // Resituisce un dizionario con i vicini disponibili
    let vicini = {};
    try {
      // Cerco di prendere il vicino di sopra
      // Nota che se l'indice x va fuori dal range sollevo un errore. Lo gestisco e non faccio niente
      // Se invece l'indice y va fuori dal range, semplicemente top sarà undefined. Questo secondo caso viene gestito dall'if top
      let top = griglia[this.x][this.y - 1];
      if (top && !top.visited) {
        vicini["top"] = top;
      }
    } catch {}
    try {
      let right = griglia[this.x + 1][this.y];
      if (right && !right.visited) {
        vicini["right"] = right;
      }
    } catch {}
    try {
      let bottom = griglia[this.x][this.y + 1];
      if (bottom && !bottom.visited) {
        vicini["bottom"] = bottom;
      }
    } catch {}
    try {
      let left = griglia[this.x - 1][this.y];
      if (left && !left.visited) {
        vicini["left"] = left;
      }
    } catch {}
    finally {
      return vicini;
    }
  }

  getVicino() {
    // Restituisce, se possibile, un vicino a caso.
    // Se restituisce un vicino, elimina i muri tra questa cella e il vicino ottenuto
    let vicini = this.vicini();
    if (Object.values(vicini).length > 0) {
      let vicinoOttenuto = Object.values(vicini)[floor(random(0, Object.values(vicini).length))];
      // Devo rimuovere i muri che separano this da vicinoOttenuto
      if (vicini["top"] == vicinoOttenuto) {
        // Se il vicino ottenuto è quello di sopra, tolgo il muro di sopra dalla cella corrente
        // E il muro di sotto dalla cella vicina
        this.walls[0] = false;
        vicini["top"].walls[2] = false;

      } else if (vicini["right"] == vicinoOttenuto) {
        this.walls[1] = false;
        vicini["right"].walls[3] = false;

      } else if (vicini["bottom"] == vicinoOttenuto) {
        this.walls[2] = false;
        vicini["bottom"].walls[0] = false;

      } else if (vicini["left"] == vicinoOttenuto) {
        this.walls[3] = false;
        vicini["left"].walls[1] = false;
      }
      return vicinoOttenuto;
    }
  }

}
