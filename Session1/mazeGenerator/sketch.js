let griglia = []; // Array bidimensionale di celle
let cols, rows;
let scale = 20;
let currentCell;


function setup() {
  createCanvas(400, 400);
  background(0);
  cols = floor(width / scale); // Numero di colonne
  rows = floor(height / scale); // Numero di righe
  console.log("colonne: ", cols);
  console.log("righe: ", rows);

  createGrid();
  // Inizio dalla prima cella in alto a destra
  currentCell = griglia[0][0];

}

function draw() {
  // Implemento l'algoritmo direttamente qui utilizzando il loop predefinito di draw di p5js
  frameRate(10);
  // Imposto la cella corrente come cella corrente
  currentCell.setCurrent(true);
  // Imposto visitata la cella corrente
  currentCell.visit();
  // Prendo la prossima cella
  let next = currentCell.getVicino();
  // Disegno la griglia
  showGrid();
  // Se si può prendere una cella, aggiorno la cella corrente
  if (next) {
    // Cambio cella corrente
    currentCell.setCurrent(false);
    currentCell = next;
  }



}


function showGrid() {
  // Disegna la griglia
  for (let row of griglia) {
    for (let cella of row) cella.show();
  }
}

function createGrid() {
  // Popolo l'array di celle
  for (let x = 0; x < rows; x++) {
    let row = []
    for (let y = 0; y < cols; y++) {
      row.push(new Cell(x, y));
    }
    griglia.push(row);
  }
}
