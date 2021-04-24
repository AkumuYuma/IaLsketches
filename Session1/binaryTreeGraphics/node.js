class Node {
  // Costruisco il nodo con due figli e un valore
  constructor(val, x = null, y = null) {
    this.val = val;
    this.left = null;
    this.right = null;

    // Valori per la visualizzazione
    this.pos = createVector(x, y);

  }

  static depth = 1;

  // Funzione per aggiungere un nodo a destra o a sinistra a seconda del valore
  addNode(valueNode) {
     if (valueNode.val < this.val) {
       // Se il valore da aggiungere è più piccolo, lo aggiungo a sinistra
       if (this.left == null) {
         // Se il figlio sinistro è vuoto aggiungo direttamente il nodo
         this.left = valueNode;
         // Disegno il nodo
         this.left.pos.x = this.pos.x - 30/(0.2 * Node.depth);
         this.left.pos.y = this.pos.y + 60;
         this.left.show();
         line(this.pos.x, this.pos.y, this.left.pos.x, this.left.pos.y);
       } else {
         // Altrimenti rifaccio il procedimento con il figlio di sinistra
         Node.depth++;
         this.left.addNode(valueNode);
       }

     } else if (valueNode.val > this.val) {
       // Se il valore è più grande, lo inserisco a destra
       if (this.right == null) {
         this.right = valueNode;
         // Disegno il nodo
         this.right.pos.x = this.pos.x + 30/(0.2 * Node.depth);
         this.right.pos.y = this.pos.y + 60;
         this.right.show();
         line(this.pos.x , this.pos.y , this.right.pos.x , this.right.pos.y );
       } else {
         Node.depth++
         this.right.addNode(valueNode);
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

  show() {
    // Funzione per la visualizzazione del nodo
    noFill();
    stroke(255);
    // Faccio un cerchio con il valore dentro
    ellipse(this.pos.x, this.pos.y, 40);
    // Inserisco il valore del nodo all'interno
    textAlign(CENTER);
    text(this.val, this.pos.x, this.pos.y);
  }

}
