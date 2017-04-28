#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	int num = 1500;
	p.assign(num, demoParticle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to brightest point";

	resetParticles();
	cam.initGrabber(640, 480);
    
    // db fork april 2017
    showCamera = true;
    showGui =true;
    gui.setup( "Parameters", "settings.xml" );  //-- gui setup
    gui.add( blobSize.setup( "blobSize", 4.0, 1.0, 20.0 ) );
    //gui.add( blobSpeed.setup( "blobSpeed", 20, 1, 200 ) );
    //gui.add( blobAmount.setup( "blobAmount", 200, 10, 2000 ) );
    gui.add(blobFill.setup( "filled", true));
    gui.add( blobColor.setup( "color",
                                                                ofColor::black,
                                                               ofColor(0,0,0,0),
                                                              ofColor::white));
    
    gui.loadFromFile("settings.xml"); //save presets we like to xml data file
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the forth demo
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
	}

	attractPointsWithMovement = attractPoints;

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update(){

	int w = cam.getWidth();
	int h = cam.getHeight();

	maxBrightness  = 0;
	oldMaxBrightness  = 0;

	maxBrightnessX = 0;
	maxBrightnessY = 0;

	for (int y=0; y<h; y++) {
		for(int x=0; x<w; x++) {
			ofColor colorAtXY = cam.getPixels().getColor(x, y);
			float brightnessOfColorAtXY = colorAtXY.getBrightness();
			if (brightnessOfColorAtXY > maxBrightness){
				maxBrightness = brightnessOfColorAtXY;
				maxBrightnessX = x;
				maxBrightnessY = y;
			}
		}
	}

    ofLog(OF_LOG_NOTICE, "%f %f", maxBrightness, oldMaxBrightness);


	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].setXY(maxBrightnessX, maxBrightnessY);
		p[i].update();
	}

	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}

	cam.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

 //   ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	if (showCamera)cam.draw(0, 0);

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw(blobSize, blobColor, blobFill);
	}

	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	ofNoFill();
    ofDrawCircle(maxBrightnessX, maxBrightnessY, 10);
    ofFill();
    ofDrawCircle(maxBrightnessX, maxBrightnessY, 4);
    
    if (showGui) {
        ofSetColor(230);
        ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	}
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
	}
	if( key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force";
	}
	if( key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
	}

	if( key == ' ' ){
		resetParticles();
	}
    if (key=='c'){
        showCamera=!showCamera;
    }
    
    if (key=='g'){
        showGui=!showGui;
    }
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
