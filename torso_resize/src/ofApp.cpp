#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    string path = "../../../../../../../../../Volumes/BenSnell/torsos-7k/photos-jpg"; // source directory
    dir = ofDirectory(path);
//    dir.allowExt("PNG");
//    dir.allowExt("png");
    dir.allowExt("jpg");
    dir.listDir();
    
//    for (int i = 0; i < dir.size(); i++) {
//        ofImage img(dir.getFile(i));
//        img.resize(340, 510);
//        string name = dir.getName(i);
//        string newpath = "../../../../../../../../../Volumes/BenSnell/torsos-7k/newphotos-jpg/" + (dir.getName(i)).substr(0, 11) + ".jpg";
//        img.save(newpath);
////        cout << newpath << endl;
//        img.clear();
//    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofImage img(dir.getFile(counter));
    img.setImageType(OF_IMAGE_GRAYSCALE); // turn image black and white
    img.resize(imgW, imgH);
    
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
    
    img.draw(0, 0);
    string name = dir.getName(counter);
    string newpath = "../../../../../../../../../Volumes/BenSnell/torsos-7k/" + folderName + "/" + (dir.getName(counter)).substr(0, 11) + ".jpg";
//    img.save(newpath); // may not save properly
    ofSaveScreen(newpath);
    //        cout << newpath << endl;
    img.clear();
    counter++;

    if(counter == dir.size()) exit();
    
    
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
