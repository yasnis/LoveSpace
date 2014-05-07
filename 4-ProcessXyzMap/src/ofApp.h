#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxCv.h"
#include "ofAutoShader.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofFloatImage xyzMap;
    ofFloatImage normalMap;
    ofFloatImage confidenceMap;
	ofAutoShader shader;
    
    ofImage img;
    
//    ofFbo wallFbo;
};