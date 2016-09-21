#pragma once

#include "ofMain.h"
#include "ofxPortSF.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void exit();//you should add this to your projects that use this library
	void audioOut(float *buffer, int bufferSize, int nChannels);//audio thread

	//Used for loading sound
	PSF_PROPS soundFileProperties;//will be auto-populated when file loaded
	long framesRead, totalFramesRead;//framesread used to check if there are still more frames in file
	int ifd = -1;//identification for the sound file, used by the library
	float* frame = NULL;//location of currently read frame
	vector<float> soundFile;//actual stored sound file

	//used for playing sound
	bool playSound;//on/off toggle
	unsigned int playIndex;//location of needle head

};
