/**
 * ofxTimecode
 * James George 2012
 *
 * Created as part of the Duration + ofxTimeline project
 * Supported by YCAM InterLab Guest Research Project ( http://interlab.ycam.jp/en/ )
 *
 */

#include "ofxTimecode.h"

ofxTimecode::ofxTimecode(){
    fps = 30;
}
    
void ofxTimecode::setFPS(float _fps){
    if(fps < 1){
        ofLogError("ofxTimecode::setFPS invalid FPS set");
        return;
    }
	fps = _fps;
}

float ofxTimecode::getFPS(){
    return fps;
}
    
//expects format HH:MM:SS:FR
long ofxTimecode::millisForTimecode(string timecode){
    return millisForFrame(frameForTimecode(timecode));
}

//expects format HH:MM:SS:FR
float ofxTimecode::secondsForTimecode(string timecode){
    return secondsForFrame(frameForTimecode(timecode));
}

int ofxTimecode::frameForSeconds(float timeInSeconds){
    return timeInSeconds * fps;
}

int ofxTimecode::frameForMillis(long timeInMillis){
    return timeInMillis * fps / 1000;
}

float ofxTimecode::secondsForFrame(int frame){
	return frame / fps;
}

long ofxTimecode::millisForFrame(int frame){
	return frame * 1000 / fps;    
}

int ofxTimecode::frameForTimecode(string timecode){
    int times[4];
    if(decodeString(timecode, times)){
            	//hours					  //minutes				//seconds		 //frames
        return times[0] * fps * 60 * 60 + times[1] * fps * 60 + times[2] * fps + times[3];
    }
    return -1;
}

string ofxTimecode::timecodeForMillis(long millis){
    return timecodeForFrame(millis * fps / 1000 );
}

string ofxTimecode::timecodeForSeconds(float seconds){
    return timecodeForFrame(seconds * fps);
}
    
string ofxTimecode::timecodeForFrame(int frame){
	char buf[512];
    sprintf(buf, "%02d:%02d:%02d:%d", int(frame / (60 * 60 * fps)), int(frame / (60 * fps)) % 60, int(frame / fps) % 60, frame % int(fps) );
    return string(buf);
}

bool ofxTimecode::decodeString(string time, int* times){
    vector<string> split = ofSplitString(time, ":");
    if(split.size() != 4){
        ofLogError("ofxTimecode::decodeString -- incorrect timecode");
        return false;
    }
    for(int i = 0; i < split.size(); i++){
    	times[i] = ofToInt(split[i]);
    }
    return true;
}
