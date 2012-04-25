#pragma warning(disable : 4786)

#include "particleSystem.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <ctime>


/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() 
{
	srand(time(0));

	Gravity* g = new Gravity(Vec3<float>(0, -0.001, 0));
	Friction* f = new Friction(0.01);

	forces.push_back(g);
	forces.push_back(f);
}




/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	particles.clear();
	forces.clear();
}


/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
    
	// TODO

	// These values are used by the UI ...
	// -ve bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	bake_end_time = -1;
	simulate = true;
	dirty = true;

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
	if (simulate) {
		vector<Particle*>::iterator iter;
		for (iter = particles.begin(); iter != particles.end(); iter++) {
			(*iter)->move();
		}
	}
}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	if (simulate) {
		vector<Particle*>::iterator iter;
		for (iter = particles.begin(); iter != particles.end(); iter++) {
			(*iter)->draw();
		}
	}
}





/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{

	// TODO
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{

	// TODO
}

void ParticleSystem::addParticlesAt(Vec3<float> pos, int num) {
	for (int i = 0; i < num; i++) {
		Particle* p = new Particle(Vec3<float>(pos[0], pos[1], pos[2]), 1);
	
		float xSpeed = rand() % 10 / 100.0 + 0.1;
		float zSpeed = rand() % 10 / 100.0 - 0.05;
		float ySpeed = rand() % 10 / 100.0 - 0.05;
		p->setSpeed(Vec3<float>(xSpeed, ySpeed, zSpeed));
	
		vector<Force*>::iterator iter;
		for (iter = forces.begin(); iter != forces.end(); iter++) {
			p->addForce(*iter);
		}
	
		particles.push_back(p);
	}
}
