#include "Point2d.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include <math.h>
#include "Error.h"

/*


 F. Aubert

*/
using namespace prog3d;


Point2d::Point2d() : Tuple2d() {}
Point2d::Point2d(const Tuple2d &t) : Tuple2d(t) {}
Point2d::Point2d(double x,double y) : Tuple2d(x,y) {}

Point2d::~Point2d() {
}



// donne un vecteur normé orthogonal au segment [this,P2].
Vector2d Point2d::normaleSegment(const Point2d &p2) {
    Vector2d res;
    res.set(this->getY()-p2.getY(),p2.getX()-this->getX());
    res.normalize();
    return res;
}

double Point2d::distance2(const Point2d &a) const {
    Vector2d l;
    l.setVector(*this,a);
    return l.length2();
}


