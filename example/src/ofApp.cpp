#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetFrameRate(60);
	
	double frequency = 60 ; // Hz
	double mincutoff = 1.0 ; // FIXME
	double beta = 1.0 ;      // FIXME
	double dcutoff = 1.0 ;   // this one should be ok

	
	filter.setup(frequency, mincutoff, beta, dcutoff);
	
	rawArray.assign(ofGetWidth(), 0.0);
	filterArray.assign(ofGetWidth(), 0.0);
}

//--------------------------------------------------------------
void ofApp::update(){

	float v = (float)mouseY / (float)ofGetHeight();
	float fv = filter.filter(v, ofGetElapsedTimef());
	
	rawArray.pop_front();
	rawArray.push_back(v);
	
	filterArray.pop_front();
	filterArray.push_back(fv);
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofNoFill();
	
	ofSetLineWidth(2);
	
	// draw raw
	ofSetColor(245, 58, 135);
	ofBeginShape();
	for (unsigned int i = 0; i < rawArray.size(); i++){
		float x =  ofMap(i, 0, rawArray.size(), 0, ofGetWidth(), true);
		ofVertex(x, rawArray[i] * ofGetHeight() );
	}
	ofEndShape(false);

	
	// draw filtered
	ofSetColor(58, 245, 135);
	ofBeginShape();
	for (unsigned int i = 0; i < filterArray.size(); i++){
		float x =  ofMap(i, 0, filterArray.size(), 0, ofGetWidth(), true);
		ofVertex(x, filterArray[i] * ofGetHeight() );
	}
	ofEndShape(false);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

	// adjust queues
	filterArray.resize(w);
	rawArray.resize(w);
	
	ofShowCursor();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
