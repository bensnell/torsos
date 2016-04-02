#include "ofApp.h"

const string allowed_ext[] = {"jpg", "png", "gif", "jpeg"};

void ofApp::scan_dir_imgs(ofDirectory dir){
    ofDirectory new_dir;
    int size = dir.listDir();
    for (int i = 0; i < size; i++){
        if (dir.getFile(i).isDirectory()){
            new_dir = ofDirectory(dir.getFile(i).getAbsolutePath());
            new_dir.listDir();
            new_dir.sort();
            scan_dir_imgs(new_dir);
        } else if (std::find(std::begin(allowed_ext),
                             std::end(allowed_ext),
                             dir.getFile(i).getExtension()) != std::end(allowed_ext)) {
            imageFiles.push_back(dir.getFile(i));
        }
    }
}

//--------------------------------------------------------------
void ofApp::setup(){

    // APP PARAMS
    string imageDir = "../../../../../../../../../Volumes/BenSnell/torsos-7k/photos-jpg";
    string folderName = "torsos_7k_bw_color";
    nx = 86;
    ny = 86;
    w = 60;
    h = 90;
    
    // get images recursively from directory
    ofLog() << "Gathering images...";
    ofDirectory dir = ofDirectory(imageDir);
    // scan image directory
    scan_dir_imgs(dir);
    if (imageFiles.size() < nx * ny) {
        ofLog(OF_LOG_ERROR, "There are less images in the directory than the grid size requested (nx*ny="+ofToString((nx*ny))+"). Exiting to save you trouble...");
        ofExit(); // not enough images to fill the grid, so quitting
    }

    // load all the images
    for(int i=0; i<nx*ny; i++) {
        if (i % 20 == 0)    ofLog() << " - loading image "<<i<<" / "<<nx*ny<<" ("<<dir.size()<<" in dir)";
        images.push_back(ofImage());
        images.back().load(imageFiles[i]);
    }
    
    // resize images to w x h
    for (int i=0; i<images.size(); i++) {
        if (images[i].getWidth() > images[i].getHeight()) {
            images[i].crop((images[i].getWidth()-images[i].getHeight()) * 0.5, 0, images[i].getHeight(), images[i].getHeight());
        }
        else if (images[i].getHeight() > images[i].getWidth()) {
            images[i].crop(0, (images[i].getHeight()-images[i].getWidth()) * 0.5, images[i].getWidth(), images[i].getWidth());
        }
        images[i].resize(w, h);
    }
    
    // turn tsneVecs into a grid
    
    // load the csv data into tsneCoords and gridCoords
    ofFile file(folderName + "/tsne_metadata.csv");
    ofBuffer buffer(file);
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string thisLine = *it;
        vector<string> line = ofSplitString(thisLine, ",");
        if (it == buffer.getLines().begin()) continue;
        
        // add data to vectors
        tsneCoords.push_back(ofVec2f(ofToFloat(line[5]), ofToFloat(line[6])));
        gridCoords.push_back(ofVec2f(ofToFloat(line[3]), ofToFloat(line[4])));
    }
    ofLog() << "TSNE and GRID data loaded...";

    // save image grid
    bool bSaveGrid = true;
    if (bSaveGrid) {
        string imageGridName = "tsne_grid.png";
        ofFbo fbo;
        fbo.allocate(nx * w, ny * h);
        fbo.begin();
        ofClear(0, 0);
        ofBackground(0);
        for (int i=0; i<gridCoords.size(); i++) {
            float x = (fbo.getWidth() - w) * gridCoords[i].x;
            float y = (fbo.getHeight() - h) * gridCoords[i].y;
            images[i].draw(x, y, w, h);
        }
        fbo.end();
        ofImage img;
        fbo.readToPixels(img);
        img.save(folderName + "/" + imageGridName);
        ofLog() << "GRID image saved.";
    }
    
    // save image clusters
    bool bSaveClusters = true;
    float imgScale = 0.5;
    if (bSaveClusters) {
        string imageClustersName = "tsne_clusters.png";
        ofFbo fbo;
        fbo.allocate(nx * w, ny * h);
        fbo.begin();
        ofClear(0, 0);
        ofBackground(255);
        for (int i=0; i<tsneCoords.size(); i++) {
            float x = (fbo.getWidth() - w) * tsneCoords[i].x;
            float y = (fbo.getHeight() - h) * tsneCoords[i].y;
            ofSetColor(255, 180);
            images[i].draw(x, y, w * imgScale, h * imgScale);
            ofSetColor(0);
            ofDrawBitmapString(imageFiles[i].getFileName(), x, y + h * imgScale);
        }
        fbo.end();
        ofImage img;
        fbo.readToPixels(img);
        img.save(folderName + "/" + imageClustersName);
        ofLog() << "TSNE clusters image saved";
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
