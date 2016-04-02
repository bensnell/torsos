#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void keyPressed(int key);
	
	ofxCv::ObjectFinder finder;
    
    ofDirectory dir;
    
    int lastCounter = -1;
    int imgCounter = 0;
    ofImage thisImg;
    
};
