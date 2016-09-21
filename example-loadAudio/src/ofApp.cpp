#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {


	if (psf_init()) {//initialize the portSF library
		cout << "unable to initalize port sound file ):" << endl;//warn if initialization fails
	}

	playSound = false;//dont try to play until sound is loaded
	playIndex = 0;//start sound from beginning 

	//start audio thread
	ofSoundStreamSetup(6, 0, 48000, 512, 6);//5.1
	//ofSoundStreamSetup(2, 0, 48000, 512, 4);//stereo

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(50);
	ofDrawBitmapString("press spacebar to load sound", 20, 20);
	ofDrawBitmapString("sound will start playing once loaded", 20, 40);

}
//--------------------------------------------------------------
void ofApp::audioOut(float *buffer, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {

		/*sound file player that can adapt to number of channels in audio file
		this ignores sample rate. If the sample rate of the file is different than the sample rate of your DAC, 
		playback will be at the wrong speed. This is just to demonsrate.
		Also, this will crash if you attempt to play a soundfile with more channels than your playback.*/
		if (playSound) {
			for (int j = 0; j < soundFileProperties.chans; j++) {//for every sample in a frame (2 if stereo, for example)
				buffer[i*nChannels + j] = soundFile[playIndex + j] * 0.1;//interleave samples into audio buffer
			}

			playIndex += soundFileProperties.chans;//skip ahead one frame
			if (playIndex >= totalFramesRead) {//if sound file is finished,
				playIndex = 0;//start over
			}
		}//end of sound player

	}//end of audio buffer loop
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {

		ofFileDialogResult loadFileResult = ofSystemLoadDialog();//open the load dialog
		string path = loadFileResult.getPath();//store the string
		const char *filePath = path.c_str();// convert from fancy string to C string

		ifd = psf_sndOpen(filePath, &soundFileProperties, 0);//open the sound file

		if (ifd < 0) {//this can happen if the file does not exist or the format is not supported
			ofSystemAlertDialog("Error loading file");
		}
		else {
			frame = (float*)malloc(soundFileProperties.chans * sizeof(float));//set the size of frame to be the nSamples per Frame
			framesRead = psf_sndReadFloatFrames(ifd, frame, 1);//grab the first frame
			totalFramesRead = 0;
			soundFile.clear();//clear the vector that the soundFile will be stored in
			while (framesRead == 1) {//while there are still frames to be read
				totalFramesRead++;//keep track of number of frames;
				for (int i = 0; i < soundFileProperties.chans; i++) {//for every sample in the frame
					soundFile.push_back(frame[i]);//add frame to the soundFile vector
				}
				framesRead = psf_sndReadFloatFrames(ifd, frame, 1);//returns 1 if there are still more frames
				//cout << framesRead << " " << endl;
			}
			playIndex = 0;//start sound from beginning
			playSound = true;//start playing the sound once loaded
		}
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofSoundStreamClose();
	psf_finish();//safety. will close sound files on exit
}
