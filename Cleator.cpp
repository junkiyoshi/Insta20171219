#include "Cleator.h"

Cleator::Cleator(){
	this->location = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
	this->velocity = ofVec3f(0, 0, 0);
	this->acceleration = ofVec3f(0, 0, 0);

	this->max_speed = 8;
	this->max_force = 3;
	this->radius = 30;
	this->angle = ofRandom(360);
	this->angle_2 = ofRandom(180);
}

Cleator::~Cleator(){

}

void Cleator::applyForce(ofVec3f force){
	this->acceleration += force;
}

void Cleator::seek(ofVec3f target){
	ofVec3f desired = this->location - target;
	float distance = desired.length();
	desired.normalize();
	if (distance < this->radius)
	{
		float m = ofMap(distance, 0, this->radius, 0, this->max_speed);
		desired *= m;
	}
	else
	{
		desired *= this->max_speed;
	}

	ofVec3f steer = this->velocity - desired;
	steer.limit(this->max_force);
	applyForce(steer);
}

void Cleator::update(){
	this->future.set(this->velocity);
	this->future.normalize();
	this->future *= 30;
	this->future += this->location;

	this->angle = ofRandom(0, 360);
	this->angle_2 = ofRandom(0, 180);
	float x = 30 * cos(this->angle * DEG_TO_RAD) * sin(this->angle_2 * DEG_TO_RAD) + future.x;
	float y = 30 * sin(this->angle * DEG_TO_RAD) * sin(this->angle_2 * DEG_TO_RAD) + future.y;
	float z = 30 * cos(this->angle_2 * DEG_TO_RAD) + future.z;
	this->target = ofVec3f(x, y, z);

	this->seek(this->target);

	this->velocity += this->acceleration;
	this->velocity.limit(max_speed);
	this->location += this->velocity;

	if (this->location.x < -ofGetWidth() / 2) {
		this->location.x = -ofGetWidth() / 2;
		this->velocity.x *= -1;
	}
	else if (this->location.x > ofGetWidth() / 2) {
		this->location.x = ofGetWidth() / 2;
		this->velocity.x *= -1;
	}

	if (this->location.y < -ofGetHeight() / 2) {
		this->location.y = -ofGetHeight() / 2;
		this->velocity.y *= -1;
	}
	else if (this->location.y > ofGetHeight() / 2) {
		this->location.y = ofGetHeight() / 2;
		this->velocity.y *= -1;
	}

	if (this->location.z < -360) {
		this->location.z = -360;
		this->velocity.z *= -1;
	}else if(this->location.z > 360) {
		this->location.z = 360;
		this->velocity.z *= -1;
	}

	this->acceleration *= 0;
	this->velocity *= 0.98;

}

void Cleator::draw(){

}

ofVec3f Cleator::get_location() {
	return this->location;
}

ofVec3f Cleator::get_velocity() {
	return this->velocity;
}