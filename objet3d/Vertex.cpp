#include "Vertex.h"
#include <iostream>
#include <math.h>

using namespace std;
using namespace prog3d;




Vertex::~Vertex() {
    /*
    if (p) delete p;
    if (n) delete n;
    */
}


void Vertex::init() {
    /*
    p=new Point3d;
    n=new Vector3d;
    */
}

Vertex::Vertex() {
    init();
    p.set(0,0,0);
}

Vertex::Vertex(double x,double y, double z) {
    init();
    p.set(x,y,z);
}

Vertex::Vertex(const Point3d &p) {
    init();
    this->p.set(p);
}

Point3d &Vertex::getPoint() {
    return p;
}

Vector3d &Vertex::getNormal() {
    return n;
}

const Point3d &Vertex::point() const {
	return p;
}

const Vector3d &Vertex::normal() const {
	return n;
}

void Vertex::setPoint(const Point3d &p) {
    this->p.set(p);
}

void Vertex::setNormal(const Vector3d &n) {
    this->n.set(n);
}

void Vertex::translate(double x,double y,double z) {
    p.add(x,y,z);
}

void Vertex::scale(double k) {
    p.scale(k);
}

void Vertex::scale(double kx,double ky,double kz) {
    this->getPoint().scale(kx,ky,kz);
}

void Vertex::setNumber(int i) {
    number=i;
}

int Vertex::getNumber() {
    return number;
}

void Vertex::averageNormalBegin() {
    nbNormal=0;
}

void Vertex::averageNormalEnd() {
//    cout << nbNormal << endl;
    if (fabs(n.length2())>1e-10) {
        n.scale(1.0/nbNormal);
        n.normalize();
    }
}

void Vertex::averageNormalAdd(const Vector3d &a) {
    n.add(a);
    nbNormal++;
}


void Vertex::set(const Vertex &v) {
	setPoint(v.point());
	setNormal(v.normal());
}



