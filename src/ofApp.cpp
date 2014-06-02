#include "ofApp.h"


#define AUIDO_THRESHOLD 0.8

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofBackground(0, 0, 34);
	ofSetVerticalSync(false);
	ofEnableAlphaBlending();
    
    shader.load("shader");
    
    loader.loadModel("shpere.dae");
    doShader = true;
    
    
    
    
    
    //for Audio
	soundStream.listDevices();
	int bufferSize = 256;
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    currentVol = 0.0;
    oldVol = 0.0;
    
    
    //Initialize Parameter
    amplitude = 1.0;
    audioFlag = false;
    audioMax = 0.1;
    audioThreshold = .9;
    
    loader.setRotation(1, 90, 1, 0, 0);
    loader.setScale(1.2,1.2,1.2);
    
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    oldVol = scaledVol;
    
	scaledVol = ofMap(smoothedVol, 0.0, audioMax, 0.0, 1.0, true);
    audioFlag = (scaledVol > audioThreshold) && (oldVol < AUIDO_THRESHOLD);
    
//    loader.get
//    cout << scaledVol << " : " << audioFlag << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(225);
	ofDrawBitmapString("'s' toggles shader", 10, 20);
    
	ofSetColor(245, 58, 135);
	ofFill();
    
    if(doShader){
        shader.begin();
        shader.setUniform2f("mouse", mouseX, mouseY ); // setting mouse coordinate.
        shader.setUniform1f("soundVolume", scaledVol);
        shader.setUniform1i("time", ofGetElapsedTimeMillis());
    }
//    ofRect(0.0, ofGetHeight() * 0.5 , ofGetWidth(), ofGetHeight());
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    ofSetColor(255, 255, 255, 255);
    loader.drawWireframe();
//    loader.get
//    loader.drawFaces();
    loader.drawVertices();
    ofPopMatrix();
    if(doShader){
        shader.end();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if( key == 's' ){
        doShader = !doShader;
    }else if(key == 'f'){
        ofToggleFullscreen();
    }else if(key == 'r'){
        shader.unload();
        shader.load("shader");
    }
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	float curVol = 0.0;
	// samples are "interleaved"
	int numCounted = 0;
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	smoothedVol *= 0.5;
	smoothedVol += 0.5 * curVol;
	bufferCounter++;
}
