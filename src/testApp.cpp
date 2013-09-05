#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);
	mode = 1;
	xA=0;
	yA=0;
	zA=0;
	xM=0;
	yM=0;
	zM=0;
	receiver.setup(2234);
	box = ofBoxPrimitive(2,4,0.2f);
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
			float newX = m.getArgAsFloat(0) * 180.0f / PI;
			float newY = m.getArgAsFloat(1) * 180.0f / PI;
			float newZ = m.getArgAsFloat(2) * 180.0f / PI;
			xA = newX;
			yA = newY;
			zA = newZ;
			//ofQuaternion qAt( -yA, ofVec3f(1,0,0), 0, ofVec3f(0,1,0), 0, ofVec3f(0,0,1));
			//ofQuaternion qAt( 0, ofVec3f(1,0,0), zA, ofVec3f(0,1,0), 0, ofVec3f(0,0,1));
			//ofQuaternion qAt( -yA, ofVec3f(1,0,0), zA, ofVec3f(0,1,0), 0, ofVec3f(0,0,1));
			ofQuaternion qAt( -yA, ofVec3f(1,0,0), zA, ofVec3f(0,1,0), -xA, ofVec3f(0,0,1));
			qA.slerp( 1-smooth, qA, qAt);
		} else if(m.getAddress() == "/data/quaternion/A"){
			ofQuaternion qAt(m.getArgAsFloat(0), m.getArgAsFloat(3), -1*m.getArgAsFloat(2), -1*m.getArgAsFloat(1));
			qA.slerp( 1-smooth, qA, qAt);
		} else if(m.getAddress() == "/data/quaternion/M"){
			ofQuaternion qMt(m.getArgAsFloat(0), m.getArgAsFloat(3), -1*m.getArgAsFloat(2), -1*m.getArgAsFloat(1));
			qM = qMt;
		} else if(m.getAddress() == "/data/angles/M"){
			float newX = m.getArgAsFloat(0) * 180.0f / PI;
			float newY = m.getArgAsFloat(1) * 180.0f / PI;
			float newZ = m.getArgAsFloat(2) * 180.0f / PI;
			xM = newX;
			yM = newY;
			zM = newZ;
		}  
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255,255,255);
	
	cam.begin();
	if (mode == 0){
		box.setOrientation(qA);
	} else {
		box.setOrientation(qM);
	}
	box.draw();

	cam.end();
	string buf;
	buf = "A  |  X: " + ofToString(xA) + " Y: " + ofToString(yA) + " Z: " + ofToString(zA);
	ofDrawBitmapString(buf, 20, 20);
	buf = "M  |  X: " + ofToString(xM) + " Y: " + ofToString(yM) + " Z: " + ofToString(zM);
	ofDrawBitmapString(buf, 20, 40);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if (key == 'm'){
		mode = 1;
	} else if (key == 'a'){
		mode = 0;
	}

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
