#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofDirectory dir;
    
    // scale
    float scale = 0.5;
    
    int imgW = 340 * scale;
    int imgH = 510 * scale;
    
    // directory path
    string dirPath = "/Volumes/BenSnell/torsos-7k/";
    string srcFolder = "photos-jpg-bw-eq";
    string srcType = "jpg";
    string dstFolder = "photos-jpg-bw-eq-lowres";
    string dstType = "jpg";
    
};


