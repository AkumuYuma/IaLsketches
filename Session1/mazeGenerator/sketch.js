let celle = [];
let cols, rows;
let scale = 20;


function setup() {
  createCanvas(400, 400);
  background(0);
  cols = floor(width/scale); // Numero di colonne
  rows = floor(height/scale); // Numero di righe

  for (let x = 0; x < rows; x++) {
    for (let y = 0; y < cols; y++) {
      celle.push(new Cell(x, y));
    }
  }

  for (cella of celle) {
    cella.show(); 
  }
}
