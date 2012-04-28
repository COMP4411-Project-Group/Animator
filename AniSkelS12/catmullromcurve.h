#include "curveevaluator.h"
#include <vector>
using std::vector;
#ifndef CATMULLROMCURVE_H
#define CATMULLROMCURVE_H
class CatMullRomCurve: public CurveEvaluator {
public:
	void evaluateCurve(
		const vector<Point>& ptvCtrlPts,
		vector<Point>& pvtEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const; 
};
#endif