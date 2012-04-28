#include "particle.h"

void Particle::addForce(Force* f) {
	forces.push_back(f);
}

void Particle::move(float deltaT) {
	vector<Force*>::iterator iter;
	for (iter = forces.begin(); iter != forces.end(); iter++) {
		(*iter)->applyTo(speed, deltaT);
	}
	pos += speed * deltaT;
}

void Particle::draw() {
	setDiffuseColor(1, 1, 1);
	glPushMatrix();
		glBegin(GL_POINTS);
		glVertex3f(pos[0], pos[1], pos[2]);
		glEnd();
	glPopMatrix();
}