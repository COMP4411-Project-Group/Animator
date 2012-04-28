#ifndef FORCE_H_
#define FORCE_H_

#include "vec.h"

class Force {
public:
	virtual void applyTo(Vec3<float>& speed, float deltaT) = 0;
};

class Gravity : public Force {
public:
	Gravity(Vec3<float> v) : val(v) {}
	Vec3<float> val;
	virtual void applyTo(Vec3<float>& speed, float deltaT);
};

class Friction : public Force {
public:
	Friction(float m) : mag(m) {}
	float mag;
	virtual void applyTo(Vec3<float>& speed, float deltaT);
};

class Disturbance : public Force {
public:
	Disturbance(float m) : mag(m) {}
	float mag;
	virtual void applyTo(Vec3<float>& speed, float deltaT);
};

#endif 