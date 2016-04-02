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
    
    // SETUP
    // imageDir, imageSavePath = location of images, path to save the final grid image
    // nx, ny = size of the grid (make sure there are at least nx*ny images in imageDir!)
    // w, h = size of the image thumbnails
    // perplexity, theta (for t-SNE, see 'example' for explanation of these)
    
    // -------------- SET FILE I/O ---------------
    
    string imageDir = "../../../../../../../../../Volumes/BenSnell/torsos-7k/photos-jpg"; // source directory
    
    string folderName = "torsos_7k_all"; // destination directory

    // -------------------------------------------
    
    nx = 87;
    ny = 87;
    w = 340;
    h = 510;
    perplexity = 75;
    theta = 0.001;

    
    /////////////////////////////////////////////////////////////////////
    // CCV activations -> t-SNE embedding -> grid assignments
    
    // get images recursively from directory
    ofLog() << "Gathering images...";
    ofDirectory dir = ofDirectory(imageDir);
    scan_dir_imgs(dir);
    if (imageFiles.size() < nx * ny) {
        ofLog(OF_LOG_ERROR, "There are less images in the directory than the grid size requested (nx*ny="+ofToString((nx*ny))+"). Exiting to save you trouble...");
//        ofExit(); // not enough images to fill the grid, so quitting
    }
    
    // load all the images
//    for(int i=0; i<nx*ny; i++) {
//        if (i % 20 == 0)    ofLog() << " - loading image "<<i<<" / "<<nx*ny<<" ("<<dir.size()<<" in dir)";
//        images.push_back(ofImage());
//        images.back().load(imageFiles[i]);
////        images.back().resize(w, h); // ADDED -- DOES THIS WORK?
//    }
    for(int i=0; i<imageFiles.size(); i++) {
        if (i % 20 == 0)    ofLog() << " - loading image "<<i<<" / "<<imageFiles.size()<<" ("<<dir.size()<<" in dir)";
        images.push_back(ofImage());
        images.back().load(imageFiles[i]);
        //        images.back().resize(w, h); // ADDED -- DOES THIS WORK?
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
    
    // setup ofxCcv
    ccv.setup("image-net-2012.sqlite3");
    
    // encode all of the images with ofxCcv
    ofLog() << "Encoding images...";
    for (int i=0; i<images.size(); i++) {
        if (i % 20 == 0) ofLog() << " - encoding image "<<i<<" / "<<images.size();
        vector<float> encoding = ccv.encode(images[i], ccv.numLayers()-1);
        encodings.push_back(encoding);
    }
    
    // run t-SNE and load image points to imagePoints
    ofLog() << "Run t-SNE on images";
    tsneVecs = tsne.run(encodings, 2, perplexity, theta, true);
    // tsneVecs contains {x, y} for each image in images
    
    // save tsne
    ofFile tsneFile;
    tsneFile.open(folderName + "/" + "tsne_only_metadata.csv", ofFile::WriteOnly);
    tsneFile << "image_name,tsne_x,tsne_y";
    for (int i = 0; i < images.size(); i++) {
        tsneFile << "\n";
        tsneFile << imageFiles[i].getFileName() << ",";
        tsneFile << ofToString(tsneVecs[i][0]) << ",";
        tsneFile << ofToString(tsneVecs[i][1]);
    }
    tsneFile.close();
    
    ofExit(); // TEMP!!!
    
    // solve assignment grid
    vector<ofVec2f> tsnePoints; // convert vector<double> to ofVec2f
    for (auto t : tsneVecs) tsnePoints.push_back(ofVec2f(t[0], t[1]));
    vector<ofVec2f> gridPoints = makeGrid(nx, ny);
    solvedGrid = solver.match(tsnePoints, gridPoints, false);
    
    // export data to csv containing names and positions of images
    bool bExport = true;
    if (bExport) {
        int nImages = images.size(); //nx * ny;
        ofFile file;
        file.open(folderName + "/" + "tsne_metadata.csv", ofFile::WriteOnly);
        file << "image_name,grid_row,grid_column,grid_x_norm,grid_y_norm,tsne_x,tsne_y";
        for (int i = 0; i < nImages; i++) {
            file << "\n";
            file << imageFiles[i].getFileName() << ",";
            file << ofToString(solvedGrid[i].x * (nx-1)) << ",";
            file << ofToString(solvedGrid[i].y * (ny-1)) << ",";
            file << ofToString(solvedGrid[i].x) << ",";
            file << ofToString(solvedGrid[i].y) << ",";
            file << ofToString(tsneVecs[i][0]) << ",";
            file << ofToString(tsneVecs[i][1]);
        }
        file.close();
    }
    
    // save image grid
    bool bSaveGrid = true;
    if (bSaveGrid) {
        string imageGridName = "tsne_grid.png";
        ofFbo fbo;
        fbo.allocate(nx * w, ny * h);
        fbo.begin();
        ofClear(0, 0);
        ofBackground(0);
        for (int i=0; i<solvedGrid.size(); i++) {
            float x = (fbo.getWidth() - w) * solvedGrid[i].x;
            float y = (fbo.getHeight() - h) * solvedGrid[i].y;
            images[i].draw(x, y, w, h);
        }
        fbo.end();
        ofImage img;
        fbo.readToPixels(img);
        img.save(folderName + "/" + imageGridName);
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
        for (int i=0; i<tsneVecs.size(); i++) {
            float x = (fbo.getWidth() - w) * tsneVecs[i][0];
            float y = (fbo.getHeight() - h) * tsneVecs[i][1];
            ofSetColor(255, 180);
            images[i].draw(x, y, w * imgScale, h * imgScale);
            ofSetColor(0);
            ofDrawBitmapString(imageFiles[i].getFileName(), x, y + h * imgScale);
        }
        fbo.end();
        ofImage img;
        fbo.readToPixels(img);
        img.save(folderName + "/" + imageClustersName);
    }
    
    // setup gui
    gui.setup();
    gui.add(scale.set("scale", 1.0, 0.0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofPushMatrix();
    ofTranslate(-ofGetMouseX() * (scale - 0.5), -ofGetMouseY() * (scale - 0.5));
    for (int i=0; i<solvedGrid.size(); i++) {
        float x = scale * (nx - 1) * w * solvedGrid[i].x;
        float y = scale * (ny - 1) * h * solvedGrid[i].y;
        images[i].draw(x, y, scale * images[i].getWidth(), scale * images[i].getHeight());
    }
    ofPopMatrix();
    
    gui.draw();
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
