#include "TreeNode.hpp"
#include "ofMain.h"

struct TreeNode {
    TreeNode *left;   // Pointer to the left subtree.
    TreeNode *right;  // Pointer to the right subtree.

    int level;      // Current level
    int levelMax;   // Save the whole tree maximum level. Used basically for color
    int angle;      // Branch angle
    ofPoint start;
    ofPoint endPoint;

    int maxLength;  // Branch max length. We make it smaller each recursive call


    TreeNode(int l, int a, ofPoint s, ofPoint e, int maxL = 80) {
        level = l;
        angle = a;
        start = s;
        endPoint = e;
        maxLength = maxL;

        left = NULL;
        right = NULL;
    }


    TreeNode() {
        left = NULL;
        right = NULL;
    }


    void build(int buildLevelMax) {
        levelMax = buildLevelMax;

        if (level < buildLevelMax) {
            // From the current angle let's get the pair x,y
            float angleOffset = ofMap(ofRandom(0,1), 0.0, 1.0, -20, 40.0);
            float angRad = ofDegToRad(angle);
            float xOffset = cos(angRad) * maxLength;
            float yOffset = sin(angRad) * maxLength;

            // Set the endpoint and generate two new subtrees

            endPoint.set(start.x + xOffset, start.y - yOffset);
            int newLevel = level + 1;

            TreeNode *l = new TreeNode(newLevel, angle + angleOffset, endPoint, endPoint, maxLength - ofRandom(0, 10));
            TreeNode *r = new TreeNode(newLevel, angle - angleOffset, endPoint, endPoint, maxLength - ofRandom(0, 10));

            left = l;
            right = r;
            left->build(buildLevelMax);
            right->build(buildLevelMax);
        }
    }


    void render(int renderLevel, float renderPct) {

        // Default color and line width
        ofSetColor(ofMap(level, 1, levelMax, 120, 30));
        ofSetLineWidth(levelMax - level + 0.2);

        if (level < renderLevel) {
            ofDrawLine(start.x, start.y, endPoint.x, endPoint.y);

            if ( left != NULL ) {
                left->render(renderLevel, renderPct);
            }
            if ( right != NULL ) {
                right->render(renderLevel, renderPct);
            }
        } else {

            // If it's the last level let's color it differently
            if (level == levelMax) {
                ofSetColor(0, 200, 10, 70);
                ofSetLineWidth(3);
                renderPct = ofMap(renderPct, 0, 1, 0, 0.5);
            }

            // And also let's just animate a percentage to create animated growth
            float angRad = ofDegToRad(angle);
            float xOffset = cos(angRad) * maxLength * renderPct;
            float yOffset = sin(angRad) * maxLength * renderPct;

            ofDrawLine(start.x, start.y, start.x + xOffset, start.y - yOffset);
        }

    }

};

