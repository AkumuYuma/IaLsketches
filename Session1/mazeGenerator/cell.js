class Cell {
  constructor(x, y) {
    // Posizione
    this.x = x;
    this.y = y;
    // Muri
    this.walls = [true, true, true, true] // Top, right, bottom, left walls
    // Visitata
    this.visited = false;
  }

  visit() {
    // Visita la cella
    this.visited = true;
  }

  show() {
    // Disegna la cella con i suoi muri. Di un colore diverso se visitata
    noFill();
    stroke(255);
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
  }

  vicini() {
    // Resituisce un array con i vicini disponibili
    let vicini = [];

    try {
      // Cerco di prendere il vicino di sopra
      // Nota che se l'indice x va fuori dal range sollevo un errore. Lo gestisco e non faccio niente
      // Se invece l'indice y va fuori dal range, semplicemente top sarà undefined. Questo secondo caso viene gestito dall'if top
      let top = griglia[this.x][this.y-1];
      if (top && !top.visited) vicini.push(top);
    } catch {}
    try {
      let right = griglia[this.x + 1][this.y];
      if (right && !right.visited) vicini.push(right);
    } catch {}
    try {
      let bottom = griglia[this.x][this.y + 1];
      if (bottom && !bottom.visited) vicini.push(bottom);
    } catch {}
    try {
      let left = griglia[this.x - 1][this.y];
      if (left && !left.visited) vicini.push(left);
    } catch {}
    finally {
      return vicini;
    }
  }

  getVicino() {
    // Restituisce, se possibile, un vicino a caso
    let vicini = this.vicini();
    if (vicini.length > 0) {
      return vicini[floor(random(0, vicini.length))];
    }
  }

}
