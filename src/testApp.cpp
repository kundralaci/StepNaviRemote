#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);
	x=0;
	y=0;
	z=0;
	receiver.setup(2234);
	box = ofMesh::box(2.0f,4.0f,0.2f);
	cam.setPosition(ofVec3f(0,0,5));
	light.enable();
	light.setDirectional();
	light.setPosition(0,0,5);
	ofFloatColor color(1.0f,0.7f,0.3f,1.0f);
	light.setAmbientColor(color);
	light.setSpecularColor(color);
	light.setDiffuseColor(color);
}

//--------------------------------------------------------------
void testApp::update(){
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		// check for mouse moved message
		if(m.getAddress() == "/data/angles/A"){
			// both the arguments are int32's
			x = m.getArgAsInt32(0);
			y = m.getArgAsInt32(1);
			z = m.getArgAsInt32(2);
		} 
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255,255,255);
	cam.begin();
	ofPushStyle();
	ofRotateX(-y);
	ofRotateY(z);
	ofRotateZ(x);
	box.draw();
	ofPopStyle();
	cam.end();
	string buf;
	buf = "X: " + ofToString(x) + " Y: " + ofToString(y) + " Z: " + ofToString(z);
	ofDrawBitmapString(buf, 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
