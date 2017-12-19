#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle();
	Particle(ofVec3f location, ofVec3f velocity);
	Particle(ofVec3f location, ofVec3f velocity, ofColor body_color);
	~Particle();

	void update();
	void draw();

	ofVec3f get_location();
	bool isDead();
private:
	ofVec3f location;
	ofVec3f velocity;

	float	body_size;
	ofColor body_color;
	int		alpha;
};