#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxAssimpModelLoader.h"
#include "ofxProCamToolkit.h"
#include "ofxAutoControlPanel.h"
//#include "LineArt.h"

class ofApp : public ofBaseApp {
public:
	void setb(string name, bool value);
	void seti(string name, int value);
	void setf(string name, float value);
	bool getb(string name);
	int geti(string name);
	float getf(string name);
	
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	
	void setupControlPanel();
	void setupMesh();
	void drawLabeledPoint(int label, ofVec2f position, ofColor color, ofColor bg = ofColor::black, ofColor fg = ofColor::white);
	void updateRenderMode();
	void drawSelectionMode();
	void drawOverlay();
	void drawRenderMode();
	void render();
	void saveCalibration();
	void saveXyzMap();
	
	ofImage referenceImage;
	ofShader xyzShader, normalShader;
	float range;
	ofVec3f zero;
	ofFbo fboPositions, fboNormals;
	
	ofxAssimpModelLoader model;	
	ofEasyCam cam;
	ofVboMesh objectMesh;
	ofMesh imageMesh;
	ofLight light;
	ofxAutoControlPanel panel;
	
	vector<cv::Point3f> objectPoints;
	vector<cv::Point2f> imagePoints;
	vector<bool> referencePoints;
	
	cv::Mat rvec, tvec;
	ofMatrix4x4 modelMatrix;
	ofxCv::Intrinsics intrinsics;
	bool calibrationReady;
	
	Poco::Timestamp lastFragTimestamp, lastVertTimestamp;
	Poco::Timestamp lastFragTimestampXyz, lastVertTimestampXyz;
	ofShader shader;
};
