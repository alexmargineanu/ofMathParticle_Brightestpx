#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE
};

class demoParticle{

	public:
		demoParticle();

		void setMode(particleMode newMode);
		void setXY(int newX, int newY);
		void setAttractPoints( vector <ofPoint> * attract );

		void reset();
		void update();
		void draw();

		ofPoint pos;
		ofPoint vel;
		ofPoint frc;

		float drag;
		float uniqueVal;
		float scale;

		particleMode mode;
		int myX;
		int myY;

		vector <ofPoint> * attractPoints;
    

    
    int blobAmount;
    int blobSpeed;
};
