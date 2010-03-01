#include "ViewportUtil.h"
#include "Point3d.h"
#include "Point4d.h"
#include <GL/gl.h>
#include "Error.h"

/*


 F. Aubert

*/
using namespace prog3d;


ViewportUtil::ViewportUtil() {
    localWindow.setIdentity();
    normalizedLocal.setIdentity();
    windowNormalized.setIdentity();
    normalizedWindow.setIdentity();
    eyeLocal.setIdentity();
}

ViewportUtil::~ViewportUtil() {}

	// transform the mouse (Window coordinates) to the local coordinates (accordingly to localScreen matrix)
	// reference (local coordinates) is required to set the depth of the mouse cursor in screen
Point3d ViewportUtil::applyLocalWindow(const Point2d &mouse,const Point3d &reference) {
		Point4d ref4d(reference);
		normalizedLocal.transform(&ref4d);
		Point4d result4d(mouse.getX(),mouse.getY(),ref4d.getZ()/ref4d.getW(),1.0);
		localWindow.transform(&result4d);
		Point3d result;
		result.project(result4d);
		return result;
	}

// CU : depth should be comprised between [-1,1] (depth in normalized device coordinate)
Point3d ViewportUtil::applyLocalWindow(const Point2d &mouse,double depth) {
	Point4d result4d(mouse.getX(),mouse.getY(),depth,1);
//	result4d.print("result4d avant =");
	localWindow.transform(&result4d);
//	localWindow.print("localWindow =");
//	result4d.print("result4d =");
	Point3d result;
	result.project(result4d);
	return result;
}

Point3d ViewportUtil::applyEyeLocal(const Point3d &p) const {
    Point3d res;
    res.set(p);
    eyeLocal.transform(&res);
    return res;
}

Point3d ViewportUtil::applyEyeLocal(const Vector3d &p) const {
    Vector3d res;
    res.set(p);
    eyeLocal.transform(&res);
    return res;
}

void ViewportUtil::setView() {
    // passage souris en normalisé : xn=1/wv*xs-xv, yn=1/yw*ys-yv
	Matrix4d mproj;
	Matrix4d mmodelview;
	Matrix4d localNormalized;
	double viewport[4]; // viewport : [0]=x_min,[1]=y_min, [2]=width, [3]=height
	double mat[16];
	glGetDoublev(GL_VIEWPORT, viewport);
	glGetDoublev(GL_PROJECTION_MATRIX,mat);
	mproj.set(mat);
	glGetDoublev(GL_MODELVIEW_MATRIX, mat);
	eyeLocal.set(mat);
	mmodelview.set(mat);
	normalizedLocal.mul(mproj,mmodelview);
	localNormalized.invert(normalizedLocal);


	normalizedWindow.setRow(0,2.0/viewport[2],0,0,-1-viewport[0]);
	normalizedWindow.setRow(1,0,-2.0/viewport[3],0,1+viewport[1]);
	normalizedWindow.setRow(2,0,0,1,0);
	normalizedWindow.setRow(3,0,0,0,1);
//	normalizedWindow.print("normalizedWindow");
	windowNormalized.invert(normalizedWindow);
//	windowNormalized.print("windowNormalized");
	localWindow.mul(localNormalized,normalizedWindow);
//	localWindow.print("localWindow=");
}

Point2d ViewportUtil::windowCoordinate(const Point3d &p) const {
	Point2d point2;
	Point4d point3(p);
	normalizedLocal.transform(&point3);
	windowNormalized.transform(&point3);
	point2.setX(point3.getX()/point3.getW());
	point2.setY(point3.getY()/point3.getW());
	return point2;
}

Point3d ViewportUtil::cameraLocal() {
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,mat);
	Matrix4d m;
	m.set(mat);
	m.invert();
	Point3d p(0,0,0);
	m.transform(&p);
	return p;
}

const Matrix4d &ViewportUtil::getEyeLocal() const {
	return eyeLocal;
}



