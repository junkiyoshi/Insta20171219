#pragma once
#include "ofMain.h"

class Cleator
{
public:
	Cleator();
	~Cleator();

	void applyForce(ofVec3f force);
	void seek(ofVec3f target);

	void update();
	void draw();

	ofVec3f get_location();
	ofVec3f get_velocity();

private:
	ofVec3f location;
	ofVec3f velocity;
	ofVec3f acceleration;
	ofVec3f future;
	ofVec3f target;
	float max_speed;
	float max_force;
	float radius;
	float angle;
	float angle_2;
};