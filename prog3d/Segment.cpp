#include "Segment.h"
#include "Vector3d.h"
#include "Line.h"

#include <iostream>

/*


 F. Aubert

*/
using namespace std;

using namespace prog3d;

void Segment::init() {
		resultatDistance=A;
}

Segment::Segment() {
    init();
    a.set(0,0,0);
    b.set(0,0,0);
}

Segment::Segment(const Point3d &aa,const Point3d &bb) {
		init();
		a.set(aa);
		b.set(bb);
	}

Segment::Segment(const Point2d &aa,const Point2d &bb) {
		init();
		a.set(aa.getX(),aa.getY(),0);
		b.set(bb.getX(),bb.getY(),0);
	}


void Segment::print(string mesg) {
    cout << mesg << " : "; a.print("a=");b.print("b="); cout << endl;
}

void Segment::setAB(const Point3d &aa,const Point3d &bb) {
		a.set(aa);
		b.set(bb);
}

void Segment::setAB(const Point2d &aa,const Point2d &bb) {
		a.set(aa.getX(),aa.getY(),0);
		b.set(bb.getX(),bb.getY(),0);
}

double Segment::distance2(const Point3d &p) {
		Vector3d ab(b);
		ab.sub(a);
		Vector3d pab(p);
		pab.sub(a);
//		this->print("Segment =");
//		p.print("Point =");
		if (pab.dot(ab)<0) {
			return p.distance2(a);
		}
		pab.set(p);pab.sub(b);
		if (pab.dot(ab)>0) {
			return p.distance2(b);
		}

		Line d(a,b);

		return d.distance2(p);
	}

double Segment::distance2(const Point2d &p) {
		return distance2(Point3d(p.getX(),p.getY(),0));
}

Point3d Segment::interp(double k) {
    return Point3d((1-k)*a+k*b);
}

