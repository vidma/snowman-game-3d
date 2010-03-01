#include "Vector3d.h"
#include <math.h>
#include "Error.h"

/*


 F. Aubert

*/

using namespace prog3d;

Vector3d::Vector3d() : Tuple3d() {}
Vector3d::Vector3d(const Tuple3d &t) : Tuple3d(t) {}
Vector3d::Vector3d(double x,double y,double z) : Tuple3d(x,y,z) {}

Vector3d::Vector3d(const Point3d &a,const Point3d &b) : Tuple3d(0,0,0) {
    this->setVector(a,b);
}

void Vector3d::setVector(const Point3d &a,const Point3d &b) {
    this->set(b);
    this->sub(a);
}

void Vector3d::wedge(const Vector3d &a,const Vector3d &b) {
    this->set(a.getY()*b.getZ()-a.getZ()*b.getY(),
        a.getZ()*b.getX()-b.getZ()*a.getX(),
        a.getX()*b.getY()-b.getX()*a.getY());
}


void Vector3d::project(const Point4d &p) {
    if (fabs(p.getW())>1e-10)
        error("W is not zero ! (Vector3d.cpp)",__LINE__,__FILE__);
    set(p.getX(),p.getY(),p.getZ());
}




