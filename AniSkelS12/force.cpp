#include "force.h"

void Gravity::applyTo(Vec3<float>& speed) {
	speed += val;
}

void Friction::applyTo(Vec3<float>& speed) {
	speed *= (1 - mag);
}