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

	forces.push_back(new Gravity(Vec3<float>(0, -0.02, 0)));
	forces.push_back(new Friction(0.001));
	forces.push_back(new Disturbance(0.1));
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
	bake_fps = t - curr_time;
	curr_time = t;
	if (simulate) {
		if (!isBakedAt(t)) {
			vector<Particle>::iterator iter;
			for (iter = particles.begin(); iter != particles.end(); iter++) {
				iter->move(bake_fps);
			}
			bakeParticles(t);
		} else {
			particles = bakeData[t];
		}
	}
}

/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	if (simulate) {
		vector<Particle>::iterator iter;
		for (iter = bakeData[t].begin(); iter != bakeData[t].end(); iter++) {
			iter->draw();
		}
	}
}

/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{
	bakeData.insert(pair<float, vector<Particle>>(t, particles));
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	bakeData.clear();
}

void ParticleSystem::addParticlesAt(Vec3<float> pos, int num) {
	if (simulate) {
		if (!isBakedAt(curr_time + bake_fps)) {
			for (int i = 0; i < num; i++) {
				Particle p(Vec3<float>(pos[0], pos[1], pos[2]), 1);
			
				float mag = rand() % 10 / 10.0 + 0.2;
				float theta = rand() % 360 / 57.3;
		
				float xSpeed = rand() % 10 / 10.0 + 2;
				float ySpeed = cos(theta) * mag;
				float zSpeed = sin(theta) * mag;
		
				p.setSpeed(Vec3<float>(xSpeed, ySpeed, zSpeed));
			
				vector<Force*>::iterator iter;
				for (iter = forces.begin(); iter != forces.end(); iter++) {
					p.addForce(*iter);
				}
			
				particles.push_back(p);
			}
		}
	}
}

bool ParticleSystem::isBakedAt(float t) {
	map<float, vector<Particle>>::iterator it = bakeData.find(t);
	return (it != bakeData.end());
}
