let griglia = []; // Array bidimensionale di celle
let cols, rows;
let scale = 20;
let currentCell;
let stack = [];

function setup() {
  createCanvas(800, 800);
  background(0);
  cols = floor(width / scale); // Numero di colonne
  rows = floor(height / scale); // Numero di righe
  console.log("colonne: ", cols);
  console.log("righe: ", rows);

  createGrid();
  // Inizio dalla prima cella in alto a destra
  let start = griglia[0][0];
  // Imposto la prima cella come corrente (per visualizzazione)
  start.setCurrent(true);
  // Contrassegno la prima cella come visitata
  start.visit();
  stack.push(start);
}

function draw() {
  // Implemento l'algoritmo direttamente qui utilizzando il loop predefinito di draw di p5js
  frameRate(60);

  if (stack.length > 0) {
    currentCell = stack.pop();

    // Disegno la griglia con la cella corrente evidenziata
    currentCell.setCurrent(true);
    showGrid();
    currentCell.setCurrent(false);
    // Rimuovo l'evidenza alla cella corrente

    // Prendo la prossima cella
    let next = currentCell.getVicino();
    // Se si può prendere una cella, aggiorno la cella corrente
    if (next) {
      // Cambio cella corrente
      stack.push(currentCell);
      next.visit();
      stack.push(next);
    }
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
