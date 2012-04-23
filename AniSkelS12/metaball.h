#include "vec.h"
#ifndef METABALL_H
#define METABALL_H
class MetaBall {
public:
	Vec3<float> position;
	float squaredRadius;
	void Init(Vec3<float> Pos, float newSquaredRadius) {
		position = Pos;
		squaredRadius = newSquaredRadius;
	}
};
#endif

