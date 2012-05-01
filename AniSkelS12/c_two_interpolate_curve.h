#include "curveevaluator.h"
#ifndef C_TWO_INTERPOLATE_CURVE_H
#define C_TWO_INTERPOLATE_CURVE_H
using std::vector;
class CtwoCurve: public CurveEvaluator {
	void evaluateCurve(
		const vector<Point>& ptvCtrlPts,
		vector<Point>& pvtEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const; 
};

#endif