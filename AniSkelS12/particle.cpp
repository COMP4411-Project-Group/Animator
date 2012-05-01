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

void Particle::draw(Vec3f viewDir) {
	setDiffuseColor(1, 1, 1);
	glPushMatrix();

		glBegin(GL_POINTS);
		glVertex3f(pos[0], pos[1], pos[2]);
		glEnd();

		/*
		glTranslated(pos[0], pos[1], pos[2]);
		glRotated(viewDir[0] * 57.3, 0, 1, 0);
		glRotated(viewDir[1] * 57.3, 0, 0, 1);
		glRotated(viewDir[2] * 57.3, 1, 0, 0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 2);
		glBegin(GL_QUADS);

		glTexCoord2f (0.0, 0.0);
		glVertex3f (0.0, 0.0, 0.0);

		glTexCoord2f (1.0, 0.0);
		glVertex3f (0.0, 0.1, 0.0);

		glTexCoord2f (1.0, 1.0);
		glVertex3f (0.0, 0.1, 0.1);

		glTexCoord2f (0.0, 1.0);
		glVertex3f (0.0, 0.0, 0.1);

		glEnd();
		*/

	glPopMatrix();
}