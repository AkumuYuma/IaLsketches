// Script per costruire e utilizzare un binary search Tree
let t;

function setup() {
  noCanvas();
  t = new Tree();

  for (let i = 0; i < 10; i++) {
    t.addElement(floor(random(0, 100)));
  }

  t.traverse();
}
