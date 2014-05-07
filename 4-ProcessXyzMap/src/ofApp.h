#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxCv.h"
#include "ofAutoShader.h"

#include "ofxOsc.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofImage mask;
	ofFloatImage xyzMap;
    ofFloatImage normalMap;
    ofFloatImage confidenceMap;
	ofAutoShader shader;
    
    ofImage img;
    
    //    ofFbo wallFbo;
    
    //for MirrorBall
    int type;
    float value1;
    float value2;
    ofVec2f value3;
    
    //for Audio
    void audioIn(float * input, int bufferSize, int nChannels);
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    int 	bufferCounter;
    int 	drawCounter;
    float smoothedVol;
    float scaledVol;
    ofSoundStream soundStream;
    
    //for OSC
	ofxOscReceiver oscIn;
	ofxOscSender oscOut;
};