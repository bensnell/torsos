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

    int counter = 0;
    ofDirectory dir;
    
    int imgW = 170;
    int imgH = 255;
    
    string highDir = "generated_torsos_2";
    string srcFolder = "gen_torsos_15k";
    string dstFolder = "gen_torsos_15k_bw_lowres";
    string srcType = "jpg";
    string dstType = "jpg";
    
};


