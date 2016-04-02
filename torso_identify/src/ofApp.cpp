#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(120); // ?
    
    // setup torso finder
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Accurate); // Fast, Accurate, Sensitive
    
    // load directory of images
    string srcDirPath = "../../../../../../../../../Volumes/BenSnell/torsos-7k/photos-jpg-bw-equalize";
    dir.open(srcDirPath);
    dir.allowExt("jpg");
    dir.listDir(); // populate directory
    
}

void ofApp::update() {
    
    // if the counter has been incremented, attempt to find the next torso
    if (lastCounter != imgCounter) {
        thisImg.clear();
        thisImg.load(dir.getFile(imgCounter));
        finder.update(thisImg);
    }
    lastCounter = imgCounter;
    
}

void ofApp::draw() {
    
    thisImg.draw(0, 0);
    finder.draw();
    
	ofDrawBitmapStringHighlight(ofToString(finder.size()), 10, 20);
}


void ofApp::keyPressed(int key) {
    
    if (key == ' ') {
        imgCounter++;
        if (imgCounter >= dir.size()) {
            cout << "no more files in directory to analyze" << endl;
            imgCounter--;
        }
    }
    
}