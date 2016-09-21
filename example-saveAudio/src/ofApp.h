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

	psf_format outputFormat = PSF_FMT_UNKNOWN;//the format of the file being saved, determined by user
	PSF_PROPS soundFileProperties;//will be auto-populated
	long framesRead, totalFramesRead; //framesread is a condition used to load the file, checking for frames. 
	int ifd = -1;//identification for the sound file, used by the library
	int ofd = -1;//output file id
	float* frame = NULL;//location of currently read frame
	vector<float> soundFile;//actual stored sound file

};
