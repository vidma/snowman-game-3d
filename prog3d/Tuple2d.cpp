#define EPSILON_PREC 0.000001
#include <math.h>
#include <iostream>
#include "Tuple2d.h"

/*!
*
* @file
* @brief Op\'erations sur les entit\'es de type (x,y)
*
* @author F. Aubert
*
*/

using namespace prog3d;
using namespace std;

vector<float> Tuple2d::fc(2);

void Tuple2d::cnew() {
    c.resize(2);
    this->set(0,0);
}

Tuple2d::Tuple2d() {
    cnew();
}

Tuple2d::Tuple2d(double x,double y) {
    cnew();
    this->set(x,y);
}

void Tuple2d::set(double x,double y) {
    c[0]=x;c[1]=y;
}

void Tuple2d::set(const Tuple2d &copy) {
    this->set(copy.getX(),copy.getY());
}

double Tuple2d::getX() const { return c[0];}
double Tuple2d::getY() const { return c[1];}
const double *Tuple2d::dv() const {return &c.front();}

const float *Tuple2d::fv() const {
    fc[0]=c[0];fc[1]=c[1];
    return &fc.front();
}

void Tuple2d::setX(double a) { c[0]=a;}
void Tuple2d::setY(double a) { c[1]=a;}

double Tuple2d::length2() {
    return c[0]*c[0]+c[1]*c[1];
}

double Tuple2d::length() {
    return sqrt(this->length2());
}

void Tuple2d::normalize() {
    double d=this->length();
    if (fabs(d)<EPSILON_PREC) {
        throw "Normale nulle";
    }
    c[0]/=d;
    c[1]/=d;

}


void Tuple2d::add(const Tuple2d &a) {
    this->set(this->getX()+a.getX(),
    this->getY()+a.getY());
}

void Tuple2d::add(const Tuple2d &a,const Tuple2d &b) {
    this->set(b.getX()+a.getX(),
        b.getY()+a.getY());
}

void Tuple2d::sub(const Tuple2d &a) {
    this->set(this->getX()-a.getX(),
        this->getY()-a.getY());
}


void Tuple2d::sub(const Tuple2d &a,const Tuple2d &b) {
    this->set(a.getX()+b.getX(),
        a.getY()+b.getY());
}

double Tuple2d::dot(const Tuple2d &a) {
    return getX()*a.getX()+getY()*a.getY();
}


void Tuple2d::scale(double k) {
    c[0]*=k;
    c[1]*=k;
}



void Tuple2d::moyenne(const Tuple2d& n1,const Tuple2d &n2) {
    this->add(n1,n2);
    this->scale(0.5);
}


void Tuple2d::moyenne(const Tuple2d& n1) {
    this->add(n1);
    this->scale(0.5);
}



void Tuple2d::print() {
    cout << "x=" << this->getX() << ",y=" << this->getY() << endl;
}

Tuple2d::~Tuple2d() {}


namespace prog3d {
Tuple2d operator +(const Tuple2d &a,const Tuple2d &b) {
    Tuple2d p(a);
    p.add(b);
    return p;
}

Tuple2d operator -(const Tuple2d &a,const Tuple2d &b) {
    Tuple2d p(a);
    p.sub(b);
    return p;
}

Tuple2d operator *(double k,const Tuple2d &b) {
    Tuple2d p(b);
    p.scale(k);
    return p;
}

Tuple2d operator *(const Tuple2d &b,double k) {
    return k*b;
}

Tuple2d &Tuple2d::operator=(const Tuple2d &a) {
    this->set(a);
    return *this;
}


ostream& operator <<(std::ostream &s,const Tuple2d &q) {
    s << "(" << q.getX() << "," << q.getY() << ")";
    return s;
}
}

