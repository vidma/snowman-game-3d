#include "Line.h"
#include <iostream>

/*


 F. Aubert

*/

using namespace std;
using namespace prog3d;


Line::~Line() {
}

Line::Line() {
    a.set(0,0,0);
    u.set(1,0,0);
}


Line::Line(const Point3d &aa,const Vector3d &uu) {
		u.set(uu);
		a.set(aa);
}

Line::Line(const Point3d &aa,const Point3d &bb) {
    u.set(bb);
    u.sub(aa);
	a.set(aa);
}

void Line::set(const Point3d &aa,const Vector3d &uu) {
    u.set(uu);
    a.set(aa);
}

void Line::set(const Point3d &aa,const Point3d &bb) {
    u.set(bb-aa);
    a.set(aa);
}

Point3d Line::point(double k) const {
    return getA()+k*getU();
}

double Line::distance2(const Point3d &m) {
    Vector3d am(m);
	am.sub(a);

    double k=am.dot(u)/u.dot(u);

	Point3d h(u);
    h.scaleAdd(k,a);

	am.set(h);am.sub(m);
    return am.length2();

}

Point3d Line::getA() const {
    return a;
}

Vector3d Line::getU() const {
    return u;
}

void Line::setA(const Point3d &aa) {
    a=aa;
}

void Line::setU(const Vector3d &uu) {
    u=uu;
}

void Line::print(string mesg) const {
    cout << mesg << "A=" << this->getA() << ", U=" << this->getU() << endl;
}

ostream& prog3d::operator<<(ostream &s,const Line &l) {
    s << "[A=" << l.getA() << ",U=" << l.getU() << "]";
    return s;
}


