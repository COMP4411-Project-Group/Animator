#include "meta_drawing.h"
#include "modelerglobals.h"
#include "modelerapp.h"
//global settting up
const int minGridSize = 10;
int gridSize = 80;
float threshold = 3.0f;
Cube_Grid cubeGrid(40);
//for testing propose
void drawTwoBalls() {
	//initialize balls
	MetaBall balls[5];
	balls[0].Init(Vec3<float>(-1,0.0,0.0),0.1);
	balls[1].Init(Vec3<float>(-0.2+VAL(META_BALL_1_Pos),0.0,0.0),0.6+VAL(META_BALL_1_Size));
	balls[2].Init(Vec3<float>(0.3+VAL(META_BALL_2_Pos), -0.5, 0.0),1.1+VAL(META_BALL_2_Size));
	balls[3].Init(Vec3<float>(0.3,-1.0,0.0),0.2);
	balls[4].Init(Vec3<float>(0.6, -0.7,0.0),0.4);
	//clear the field
	for(int i=0; i<cubeGrid.numCubes; i++) {
		cubeGrid.vertices[i].value = 0.0;
		cubeGrid.vertices[i].normal->zeroElements();
	}
	Vec3<float> ballToPoint;
	float squaredRadius;
	Vec3<float> ballPosition;
	float normalScale;
	for(int i=0; i<5; i++) {
		squaredRadius = balls[i].squaredRadius;
		ballPosition = balls[i].position;
		//setting the values, tedious math and geogemetry here
		for(int j=0; j<cubeGrid.numVertices; j++) {
			//the vector from vertice to the ball 
			ballToPoint = *(cubeGrid.vertices[j].position) - ballPosition;
			//get squared distance from ball to point
			float squaredDistance = ballToPoint.length2();
			//avoid divided by zero
			if(squaredDistance == 0.0f)
				squaredDistance = 0.0001f;
			//value = r^2/d^2
			//The math of metaball:http://www.niksula.hut.fi/~hkankaan/Homepages/metaballs.html
			//sum n from 1 to k: (s_n)/(|m_n-p|)^g > r
			//m_n the location of metal number n
			//s_n size of meta ball
			//k = number of metaballs
			//g = goo value
			//r = threshold for metaballs
			//p = place vector
			//|x|= length of vector x
			//Scan through grid and evaluate the metaball formual.
			//If the result is true, draw a pixel there.
			cubeGrid.vertices[j].value+=squaredRadius/squaredDistance;
			//normal = (r^2 *v) /d^4
			normalScale = squaredRadius/(squaredDistance*squaredDistance);
			(*(cubeGrid.vertices[j].normal))+=ballToPoint*normalScale;
		}
	}
	//draw surface according to the setup
	cubeGrid.DrawSurface(threshold);
}


