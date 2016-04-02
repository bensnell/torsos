#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    string path = "../../../../../../../../../Volumes/BenSnell/generated_torsos/generated_torsos_15k"; // path to higher directory
    dir = ofDirectory(path);
    dir.listDir();
    
    // iterate through each view
    for (int i = 0; i < dir.size(); i++) {
        
        ofDirectory subDir(dir.getPath(i)); // view folder
        subDir.allowExt("jpg");
        subDir.listDir();
        
        for (int j = 0, end = subDir.size(); j < end; j++) {
            
            ofImage img(subDir.getFile(j));
            img.setImageType(OF_IMAGE_GRAYSCALE); // turn image black and white
            img.resize(imgW, imgH); // assumes aspect ratio is 2:3 (width:height)
            
            // equalize the histogram
            // search for darkest and lightest greys
            int nPixels = img.getPixels().size();
            int minBrightness = 255;
            int maxBrightness = 0;
            ofPixelsRef pixelRef = img.getPixels();
            for (int i = 0; i < nPixels; i++) {
                int val = int(pixelRef[i]);
                if (val < minBrightness) minBrightness = val;
                if (val > maxBrightness) maxBrightness = val;
            }
            // equalize all pixels
            for (int i = 0; i < nPixels; i++) {
                pixelRef[i] = int((pixelRef[i] - minBrightness) / float(maxBrightness - minBrightness) * 255.);
            }
            img.update();
            
            string name = dir.getName(counter);
            string newpath = "../../../../../../../../../Volumes/BenSnell/generated_torsos/" + folderName + "/" + dir.getName(i) + "/" +subDir.getName(j);
            
            // Save image
            img.save(newpath); // may not save properly
            
            // ALT: Save screen
            //            img.draw(0, 0);
            //            ofSaveScreen(newpath);
            
            img.clear();
            
        }
        cout << "Completed conversion of " + ofToString(subDir.size()) + " images in " + dir.getName(i) << endl;
    }
    
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
