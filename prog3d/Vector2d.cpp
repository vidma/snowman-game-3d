#include "Vector2d.h"

/*


 F. Aubert

*/

using namespace prog3d;

Vector2d::Vector2d() : Tuple2d() {}
Vector2d::Vector2d(const Tuple2d &t) : Tuple2d(t) {}
Vector2d::Vector2d(double x,double y) : Tuple2d(x,y) {}

Vector2d::Vector2d(const Point2d &a,const Point2d &b) : Tuple2d(0,0) {
    this->setVector(a,b);
}

void Vector2d::setVector(const Point2d &a,const Point2d &b) {
    this->set(b);
    this->sub(a);
}

/*
void Vector3d::set(Tuple3d &t) {
    Tuple3d::set(t);
}
*/
