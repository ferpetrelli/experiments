#include "ofApp.h"
#include "TreeNode.cpp"

// Start and end points just used to build the original trees
ofPoint start;
ofPoint endPoint;

// Counters for the animation
int level; // Tree level
float pct; // Percentage to draw

const int MAX_LEVEL = 14;
const int NUMBER_OF_TREES = 3;

std::vector<TreeNode> trees;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);

    // Build a few trees
    for(int i = 1; i <= NUMBER_OF_TREES; i++) {

        // Separate all trees from each other
        start.set(ofGetWindowWidth() / (NUMBER_OF_TREES + 1) * i, ofGetWindowHeight());
        endPoint.set(start.x, start.y - 100);

        // Create the tree object and then build it completely
        TreeNode finalTree = TreeNode(1, 90, start, endPoint);
        finalTree.build(MAX_LEVEL);

        trees.push_back(finalTree);
    }

    // Initialize counters
    level = 1;
    pct = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){

    if (level < MAX_LEVEL) {
        // If it's not the last level then reset the percentage counter
        // and increase level (to draw the next section of the tree)
        pct += 0.05;
        if (pct > 1) {
            pct = 0.0;
            level++;
        }
    } else {
        // Only increase percentage until it's 100% if it's the last level
        if (pct < 1) {
            pct += 0.05;
        }
    }

    // If the mouse is pressed, rebuild trees and reset counters
    // This will draw a new set of trees
    if (ofGetMousePressed()) {
        level = 1;
        pct = 0.0;
        for(auto it = trees.begin(); it != trees.end(); it++) {
            it->build(MAX_LEVEL);
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw() {

    // Walk our trees array and draw them
    for(auto it = trees.begin(); it != trees.end(); it++) {
        it->render(level, pct);
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
