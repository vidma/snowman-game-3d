#include "Point3d.h"
#include "Vector3d.h"
#include "Point4d.h"
#include <math.h>
#include "Error.h"
#include <GL/gl.h>

/*


 F. Aubert

*/
using namespace prog3d;


#include <iostream>

using namespace std;

Point3d::~Point3d() {
}

Point3d::Point3d() : Tuple3d() {
}

Point3d::Point3d(const Tuple3d &t) : Tuple3d(t) {}
Point3d::Point3d(double x,double y,double z) : Tuple3d(x,y,z) {}


void Point3d::project(const Point4d &p) {
    if (fabs(p.getW())<1e-10)
    throw Error("W is zero (Point3d.cpp)",__LINE__,__FILE__);
    set(p.getX()/p.getW(),p.getY()/p.getW(),p.getZ()/p.getW());
}

void Point3d::translate(double x,double y,double z) {
    this->add(x,y,z);
}

void Point3d::drawTo(const Point3d &p) const {
    glBegin(GL_LINES);
    glVertex3dv(this->dv());
    glVertex3dv(Point3d(p).dv());
    glEnd();
}

void Point3d::draw() {
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3dv(this->dv());
    glEnd();
    glPointSize(1);
}


// donne un vecteur normé orthogonal au segment [this,P2]. Tout doit être dans le plan Z=0
Vector3d Point3d::normaleSegmentXY(const Point3d &p2) {
    Vector3d res;
    res.Tuple3d::set(this->getY()-p2.getY(),p2.getX()-this->getX(),0.0);
    res.normalize();
    return res;
}

// ************************************************************************************
// APoint3d

void APoint3d::drawTo(APoint3d &l) {
    if (l.size()!=this->size()) throw Error("APoint3d::drawTo : point numbers are not equals",__LINE__,__FILE__);
    glBegin(GL_QUAD_STRIP);
    for(unsigned int i=0;i<size();i++) {
        glVertex3fv((*this)[i].fv());
        glVertex3fv(l[i].fv());
    }
    glEnd();
}









