#include "ofApp.h"

//-----------------------------------------------------
void ofApp::setup() {
    img.loadImage("test.jpg");
    ofSetWindowShape(img.width+60, img.height+60);
    selectedCorner = -1;
    
    //set points to warp
    warpPoints[0].set(0,0);
    warpPoints[1].set(img.width,0);
    warpPoints[2].set(img.width,img.height);
    warpPoints[3].set(0,img.height);
}

//-----------------------------------------------------
void ofApp::update() {
 
    
}

//-----------------------------------------------------
void ofApp::draw() {
    ofTranslate(30, 30);
    quadWarp(img, warpPoints[0], warpPoints[1], warpPoints[2], warpPoints[3], 40, 40);
    
    for (int i=0; i<4; i++) {
        ofCircle(warpPoints[i],10);
    }
}

//-----------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    selectedCorner = -1;
    for (int i=0; i<4; i++) {
        if (ofDist(warpPoints[i].x, warpPoints[i].y, x-30, y-30)<10) {
            selectedCorner = i;
        }
    }
}

//-----------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    warpPoints[selectedCorner].set(x-30,y-30);
}

//-----------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    selectedCorner = -1;
}

//-----------------------------------------------------
ofPoint ofApp::lerp(ofPoint start, ofPoint end, float amt) {
    return start + amt * (end - start);
}

//-----------------------------------------------------
int ofApp::getIndex(float x, float y, float w) {
    return y*w+x;
}

//-----------------------------------------------------
void ofApp::quadWarp(ofBaseHasTexture &tex, ofPoint lt, ofPoint rt, ofPoint rb, ofPoint lb, int rows, int cols) {
    float tw = tex.getTextureReference().getWidth();
    float th = tex.getTextureReference().getHeight();
    
    ofMesh mesh;
    
    for (int x=0; x<=cols; x++) {
        float f = float(x)/cols;
        ofPoint vTop(lerp(lt,rt,f));
        ofPoint vBottom(lerp(lb,rb,f));
        ofPoint tTop(lerp(ofPoint(0,0),ofPoint(tw,0),f));
        ofPoint tBottom(lerp(ofPoint(0,th),ofPoint(tw,th),f));
        
        for (int y=0; y<=rows; y++) {
            float f = float(y)/rows;
            ofPoint v = lerp(vTop,vBottom,f);
            mesh.addVertex(v);
            mesh.addTexCoord(lerp(tTop,tBottom,f));
        }
    }
    
    for (float y=0; y<rows; y++) {
        for (float x=0; x<cols; x++) {
            mesh.addTriangle(getIndex(x,y,cols+1), getIndex(x+1,y,cols+1), getIndex(x,y+1,cols+1));
            mesh.addTriangle(getIndex(x+1,y,cols+1), getIndex(x+1,y+1,cols+1), getIndex(x,y+1,cols+1));
        }
    }
    
    tex.getTextureReference().bind();
    mesh.draw();
    tex.getTextureReference().unbind();
    mesh.drawVertices();
}

//-----------------------------------------------------