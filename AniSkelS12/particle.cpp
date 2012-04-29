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

void Particle::draw(GLuint texture) {
	setDiffuseColor(1, 1, 1);
	glPushMatrix();

		glBegin(GL_POINTS);
		glVertex3f(pos[0], pos[1], pos[2]);
		glEnd();
		/*
		glTranslated(pos[0], pos[1], pos[2]);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 1);
		glBegin(GL_QUADS);

		glTexCoord2f (0.0, 0.0);
		glVertex3f (0.0, 0.0, 0.0);

		glTexCoord2f (1.0, 0.0);
		glVertex3f (1.0, 0.0, 0.0);

		glTexCoord2f (1.0, 1.0);
		glVertex3f (1.0, 1.0, 0.0);

		glTexCoord2f (0.0, 1.0);
		glVertex3f (0.0, 1.0, 0.0);

		glEnd ();
		*/

	glPopMatrix();
}