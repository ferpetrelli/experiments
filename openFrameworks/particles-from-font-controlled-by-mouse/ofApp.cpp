#include "ofApp.h"

ofTrueTypeFont font;

const string TEXT = "Hola";
const int PARTICLES_NUMBER = 1000;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);

    // Load font and get control points from a piece of text
    font.load(OF_TTF_SANS, 200, true, true, true);
    contourPoints = font.getStringAsPoints(TEXT);

    // Translate coordinates to the center of the window
    ofRectangle r = font.getStringBoundingBox(TEXT, 0, 0);
    ofTranslate(ofGetWindowWidth() / 2 - r.width * 0.5f, ofGetWindowHeight() / 2 + r.height * 0.5f);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Randomize the same numbers on each frame
    ofSeedRandom(1);

    // Halo effect when mouse button is pressed
    if (!ofGetMousePressed()) {
        ofBackground(0);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    int spread;
    float px;
    float py;

    // Let's translate the text to the center of the window
    ofRectangle r = font.getStringBoundingBox(TEXT, 0, 0);
    ofTranslate(ofGetWindowWidth() / 2 - r.width * 0.5f, ofGetWindowHeight() / 2 + r.height * 0.5f);

    // Spread the particles more or less depending on the mouse horizontal position
    spread = ofMap(ofGetMouseX(), 0, ofGetScreenWidth(), 0, 400);

    for( int i = 0; i < contourPoints.size(); i++){
        contourPoints[i].setStrokeWidth(2);
        polylines = contourPoints[i].getOutline();

        for ( int j = 0; j < polylines.size() ; j++) {

            // Spread dots evenly (otherwise they will be only the polygon control points)
            polylines[j] = polylines[j].getResampledByCount( PARTICLES_NUMBER );

            for (int k = 0; k < polylines[j].size(); k++) {

                // Draw each particle with some Perlin noise
                px = polylines[j][k].x + ofMap(ofNoise(ofRandom(PARTICLES_NUMBER), ofGetFrameNum() * 0.005), 0, 1, -spread, spread);
                py = polylines[j][k].y + ofMap(ofNoise(ofRandom(PARTICLES_NUMBER), ofGetFrameNum() * 0.005), 0, 1, -spread, spread);

                ofDrawCircle(px, py, 0.9);

            }

        }

    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
