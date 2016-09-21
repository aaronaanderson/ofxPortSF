#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {


	if (psf_init()) {//initialize the portSF library
		cout << "unable to initalize port sound file ):" << endl;//warn if initialization fails
	}

	//load an audio file so that we have something to save

	string path = ofToDataPath("Microbial_Surfaces.wav");//store path to pre-include sound file
	const char *filePath = path.c_str();// convert from fancy string to C string

	ifd = psf_sndOpen(filePath, &soundFileProperties, 0);//open the sound file

	if (ifd < 0) {//this can happen if the file does not exist or the format is not supported
		ofSystemAlertDialog("Error loading file");
	}
	else {
		frame = (float*)malloc(soundFileProperties.chans * sizeof(float));//set the size of frame to be the nSamples per Frame
		framesRead = psf_sndReadFloatFrames(ifd, frame, 1);//grab the first frame
		totalFramesRead = 0;
		while (framesRead == 1) {//while there are still frames to be read
			totalFramesRead++;//keep track of number of frames;
			for (int i = 0; i < soundFileProperties.chans; i++) {//for every sample in the frame
				soundFile.push_back(frame[i]);//add frame to the soundFile vector
			}
			framesRead = psf_sndReadFloatFrames(ifd, frame, 1);//returns 1 if there are still more frames
		}//finished loading sound
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(50);
	ofDrawBitmapString("press spacebar to save sound", 20, 20);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {//if spacebar pressed

		ofFileDialogResult saveFileResult = ofSystemSaveDialog("defaultName.wav", ".wav or .aif");
		string path = saveFileResult.getPath();// store path
		const char *filePath = path.c_str();// convert from fancy string to C string

		outputFormat = psf_getFormatExt(filePath);//grab the output format


		switch (outputFormat) {//error check
		case PSF_FMT_UNKNOWN://unknown format or no format given
			ofSystemAlertDialog("Not a recognized format, try .wav or .aif");
			break;//give up
		default:
			soundFileProperties.format = outputFormat;//set the given format to the write format
			ofd = psf_sndCreate(filePath, &soundFileProperties, 0, 1, PSF_CREATE_RDWR);//create sound file of specified type

			for (int i = 0; i < totalFramesRead; i++) {//for every frame of audio 
				for (int j = 0; j < soundFileProperties.chans; j++) {//for every sample in frame
					int index = i * soundFileProperties.chans + j;
					frame[j] = soundFile[index];//fill the frame
				}
				psf_sndWriteFloatFrames(ofd, frame, 1);//pass the frame to the output file
			}
			psf_sndClose(ofd);//close file when finished
		}
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofSoundStreamClose();
	psf_finish();//safety. will close sound files on exit
}
