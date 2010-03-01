#include "Tuple3d.h"
#include "Error.h"
#include <string>

/*


 F. Aubert

*/


#define EPSILON_PREC 0.000001
#include <math.h>
#include <iostream>

using namespace prog3d;
using namespace std;

vector<float> Tuple3d::fc(3);

void Tuple3d::cnew() {
    c.resize(3);
    this->set(0,0,0);
}

Tuple3d::Tuple3d() {
    cnew();
}

Tuple3d::Tuple3d(double x,double y,double z) {
    cnew();
    this->set(x,y,z);
}

Tuple3d::Tuple3d(const Tuple3d &t) {
    cnew();
    this->set(t);
}

void Tuple3d::set(double x,double y,double z) {
    c[0]=x;c[1]=y;c[2]=z;
}

void Tuple3d::set(const Tuple3d &copy) {
    this->set(copy.getX(),copy.getY(),copy.getZ());
}

void Tuple3d::set(int i,double coordinate) {
    c[i]=coordinate;
}

double Tuple3d::getX() const { return c[0];}
double Tuple3d::getY() const { return c[1];}
double Tuple3d::getZ() const { return c[2];}
double *Tuple3d::getDv() {return &c.front();}
const double *Tuple3d::dv() const {return &c.front();}

float *Tuple3d::fv() const {
    fc[0]=c[0];fc[1]=c[1];fc[2]=c[2];
    return &fc.front();
}

void Tuple3d::setX(double a) { c[0]=a;}
void Tuple3d::setY(double a) { c[1]=a;}
void Tuple3d::setZ(double a) { c[2]=a;}

double Tuple3d::length2() const {
    return c[0]*c[0]+c[1]*c[1]+c[2]*c[2];
}

double Tuple3d::length() const {
    return sqrt(this->length2());
}

const Tuple3d &Tuple3d::normalize() {
    double d=this->length();
    if (fabs(d)<EPSILON_PREC) {
        throw Error("Norme nulle",__LINE__,__FILE__);
    }
    c[0]/=d;
    c[1]/=d;
    c[2]/=d;
    return *this;

}


void Tuple3d::add(double x,double y,double z) {
    c[0]+=x;c[1]+=y;c[2]+=z;
}

void Tuple3d::add(const Tuple3d &a) {
    this->set(this->getX()+a.getX(),
        this->getY()+a.getY(),
        this->getZ()+a.getZ());
}

void Tuple3d::add(const Tuple3d &a,const Tuple3d &b) {
    this->set(b.getX()+a.getX(),
        b.getY()+a.getY(),
        b.getZ()+a.getZ());
}

void Tuple3d::sub(const Tuple3d &a) {
    this->set(this->getX()-a.getX(),
        this->getY()-a.getY(),
        this->getZ()-a.getZ());
}


void Tuple3d::sub(const Tuple3d &a,const Tuple3d &b) {
    this->set(a.getX()+b.getX(),
        a.getY()+b.getY(),
        a.getZ()+b.getZ());
}



void Tuple3d::scale(double k) {
    c[0]*=k;
    c[1]*=k;
    c[2]*=k;
}

void Tuple3d::scale(double kx,double ky,double kz) {
    c[0]*=kx;
    c[1]*=ky;
    c[2]*=kz;
}

void Tuple3d::scaleAdd(double k,const Tuple3d &a) {
    this->scale(k);
    this->add(a);
}



// rotation autour de Y (classiquement rotation de profil)
Tuple3d Tuple3d::rotationY(float angle) const {
    Tuple3d res;
    res.setX(cos(angle)*getX()-sin(angle)*getZ());
    res.setY(getY());
    res.setZ(sin(angle)*getX()+cos(angle)*getZ());
    return res;
}

void Tuple3d::moyenne(const Tuple3d& n1,const Tuple3d &n2) {
    this->add(n1,n2);
    this->scale(0.5);
}


void Tuple3d::moyenne(const Tuple3d& n1) {
    this->add(n1);
    this->scale(0.5);
}

double Tuple3d::dot(const Tuple3d &a) const {
    return getX()*a.getX()+getY()*a.getY()+getZ()*a.getZ();
}


double Tuple3d::distance2(const Tuple3d &t) const {
    Tuple3d u(t);
    u.sub(*this);
    return u.length2();
}


void Tuple3d::print(string mesg) const {
    cout << mesg << "(" << this->getX() << "," << this->getY() << "," << this->getZ() << ")" << endl;
}

namespace prog3d {
Tuple3d operator +(const Tuple3d &a,const Tuple3d &b) {
    Tuple3d p(a);
    p.add(b);
    return p;
}

Tuple3d operator -(const Tuple3d &a,const Tuple3d &b) {
    Tuple3d p(a);
    p.sub(b);
    return p;
}

Tuple3d operator *(double k,const Tuple3d &b) {
    Tuple3d p(b);
    p.scale(k);
    return p;
}

Tuple3d operator *(const Tuple3d &b,double k) {
    return k*b;
}

Tuple3d &Tuple3d::operator =(const Tuple3d &a) {
    this->set(a);
    return *this;
}

void Tuple3d::operator +=(const Tuple3d &a) {
    this->add(a);
}

Tuple3d operator -(const Tuple3d &a) {
    Tuple3d res(a);
    res.set(-res.getX(),-res.getY(),-res.getZ());
    return res;
}


ostream& operator <<(std::ostream &s,const Tuple3d &q) {
    s << "(" << q.getX() << "," << q.getY() << "," << q.getZ() << ")";
    return s;
}

}

Tuple3d::~Tuple3d() {}

