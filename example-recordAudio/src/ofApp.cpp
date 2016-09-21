#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {


	if (psf_init()) {//initialize portSF
		cout << "unable to initalize port sound file ):" << endl;//warn if initialization failed
	}

	props.chans = 1;// monophonic 
	props.samptype = PSF_SAMP_32;// 32 bits
	props.srate = 48000;//Sampling rate of recording


	currentlyRecording = false;// 

	phase = 0;//for oscillator
	//ofSoundStreamSetup(6, 0, 48000, 512, 6);//setup sound stream (if you have a 5.1 system
	ofSoundStreamSetup(2, 0, 48000, 512, 4);//setup for stereo system
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(50);
	ofDrawBitmapString("Press spacebar to start recording", 20, 20);
	ofDrawBitmapString("Press 's' to stop recording", 20, 40);

}
//--------------------------------------------------------------
void ofApp::audioOut(float *buffer, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {

		float currentSample = 0;


		//simple sine wave oscillator for testing
		currentSample = sin(phase*TWO_PI);
		if (phase >= 1.0) phase -= 1.0;
		phase += (1. / (48000 / 440));


		currentSample *= 0.1;//play it safe


		if (currentlyRecording) {
			psf_sndWriteFloatFrames(ofd, &currentSample, 1);//add the current sample to the current recording
		}

		buffer[i*nChannels] = currentSample;//left channel out
		buffer[i * nChannels + 1] = currentSample;// right channel out
	}

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {

		ofFileDialogResult saveFileResult = ofSystemSaveDialog("defaultName.wav", ".wav or .aif");
		string path = saveFileResult.getPath();// store path
		const char *filePath = path.c_str();// convert from fancy string to C string

		outputFormat = psf_getFormatExt(filePath);//grab the output format


		switch (outputFormat) {
		case PSF_FMT_UNKNOWN://unknown format or no format given
			ofSystemAlertDialog("Not a recognized format, try .wav or .aif");
			break;//give up
		default:
			props.format = outputFormat;//set the given format to the write format
			ofd = psf_sndCreate(filePath, &props, 0, 1, PSF_CREATE_RDWR);//create sound file of specified type
			currentlyRecording = true;//start writing data
		}

	}
	else if (key == 's') {
		currentlyRecording = false;//stop data from being written
		psf_sndClose(ofd);//close sound file
	}

}

//--------------------------------------------------------------
void ofApp::exit() {
	ofSoundStreamClose();
	psf_finish();//safety mechanism. closes all sound files.
}
