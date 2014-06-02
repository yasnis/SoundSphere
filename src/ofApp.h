#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofShader shader;
    bool doShader;
    
    ofxAssimpModelLoader loader;
    
    
    
    
    
    //for MirrorBall
    int type;
    float value1;
    float value2;
    ofVec2f value3;
    float amplitude;
    bool audioFlag;
    float audioThreshold;
    float audioMax;
    
    
    //for Audio
    void audioIn(float * input, int bufferSize, int nChannels);
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    int 	bufferCounter;
    int 	drawCounter;
    float smoothedVol;
    float scaledVol;
    ofSoundStream soundStream;
    float currentVol;
    float oldVol;
};
