

let target = "ciao come stai sei una persona molto speciale";
let pop;
let generazione, migliore;


function setup() {
  generazione = createP();
  migliore = createP();
  pop = new Popolazione(1000, target, 0.01);


}



function draw() {
  pop.valutaFit();
  pop.makePool();
  pop.valutaGenerazione();
  if (pop.finito) {
    noLoop();
  }
  migliore.html(pop.best);
  generazione.html(pop.generazione);
  pop.nuovaGenerazione();
}
