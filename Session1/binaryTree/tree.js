class Tree {
  // Costruisco l'albero con un riferimento alla radice
  constructor() {
    this.root = null;
  }

  // Aggiungo un elemento all'albero
  addElement(value) {
    // Creo un nuovo nodo
    let valueNode = new Node(value);

    if (this.root == null) {
      // Se l'albero è vuoto aggiungo il primo nodo
      this.root = valueNode;
    } else {
      // Altrimenti aggiungo un nodo in base al valore
      this.root.addNode(valueNode);
    }
  }

  traverse() {
    this.root.visit();
  }

  search(value) {
    return this.root.search(value);
  }

}
