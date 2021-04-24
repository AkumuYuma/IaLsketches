class Tree {
  // Costruisco l'albero con un riferimento alla radice
  constructor() {
    this.root = null;
    this.maxDepth = 0;
  }

  // Aggiungo un elemento all'albero
  addElement(value) {
    // Creo un nuovo nodo
    let valueNode = new Node(value);

    if (this.root == null) {
      // Se l'albero è vuoto aggiungo il primo nodo
      this.root = new Node(value, width/2, 20);
    } else {
      // Altrimenti aggiungo un nodo in base al valore
      let currentDepth = this.root.addNode(valueNode);
      // Aggiorno la profondità massima dell'albero
      if (currentDepth > this.maxDepth) {
        this.maxDepth = currentDepth;
      }
    }


  }

  traverse() {
    this.root.visit();
  }

  search(value) {
    return this.root.search(value);
  }

  show() {
    this.root.render(this.maxDepth);
  }

}
