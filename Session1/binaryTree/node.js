class Node {
  // Costruisco il nodo con due figli e un valore
  constructor(val) {
    this.val = val;
    this.left = null;
    this.right = null;
  }

  // Funzione per aggiungere un nodo a destra o a sinistra a seconda del valore
  addNode(valueNode) {
     if (valueNode.val < this.val) {
       // Se il valore da aggiungere è più piccolo, lo aggiungo a sinistra
       if (this.left == null) {
         // Se il figlio sinistro è vuoto aggiungo direttamente il nodo
         this.left = valueNode;
       } else {
         // Altrimenti rifaccio il procedimento con il figlio di sinistra
         this.left.addNode(valueNode);
       }

     } else if (valueNode.val > this.val) {
       // Se il valore è più grande, lo inserisco a destra
       if (this.right == null) {
         this.right = valueNode;
       } else {
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


}
