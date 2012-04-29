#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <FL/gl.h>
#include <vector>
#include "force.h"
#include "modelerdraw.h"

class Particle {
public:
	Particle(Vec3<float> p, float m) : pos(p), mass(m) {}

	void setPos(Vec3<float> p) {
		pos = p;
	}

	void setSpeed(Vec3<float> s) {
		speed = s;
	}

	Vec3<float> getPos() const {
		return pos;
	}

	Vec3<float> getSpeed() const {
		return speed;
	}

	void addForce(Force* f);
	void move(float deltaT);
	void draw(GLuint texture);

private:
	float mass;
	Vec3<float> pos;
	Vec3<float> speed;
	vector<Force*> forces;
};

#endif