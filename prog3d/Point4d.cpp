#include "Point4d.h"
#include "Point3d.h"
#include "Vector3d.h"
#include <iostream>


using namespace std;
using namespace prog3d;

vector<float> Point4d::fc(4);

void Point4d::init() {
    c.resize(4);
}

Point4d::Point4d() {
    init();
}

Point4d::Point4d(const Point3d &p) {
    init();
    this->set(p);
}

Point4d::Point4d(const Vector3d &p) {
    init();
    this->set(p);
}

Point4d::Point4d(const Point4d &p) {
    init();
    this->set(p);
}

Point4d::Point4d(double x,double y,double z,double w) {
    init();
    c[0]=x;c[1]=y;c[2]=z;c[3]=w;
}

Point4d::~Point4d() {}

void Point4d::set(const Point3d &p) {
    c[0]=p.getX();
    c[1]=p.getY();
    c[2]=p.getZ();
    c[3]=1.0;
}

void Point4d::set(const Vector3d &p) {
    c[0]=p.getX();
    c[1]=p.getY();
    c[2]=p.getZ();
    c[3]=0.0;
}


void Point4d::set(const Point4d &p) {
    c[0]=p.getX();
    c[1]=p.getY();
    c[2]=p.getZ();
    c[3]=p.getW();
}

double Point4d::getX() const { return c[0];}
double Point4d::getY() const { return c[1];}
double Point4d::getZ() const { return c[2];}
double Point4d::getW() const { return c[3];}

void Point4d::setX(double x) { c[0]=x;}
void Point4d::setY(double y) { c[1]=y;}
void Point4d::setZ(double z) { c[2]=z;}
void Point4d::setW(double w) { c[3]=w;}

double *Point4d::dv() {
    return &(c.front());
}

float *Point4d::fv() const {
    fc[0]=c[0];fc[1]=c[1];fc[2]=c[2];fc[3]=c[3];
    return &fc.front();
}

void Point4d::print(string mesg) const {
    cout << mesg << "(" << c[0] << "," << c[1] << "," << c[2] << "," << c[3] << ")\n";
}

ostream& prog3d::operator <<(ostream &s,const Point4d &p) {
    s << "(" << p.getX() << "," << p.getY() << "," << p.getZ() << "," << p.getW() << ")";
    return s;
}



