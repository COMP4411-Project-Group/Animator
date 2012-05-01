#include "curveevaluator.h"
using std::vector;
#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H
class BezierCurveEvaluator: public CurveEvaluator {
public:
	void evaluateCurve(
		const vector<Point>& ptvCtrlPts,
		vector<Point>& pvtEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const;
};
#endif

