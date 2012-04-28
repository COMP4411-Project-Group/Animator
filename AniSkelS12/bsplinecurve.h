#include "curveevaluator.h"
#ifndef BSPLINE_CURVE
#define BSPINE_CURVE

using std::vector;
class Bspline: public CurveEvaluator {
public:
	void evaluateCurve(
		const vector<Point>& ptvCtrlPts,
		vector<Point>& pvtEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const; 
private:
	void interpolate_start(vector<Point>& de_boor_ptrs);
};
#endif