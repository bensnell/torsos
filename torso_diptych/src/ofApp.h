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
    
    int imgW = 340;
    int imgH = 510;
    int margin = 100;
    
    /* Layout
     
       imgA imgB
      ___________
     |  __   __  |
     | |  | |  | |
     | |__| |__| |
     |___________|
     
     */
    
    string folderName = "generated_torsos_15k_bw";
    
};


