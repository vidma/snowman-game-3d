#include "Plan.h"
#include <iostream>
#include "UtilGL.h"

/*


 F. Aubert

*/
using namespace std;
using namespace prog3d;

Plan::~Plan() {
}

Plan::Plan() {
}

Plan::Plan(const Point3d &a,const Vector3d &n) {
    this->set(a,n);
}

void Plan::set(const Point3d &p1,const Point3d &p2,const Point3d &p3) {
    Vector3d u1(p1,p2);
    Vector3d u2(p2,p3);
    n.wedge(u1,u2);
    a.set(p1);
}

void Plan::set(const Point3d &a,const Vector3d &n) {
    this->n.set(n);
    this->a.set(a);
}

double Plan::interK(const Line &d) {
    return (n.dot(a-d.getA()))/n.dot(d.getU());
}

Point3d Plan::project(const Point3d &p) {
    Line d(p,n);
    double k=this->interK(d);
    return k*n+p;
}

Point3d Plan::project(const Point3d &p,const Vector3d &u) {
    Line d(p,u);
    double k=this->interK(d);
//    UtilGL::add(k*u+p);
    return k*u+p;
}

Point3d Plan::getA() const {
    return a;
}

Vector3d Plan::getN() const {
    return n;
}
