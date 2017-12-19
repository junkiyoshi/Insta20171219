#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
	for (int i = this->particles.size() - 1; i > -1; i--) {
		delete this->particles[i];
		this->particles.erase(this->particles.begin() + i);
	}

	for (int i = this->cleators.size() - 1; i > -1; i--) {
		delete this->cleators[i];
		this->cleators.erase(this->cleators.begin() + i);
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofNoFill();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	for (int i = 0; i < 12; i++) {
		this->cleators.push_back(new Cleator());
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < this->cleators.size(); i++) {
		ofVec3f location = this->cleators[i]->get_location();
		ofVec3f velocity = this->cleators[i]->get_velocity();
		
		if (velocity.length() > 5) {
			this->particles.push_back(new Particle(location, velocity * 0.3));
		}
	}

	for (int i = this->particles.size() - 1; i > -1; i--) {
		this->particles[i]->update();

		if (this->particles[i]->isDead()) {
			delete this->particles[i];
			this->particles.erase(this->particles.begin() + i);
		}
	}

	for (int i = 0; i < this->cleators.size(); i++) {
		this->cleators[i]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	ofSetColor(255, 128);
	ofDrawBox(720);

	float distance;
	for (int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->draw();
		for (int j = i; j < this->particles.size(); j++) {
			distance = this->particles[i]->get_location().distance(this->particles[j]->get_location());
			if (distance < 80) {
				ofDrawLine(this->particles[i]->get_location(), this->particles[j]->get_location());
			}
		}
	}

	for (int i = 0; i < this->cleators.size(); i++) {
		this->cleators[i]->draw();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}