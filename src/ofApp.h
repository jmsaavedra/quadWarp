#pragma once

#include "ofMain.h"

//TODO: implement for more than 4 points (corners) !
#define NUM_WARP_POINTS 4 //power of 2

class ofApp : public ofBaseApp{

public:

    void setup();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void quadWarp(ofBaseHasTexture &tex, ofPoint lt, ofPoint rt, ofPoint rb, ofPoint lb, int rows, int cols);
    int getIndex(float x, float y, float w);
    ofPoint lerp(ofPoint start, ofPoint end, float amt);
    
    ofImage img;
    ofPoint warpPoints[NUM_WARP_POINTS];
    int selectedCorner;

};
