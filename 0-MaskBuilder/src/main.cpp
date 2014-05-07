#include "ofMain.h"
#include "ofAppGlutWindow.h"

int sw, sh, sc;

class ofApp : public ofBaseApp {
public:
	ofFbo fbo;
	ofVec2f mouseCur, mousePrev;
	float radius;
	int screen;
	
	void setup() {
		radius = 10;
		screen = 0;
		fbo.allocate(sw, sh);
		fbo.begin();
		ofClear(0, 255);
		fbo.end();
		ofHideCursor();
	}
	void update() {
		fbo.begin();
		ofPushStyle();
		if(ofGetKeyPressed()) {
			ofSetColor(0);
		} else {
			ofSetColor(255);
		}
		if(ofGetMousePressed()) {
			float length = mousePrev.distance(mouseCur);
			for(int i = 0; i < length; i++) {
				ofCircle(mousePrev.getInterpolated(mouseCur, i / length), radius);
			}
			mousePrev = mouseCur;
		}
		ofPopStyle();
		fbo.end();
	}
	void draw() {
		ofBackground(0);
		ofTranslate(sw * screen, 0);
		fbo.draw(0, 0);
		ofPushStyle();
		ofNoFill();
		ofSetColor(255);
		ofCircle(mouseCur, radius);
		ofFill();
		ofSetColor(255, 64);
		ofCircle(mouseCur, radius);
		ofPopStyle();
	}
	void mouseMoved(int x, int y) {
		mouseCur.set(x - sw * screen, y);
	}
	void mouseDragged(int x, int y, int b) {
		mouseCur.set(x - sw * screen, y);
	}
	void mousePressed(int x, int y, int b) {
		mousePrev.set(x - sw * screen, y);
	}
	void keyPressed(int key) {
		if(key == '=') {
			radius+=5;
		}
		if(key == '-') {
			radius-=5;
		}
		if(key == 'f') {
			ofToggleFullscreen();
		}
		if(key == '\t') {
			screen = (screen + 1) % sc;
		}
	}
	void mouseReleased(int x, int y, int b) {
		ofPixels pix;
		fbo.readToPixels(pix);
		ofSaveImage(pix, "mask-" + ofToString(screen) + "-" + ofGetTimestampString() + ".png");
	}
};

int main() {
	ofSetWorkingDirectoryToDefault();
	ofXml settings;
    settings.load("../../../SharedData/settings.xml");
	sc = settings.getIntValue("projectors/count");
	sw = settings.getIntValue("projectors/width");
	sh = settings.getIntValue("projectors/height");
	
	ofSetupOpenGL(ofPtr<ofAppBaseWindow>(new ofAppGlutWindow()), sw * sc, sh, OF_FULLSCREEN);
	ofRunApp(new ofApp());
}