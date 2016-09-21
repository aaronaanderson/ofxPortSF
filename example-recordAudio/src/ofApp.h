#pragma once

#include "ofMain.h"
#include "ofxPortSF.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void exit();
	void audioOut(float *buffer, int bufferSize, int nChannels);

	PSF_PROPS props;//store sound file properties
	int ofd = -1;//to keep track if opened, and what error if not I think (could be wrong)
	psf_format outputFormat = PSF_FMT_UNKNOWN;//this should be changed if file extension is accepted
	float* frame = NULL;//create variable space for audio frame, sized later
	bool currentlyRecording;//for on/off toggle

	float phase;//for sine osc

};
