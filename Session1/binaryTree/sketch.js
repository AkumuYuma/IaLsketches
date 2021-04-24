// Script per costruire e utilizzare un binary search Tree

let t;

function setup() {
  t = new Tree();

  for (let i = 0; i < 10; i++) {
    t.addElement(i);
  }

  t.traverse();

  let result = t.search(5);
  if (result != null) {
    console.log("Trovato!");
    console.log(result);
  } else {
    console.log("Non trovato");
  }
}
