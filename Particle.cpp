#include "Particle.h"

Particle::Particle() : Particle(ofVec3f(0, 0), ofVec3f(0, 0)) { }

Particle::Particle(ofVec3f location, ofVec3f velocity){
	this->location = location;
	this->velocity = velocity;
	this->alpha = 255;
	this->body_size = velocity.length() / 2;
	this->body_color.setHsb(ofRandom(255), 255, 255);
}

Particle::Particle(ofVec3f location, ofVec3f velocity, ofColor body_color)
{
	this->location = location;
	this->velocity = velocity;
	this->alpha = 255;
	this->body_size = velocity.length() / 2;
	this->body_color = body_color;
}

Particle::~Particle() { }

void Particle::update(){
	this->location += this->velocity;
	this->alpha -= 3;
}

void Particle::draw(){
	ofSetColor(this->body_color, this->alpha);
	ofDrawSphere(this->location, this->body_size);
}

ofVec3f Particle::get_location(){
	return this->location;
}

bool Particle::isDead(){
	return this->alpha < 0;
}