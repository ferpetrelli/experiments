import Vehicle from './vehicleClass';

var containerSize = function() {
  let element = document.getElementById('m-canvas-chords')

  let width = element.clientWidth;
  let height = element.clientHeight;

  return {
    width: width,
    height: height
  }
}

let canvasDefinition = (p) => {

  p.info = {
    vehicles: [],
    formattedText: "Connect...",
    maxChangeForce: 0,
    font: null,
    prevSec: -1,
  }

  p.windowResized = function() {
    let width  = p.floor(containerSize().width);
    let height = p.floor(containerSize().height);
    p.resizeCanvas(width, height);
    p.updateText('Resized');
  }

  p.preload = function() {
    p.info.font = p.loadFont('/assets/fonts/inconsolata.otf');
  }

  p.fontSize = function() {
    return p.width / 5 / p.min(2, p.info.formattedText.length);
  }

  p.particleSize = function() {
    return p.fontSize() / 30;
  }

  p.setup = function() {
    p.createCanvas(containerSize().width, containerSize().height);
    p.background('#f6e05e');

    var bounds = p.info.font.textBounds(p.info.formattedText, 0, 0, p.fontSize());
    var posx = p.width / 2 - bounds.w / 2;
    var posy = p.height / 2 + bounds.h / 2;
    var points = p.info.font.textToPoints(p.info.formattedText, posx, posy, p.fontSize(), {
        sampleFactor: 0.2
    });

    for (var i = 0; i < points.length; i++) {
        var pt = points[i];
        var vehicle = new Vehicle(pt.x, pt.y, p.particleSize(), p);
        p.info.vehicles.push(vehicle);
    }
  };

  p.draw = function() {
    p.background('#f6e05e');

    for (let a = 0; a < p.info.vehicles.length; a++) {
      let v = p.info.vehicles[a];
      v.solve();
      v.update();
      v.show();
    }

  }

  p.updateText = function(newText) {
      p.info.formattedText = newText;
      var bounds = p.info.font.textBounds(p.info.formattedText, 0, 0, p.fontSize());
      var posx = p.width / 2 - bounds.w / 2;
      var posy = p.height / 2 + bounds.h / 2;

      var points = p.info.font.textToPoints(p.info.formattedText, posx, posy, p.fontSize(), {
          sampleFactor: 0.2
      });

      if (points.length < p.info.vehicles.length) {
          var toSplice = p.info.vehicles.length - points.length;
          p.info.vehicles.splice(points.length - 1, toSplice);

          for (var i = 0; i < points.length; i++) {
              p.info.vehicles[i].setTarget(points[i].x, points[i].y);
          }
      } else if (points.length > p.info.vehicles.length) {

          for (var i = p.info.vehicles.length; i < points.length; i++) {
              var v = p.info.vehicles[i - 1].clone();
              p.info.vehicles.push(v);
          }

          for (var i = 0; i < points.length; i++) {
              p.info.vehicles[i].setTarget(points[i].x, points[i].y);
          }

      } else {
          for (var i = 0; i < points.length; i++) {
              p.info.vehicles[i].setTarget(points[i].x, points[i].y);
          }
      }
  }

}

export default canvasDefinition;
