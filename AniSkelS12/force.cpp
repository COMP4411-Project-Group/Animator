#include "force.h"

void Gravity::applyTo(Vec3<float>& speed, float deltaT) {
	speed += val * deltaT;
}

void Friction::applyTo(Vec3<float>& speed, float deltaT) {
	speed *= (1 - mag * deltaT);
}

void Disturbance::applyTo(Vec3<float>& speed, float deltaT) {
	float randomness = 1 - mag;
	speed[0] *= (1 + (rand() % 10 / 10.0 - 0.5) * mag);
	speed[1] *= (1 + (rand() % 10 / 10.0 - 0.5) * mag);
	speed[2] *= (1 + (rand() % 10 / 10.0 - 0.5) * mag);
}