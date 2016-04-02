#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // path to images
    string hddPath = "../../../../../../../../../Volumes/BenSnell/";
    string srcPath = hddPath + "torsos-7k/photos-jpg/";
    string dstPath = hddPath + "torsos-7k/photos-diptychs/";
    
    int counter = 0;
    
    // open csv
    ofFile file("dist_between_photos_color.csv");
    ofBuffer buffer(file);
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        
        if (it == buffer.getLines().begin()) continue;
        
        string row = *it;
        vector<string> values = ofSplitString(row, ",");
        
        ofImage imgA(srcPath + values[1]);
        ofImage imgB(srcPath + values[2]);
        
        stringstream paddedCounter;
        paddedCounter << setw(5) << setfill('0') << counter;
        string fileName = "dip-" + paddedCounter.str() + "_imgA-" + values[1].substr(6, 5) + "_imgB-" + values[2].substr(6, 5) + ".jpg";
        
        // draw to frame buffer object
        ofFbo fbo;
        fbo.allocate(imgW * 2 + margin * 3, imgH + 2 * margin, GL_RGB);
        fbo.begin();
        ofClear(255, 0); // ?
        ofBackground(255);
        imgA.draw(margin, margin);
        imgB.draw(2 * margin + imgW, margin);
        fbo.end();
        
        // put fbo in image and save to file
        ofImage img;
        fbo.readToPixels(img.getPixels()); // do you need .getPixels()?
        img.save(dstPath + fileName);

        if (counter % 100 == 0) cout << "saved " + ofToString(counter) + " diptychs..." << endl;
        
        counter++;
    }
    
    ofExit();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
