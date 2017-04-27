#pragma once

#include "ofMain.h"
#include "demoParticle.h"
#include "ofxGui.h"

extern const float blobSize;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		particleMode currentMode;
		string currentModeStr;

		vector <demoParticle> p;
		vector <ofPoint> attractPoints;
		vector <ofPoint> attractPointsWithMovement;

		ofVideoGrabber cam;

		int   maxBrightnessX;
		int   maxBrightnessY;
        float maxBrightness;
        float oldMaxBrightness;
    
    // db fork apr 2017
    bool showCamera;
    bool showGui;
    
    ofxPanel gui;
     ofxFloatSlider blobSize;
    ofxIntSlider blobAmount;
    ofxIntSlider blobSpeed;
    ofxColorSlider blobColor;
    

};
