class Node {
  // Costruisco il nodo con due figli e un valore
  constructor(val, x = null, y = null) {
    this.val = val;
    this.left = null;
    this.right = null;

    // Valori per la visualizzazione
    this.x = x;
    this.y = y;
    this.r = 20;
    this.depth = 0;
  }

  // Funzione per aggiungere un nodo a destra o a sinistra a seconda del valore
  // Restituisce il valore di profondità alla quale il nodo viene inserito
  addNode(valueNode) {
     if (valueNode.val < this.val) {
       // Scendo al livello successivo e incremento la profondità del nodo da inserire
       valueNode.depth++;
       // Se il valore da aggiungere è più piccolo del valore del nodo corrente, lo aggiungo a sinistra
       if (this.left == null) {
         // Se il figlio sinistro è vuoto aggiungo direttamente il nodo
         this.left = valueNode;
         // Ritorno la profondità
         return this.left.depth;
       } else {
         // Altrimenti rifaccio il procedimento con il figlio di sinistra
         return this.left.addNode(valueNode);
       }

     } else if (valueNode.val > this.val) {
       // Scendo al livello successivo e incremento la profondità del nodo da inserire
       valueNode.depth++;
       // Se il valore è più grande del valore del nodo corrente, lo inserisco a destra
       if (this.right == null) {
         this.right = valueNode;
         return this.right.depth;
       } else {
         return this.right.addNode(valueNode);
       }

     }
  }

  visit() {
    // Visito a sinistra finchè non è vuoto
    if (this.left != null) {
      this.left.visit();
    }
    // Scrivo il valore
    console.log(this.val);
    // Visito a destra finchè non è vuoto
    if (this.right != null) {
      this.right.visit();
    }
  }

  search(value) {
    if (this.val === value) {
      return this;
    } else {
      if (this.val > value) {
        return this.left.search(value);
      } else {
        return this.right.search(value);
      }
    }
  }

  // Funzione per disegnare un nodo e tutti i sottonodi attaccati, è necessario conoscere la profondità massima per gestire le distanze di disegno
  render(maxDepth) {
    noFill();
    stroke(255);
    ellipse(this.x, this.y, this.r * 2);
    textAlign(CENTER);
    text(this.val, this.x, this.y);

    if (this.left != null) {
      this.left.x = this.x - (width/2**maxDepth);
      this.left.y = this.y + (60);
      line(this.x, this.y, this.left.x, this.left.y);
      this.left.render(maxDepth);
    }
    if (this.right != null) {
      this.right.x = this.x + (width/2**maxDepth);
      this.right.y = this.y + (60);
      line(this.x, this.y, this.right.x, this.right.y);
      this.right.render(maxDepth);
    }

  }

}
