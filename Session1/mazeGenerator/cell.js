

class Cell {
  constructor(x, y) {
    // Posizione
    this.x = x * scale;
    this.y = y * scale;
    this.walls = [true, true, true, true] // Top, right, bottom left walls
  }

  show() {
    noFill();
    stroke(255);
    if (this.walls[0]) line(this.x, this.y, this.x + scale, this.y);
    if (this.walls[1]) line(this.x + scale, this.y, this.x + scale, this.y + scale);
    if (this.walls[2]) line(this.x + scale, this.y + scale, this.x, this.y + scale);
    if (this.walls[3]) line(this.x, this.y + scale, this.x, this.y);
  }
}
