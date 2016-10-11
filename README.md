# ofxPortSF
ofxPortSF is an addon to aid in loading, recording, and saving sound
files for projects that implement an audio stream explicitly. It 
uses Richard Dobson's portsf C library, written for use with "The 
Audio Programming Book" (which I highly recommend!). The addon was 
made for the sole purpose of making the task easier for openFrameworks 
programmers with little background in C. The three example projects 
should be enough to copy-paste into your own projects with very few
changes. 

Tested on Windows and MacOS, should work on Linux.

<h2>Install:</h2>


• Place the ofxPortSF folder in your addons folder: of_currentVersion_relase > addons > ofxPortSF

<h2>Accepted Audio File Extensions:</h2>
.wav, .aif, .aiff, .aifc

Note: the library does not support compressed audio formats (most notably the .mp3).

<h2>Notes from the original author:</h2>

portsf from the audio programming book

Copyright (c) 2009,2010 Richard Dobson

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

