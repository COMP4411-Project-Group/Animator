#include "bsplinecurve.h"
#include "vec.h"
#include "mat.h"


void Bspline::evaluateCurve(
		const vector<Point>& ptvCtrlPts,
		vector<Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const {
	//Not enough points, use straight line
	int numCtrPt = ptvCtrlPts.size();
	if(numCtrPt<4) {
		printf("Smaller than 4");
		//If the number is less than 4, simply do linear, copy and paste from linear evaluator
		int iCtrlPtCount = ptvCtrlPts.size();
	
		ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
	
		float x = 0.0;
		float y1;
	
		if (bWrap) {
			// if wrapping is on, interpolate the y value at xmin and
			// xmax so that the slopes of the lines adjacent to the
			// wraparound are equal.
	
			if ((ptvCtrlPts[0].x + fAniLength) - ptvCtrlPts[iCtrlPtCount - 1].x > 0.0f) {
				y1 = (ptvCtrlPts[0].y * (fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x) + 
					  ptvCtrlPts[iCtrlPtCount - 1].y * ptvCtrlPts[0].x) /
					 (ptvCtrlPts[0].x + fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x);
			}
			else 
				y1 = ptvCtrlPts[0].y;
		}
		else {
			// if wrapping is off, make the first and last segments of
			// the curve horizontal.
	
			y1 = ptvCtrlPts[0].y;
		}
	
		ptvEvaluatedCurvePts.push_back(Point(x, y1));
	
		/// set the endpoint based on the wrap flag.
		float y2;
		x = fAniLength;
		if (bWrap)
			y2 = y1;
		else
			y2 = ptvCtrlPts[iCtrlPtCount - 1].y;
	
		ptvEvaluatedCurvePts.push_back(Point(x, y2));
		return;
	}
	ptvEvaluatedCurvePts.clear();
	// Modification
	vector<Point> de_boor_ctrl_pts;
	de_boor_ctrl_pts.assign(ptvCtrlPts.begin(),ptvCtrlPts.end());

	//Do wrapping
	if(bWrap) {
		for(int i=0; i<3; i++) {
			Point wrapped_pt(ptvCtrlPts[i].x + fAniLength, ptvCtrlPts[i].y);
			de_boor_ctrl_pts.push_back(wrapped_pt); } Point wrapped_pt(ptvCtrlPts[numCtrPt-1].x-fAniLength, ptvCtrlPts[numCtrPt-1].y);
		de_boor_ctrl_pts.insert(de_boor_ctrl_pts.begin(), wrapped_pt);
	}
	//Interpolate the start points, by duplicate the end points
	de_boor_ctrl_pts.insert(de_boor_ctrl_pts.begin(),de_boor_ctrl_pts.front()); 
	de_boor_ctrl_pts.insert(de_boor_ctrl_pts.begin(),de_boor_ctrl_pts.front()); 
	de_boor_ctrl_pts.push_back(de_boor_ctrl_pts.back());
	de_boor_ctrl_pts.push_back(de_boor_ctrl_pts.back());
	
	numCtrPt = de_boor_ctrl_pts.size();

	//Create the corresponding bezier control points
	vector<Point> bezier_ctrl_pts;
	for(int i=0; i< numCtrPt-1; i++) {
		if(i!=0) {
			Point tmp1(
				de_boor_ctrl_pts[i].x*2/3 + de_boor_ctrl_pts[i+1].x/3,
				de_boor_ctrl_pts[i].y*2/3 + de_boor_ctrl_pts[i+1].y/3);
			Point tmp0(
				(tmp1.x+bezier_ctrl_pts.back().x)/2,
				(tmp1.y+bezier_ctrl_pts.back().y)/2);
			if(i==1) {
				bezier_ctrl_pts.pop_back();
			}
			bezier_ctrl_pts.push_back(tmp0);
			if(i!=numCtrPt-1) {
				bezier_ctrl_pts.push_back(tmp1);
			}
		}
		if(i!=numCtrPt-1) {
			Point tmp2(
				de_boor_ctrl_pts[i].x/3+de_boor_ctrl_pts[i+1].x*2/3,
				de_boor_ctrl_pts[i].y/3+de_boor_ctrl_pts[i+1].y*2/3);
			bezier_ctrl_pts.push_back(tmp2);
		}
	}
	numCtrPt = bezier_ctrl_pts.size();

	Mat4f bezier_basis_matrix(-1, 3, -3, 1,
					   3 ,-6,  3, 0,
					   -3, 3,  0, 0,
					    1, 0,  0, 0);
	int index = 0;
	int step_length = 3;
	int n_sample=100;
	//For each four points, we do sample the curve
	//In C_0 continuity
	for(; index < numCtrPt-3;index+=step_length) {
		//Get the four point group
		Point p1=bezier_ctrl_pts[index];
		Point p2=bezier_ctrl_pts[index+1];
		Point p3=bezier_ctrl_pts[index+2]; 
		Point p4=bezier_ctrl_pts[index+3];

		Vec4f x_val(p1.x,p2.x,p3.x, p4.x);
		Vec4f y_val(p1.y, p2.y, p3.y, p4.y);

		//Construct Beizer from de Boor Points
		x_val = bezier_basis_matrix*x_val;
		y_val = bezier_basis_matrix*y_val;


		//pick samples
		for(int i=0; i<n_sample; i++) {
			//length betwen each sample
			float t=i/(float)n_sample;
			float bezier_x = t*t*t * x_val[0] + t*t*x_val[1] + t*x_val[2] + x_val[3];
			float bezier_y = t*t*t * y_val[0] + t*t*y_val[1] + t*y_val[2] + y_val[3];

			Point curr_pt(bezier_x, bezier_y);
			ptvEvaluatedCurvePts.push_back(curr_pt);
		}
	}
}