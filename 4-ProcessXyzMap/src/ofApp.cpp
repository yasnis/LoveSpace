#include "ofApp.h"

void ofApp::setup() {
    
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(true);
	ofSetFrameRate(120);
	shader.setup("shader");
    
    
    //for MirrorBall
    img.loadImage("image.png");
    mask.loadImage("mask.png");
    
	xyzMap.loadImage("xyzMap.exr");
    normalMap.loadImage("normalMap.exr");
    confidenceMap.loadImage("confidenceMap.exr");
    
//    wallFbo.allocate(2048, 200);
//    ofHideCursor();
//    ofToggleFullscreen();
    
    
    
    //for Audio
	soundStream.listDevices();
	int bufferSize = 256;
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
    
    //for OSC
	ofXml settings;
	settings.load("../../../SharedData/settings.xml");
	oscIn.setup(9000);
	oscOut.setup(settings.getValue("osc/iphone/address"), 9001);
}

void ofApp::update() {
    //for MirrorBall
    
    //for Audio
	//lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.05, 0.0, 1.0, true);
//    cout << scaledVol << endl;
    
    //for OSC
	ofxOscMessage msgIn;
	while(oscIn.getNextMessage(&msgIn)) {
		if(msgIn.getAddress() == "/Effect/type/1/1") {
            type = 0;
		}else if(msgIn.getAddress() == "/Effect/type/1/2"){
            type = 1;
        }else if(msgIn.getAddress() == "/Effect/type/1/3"){
            type = 2;
        }else if(msgIn.getAddress() == "/Effect/type/1/4"){
            type = 3;
        }else if(msgIn.getAddress() == "/Effect/type/2/1"){
            type = 4;
        }else if(msgIn.getAddress() == "/Effect/type/2/2"){
            type = 5;
        }else if(msgIn.getAddress() == "/Effect/type/2/3"){
            type = 6;
        }else if(msgIn.getAddress() == "/Effect/type/2/4"){
            type = 7;
        }else if(msgIn.getAddress() == "/Value/slider1"){
            value1 = msgIn.getArgAsFloat(0);
        }else if(msgIn.getAddress() == "/Value/slider2"){
            value2 = msgIn.getArgAsFloat(0);
        }else if(msgIn.getAddress() == "/Value/field"){
            value3.set(msgIn.getArgAsFloat(0), msgIn.getArgAsFloat(1));
        }
        cout << "type : " << type << endl;
        cout << "\tvalue1 : " << value1 << endl;
        cout << "\tvalue2 : " << value2 << endl;
        cout << "\tvalue3 : " << value3 << endl;
	}
}

void ofApp::draw() {
	ofBackground(64);
//    /*
	shader.begin();
    
	shader.setUniform1f("soundVolume", scaledVol);
	shader.setUniform1i("effectType", type);
	shader.setUniform1f("effectValue1", value1);
	shader.setUniform1f("effectValue2", value2);
	shader.setUniform2f("effectValue3", value3[0], value3[1]);
	shader.setUniform1f("elapsedTime", ofGetElapsedTimef());
    
	shader.setUniformTexture("xyzMap", xyzMap, 0);
	shader.setUniformTexture("normalMap", normalMap, 2);
    shader.setUniformTexture("confidenceMap", confidenceMap, 3);
    shader.setUniformTexture("texture", img.getTextureReference(), 1);
    
	xyzMap.draw(0, 0);
	shader.end();
//*/
    
    ofSetColor(245, 58, 135);
    ofFill();
    ofCircle(ofGetWidth()/2, ofGetHeight()/2, scaledVol * 190.0f);
    
//    wallFbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    mask.draw(0, 0);
}

void ofApp::keyPressed(int key) {
    if(key == 'f'){
        ofToggleFullscreen();
    }
}






//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	float curVol = 0.0;
	// samples are "interleaved"
	int numCounted = 0;
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	bufferCounter++;
}