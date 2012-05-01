#include "c_two_interpolate_curve.h"

void CtwoCurve::evaluateCurve(
	const vector<Point>& ptvCtrlPts,
	vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const {
	int size = ptvCtrlPts.size();
	if(size < 3) {
		return;
	}
	ptvEvaluatedCurvePts.clear();

	float* gamma = new float[size];
	float* deltaX = new float[size];
	float* deltaY = new float[size];
	float* DX = new float[size];
	float* DY = new float[size];
	//setup gamma
	gamma[0] = 0.5;
	for(int i=1; i<size-1; i++) {
		gamma[i] = 1.0/(4.0-gamma[i-1]);
	}
	gamma[size-1] = 0.5-gamma[size-2];

	deltaX[0] = 3*(ptvCtrlPts[1].x - ptvCtrlPts[0].x) * gamma[0];
	deltaY[0] = 3*(ptvCtrlPts[1].y - ptvCtrlPts[1].y) * gamma[0];
	
	for(int i=1; i < size-1; i++) {
		deltaX[i] = (3*(ptvCtrlPts[i+1].x - ptvCtrlPts[i-1].x)-deltaX[i-1])*gamma[i];
		deltaY[i] = (3*(ptvCtrlPts[i+1].y - ptvCtrlPts[i-1].y)-deltaY[i-1])*gamma[i];
	}
	deltaX[size-1] = (3*(ptvCtrlPts[size-1].x-ptvCtrlPts[size-2].x)-deltaX[size-2])*gamma[size-1];
	deltaY[size-1] = (3*(ptvCtrlPts[size-1].y-ptvCtrlPts[size-2].y)-deltaY[size-2])*gamma[size-1];

	DX[size-1] = deltaX[size-1];
	DY[size-1] = deltaY[size-1];
	for(int i=size-2; i>=0; i--) {
		DX[i] = deltaX[i] - gamma[i]*DX[i+1];
		DY[i] = deltaY[i] - gamma[i]*DY[i+1];
	}
	for(int i=0; i< size; i++) {
		printf("%f, %f, %f\n", gamma[i], deltaX[i], DX[i]);
	}
	int n_sample = 25;
	for(int i=0; i<size-1; i++) {
		float a_x = ptvCtrlPts[i].x;
		float a_y = ptvCtrlPts[i].y;
		float b_x = DX[i];
		float b_y = DY[i];
		float c_x = 3*(ptvCtrlPts[i+1].x - ptvCtrlPts[i].x)-2*DX[i] - DX[i+1];
		float c_y = 3*(ptvCtrlPts[i+1].y - ptvCtrlPts[i].y)-2*DY[i] - DY[i+1];
		float d_x = 2*(ptvCtrlPts[i].x - ptvCtrlPts[i+1].x)+DX[i]+DX[i+1];
		float d_y = 2*(ptvCtrlPts[i].y - ptvCtrlPts[i+1].y)+DY[i]+DY[i+1];
		//printf("%f,%f,%f,%f\n", a_x, b_x, c_x, d_x);
		for(int j=0; j<n_sample; j++) {
			float t = j/(float)n_sample;
			float c2_x = a_x + t*b_x + t*t*c_x + t*t*t*d_x;
			float c2_y = a_y + t*b_y + t*t*c_y + t*t*t*d_y;
			//printf("%f, %f\n", c2_x, c2_y);
			Point currpt(c2_x, c2_y);
			ptvEvaluatedCurvePts.push_back(currpt);
		}
	}
	delete [] gamma;
	delete [] DX;
	delete [] DY;
	delete [] deltaX;
	delete [] deltaY;
}
