// Inspired entirely by Daniel Shiffman's
// Steering Text Paths
// http://codingtra.in

export default class Vehicle {

  constructor(x, y, size, p5_instance) {
    this.p5 = p5_instance;

    this.pos = this.p5.createVector(this.p5.random(this.p5.width), this.p5.random(this.p5.height));
    this.vel = this.p5.createVector(this.p5.random(-1,1),this.p5.random(-1,1)).normalize();
    this.acc = this.p5.createVector(0, 1).normalize();
    this.target = this.p5.createVector(x, y);

    if (size != null) {
        this.r = size;
    } else {
        this.r = 8;
    }

    this.maxspeed = 10;
    this.maxforce = 1;
  }

  setTarget(x,y) {
    this.target = this.p5.createVector(x,y);
  }

  solve() {
    this.applyForce(this.calculateSteerForce());
  }

  applyForce(f) {
    this.acc.add(f);
  }

  update() {
    this.pos.add(this.vel);
    this.vel.add(this.acc);
    this.acc.mult(0);
  }

  show() {
    this.p5.stroke('#f56565');
    this.p5.strokeWeight(this.r);
    this.p5.point(this.pos.x, this.pos.y);
  }

  calculateSteerForce() {
    // p5.Vector.sub is not available on instance mode so substracting manually
    let desired = this.p5.createVector(this.target.x - this.pos.x, this.target.y - this.pos.y);

    // Calculate max speed
    let d = desired.mag();
    let speed = this.maxspeed;
    if (d < 100) {
        speed = this.p5.map(d, 0, 100, 0, this.maxspeed);
    }
    desired.setMag(speed);

    // Create a steer vector
    let steer = this.p5.createVector(desired.x - this.vel.x, desired.y - this.vel.y);
    steer.limit(this.maxforce);

    return steer;
  }

  clone() {
    var v = new Vehicle(this.pos.x, this.pos.y, this.r, this.p5);

    v.pos.x = this.pos.x;
    v.pos.y = this.pos.y;

    v.vel.x = this.vel.x;
    v.vel.y = this.vel.y;

    v.acc.x = this.acc.x;
    v.acc.y = this.acc.y;

    return v;
  }

}
