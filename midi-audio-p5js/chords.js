// Libraries used to identify notes and chords
import { chordType } from "@tonaljs/chord-dictionary";
import { pcset }     from "@tonaljs/pcset";

// P5.js library
import * as p5 from './vendor/p5';

// Midi connector implementation
import * as WebMidi from "webmidi";

// Vehicle with steering
import Vehicle from './libraries/vehicleClass';

// Canvas definition with transitions
import canvasDefinition from './libraries/canvasDefinition';

// Save our currently pressed notes and Midi input
let notes = [];
let input;

// Initialize Canvas
var canvas = new p5(canvasDefinition, 'canvas-chords');

// Load Piano definition
require('./vendor/instruments/piano.js');

// Initialize Sound system
let webaudiofont = require('webaudiofont');
var AudioContextFunc = window.AudioContext || window.webkitAudioContext;
var audioContext = new AudioContextFunc();
let player = new WebAudioFontPlayer();

// Mount the Piano
player.loader.decodeAfterLoading(audioContext, '_tone_0000_GeneralUserGS_sf2_file');

function playKey(pitch){
  player.queueWaveTable(audioContext, audioContext.destination, _tone_0000_GeneralUserGS_sf2_file, 0, pitch, 0.75);
}

// Function used to create radio buttons with our midi options
const reusable = (name) => {
  return `
    <input type="radio" name="midi" value="${name}" onSelect>
    <label for="${name}">${name}</label>
  `;
}

// Create Midi selectors
function createMidiOptions(inputs) {
  let container = document.getElementById('midi-devices');
  for (let i=0; i < inputs.length; i++) {
    let element = document.createElement('p');
    element.innerHTML = reusable(inputs[i].name);
    element.addEventListener('change', function(e) {
      if (input) { input.removeListener(); }
      input = WebMidi.getInputByName(e.target.value);
      activateInput(input);
      canvas.updateText('Play!');
    });
    container.append(element);
  }
}

function activateInput(input) {
  input.addListener('noteon', "all", function(e) {
    let fullNoteName = e.note.name + e.note.octave;
    notes.push(fullNoteName.toLowerCase());
    canvas.updateText(notes[0] + ' ' + chordType(pcset(notes).chroma).name);
    playKey(e.note.number);
  });

  input.addListener('noteoff', "all", function(e) {
    let fullNoteName = e.note.name + e.note.octave;
    notes = notes.filter(function(ele){
       return ele != fullNoteName.toLowerCase();
    });
  });
}

document.querySelector('.enable-midi-audio').addEventListener('click', function() {
  audioContext.resume().then(() => {
    console.log('Playback resumed successfully');
  });

  WebMidi.enable(function (err) {

    if (err) {
      console.log("WebMidi could not be enabled.", err);
      canvas.updateText("Error. See js log");
    } else {
      canvas.updateText("WebMidi enabled!");
    }

    createMidiOptions(WebMidi.inputs);

  });
});
