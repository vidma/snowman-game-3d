#include <stdlib.h>
#include "Quaternion.h"
#include <math.h>
#include "Matrix4d.h"
#include "Vector3d.h"
#include "Error.h"
#include <math.h>

/*


 F. Aubert

*/
using namespace std;
using namespace prog3d;


Quaternion::Quaternion(double ww,double xx, double yy, double zz) {
  set(ww,xx,yy,zz);
}

void Quaternion::set(double ww,double xx,double yy,double zz) {
  x=xx;
  y=yy;
  z=zz;
  w=ww;
}

Quaternion::Quaternion(const Quaternion &q) {
    this->set(q);
}



double Quaternion::length() const {
  return sqrt(w*w+x*x+y*y+z*z);
}

double Quaternion::lengthXYZ() const {
  return sqrt(x*x+y*y+z*z);
}

void Quaternion::normalize() {
  double n=length();
  w/=n;
  x/=n;
  y/=n;
  z/=n;
}

void Quaternion::set(float scalar,const Vector3d &v,int verif) {
    w=scalar;
    x=v.getX();y=v.getY();z=v.getZ();
}

void Quaternion::copyTo(Matrix4d *m) {
    m->set(*this);
}


void Quaternion::copyToAngleAxis(float *angle,Vector3d *u) {
  *angle=2*acos(w);
  double s=lengthXYZ();
  double ax=x/s;
  double ay=y/s;
  double az=z/s;
  u->set(ax,ay,az);
}


ostream &prog3d::operator <<(ostream &s,const Quaternion &q) {
  s<<"(w= " << q.getW() << " x= " << q.getX() << " y= " << q.getY() << " z= " << q.getZ() << ")";
  s<<"norme=" << q.length() << endl;
  return s;
}

void Quaternion::set(Matrix4d src)
{
  cout << "not implemented" << endl;
  exit(1);
}





// mult quaternion
void Quaternion::mul(const Quaternion &q1,const Quaternion &q2)
{
  if ((&q1==this) || (&q2==this)) error("MULT ref=this",__LINE__,__FILE__);
//Q1 * Q2 =( w1.w2 - v1.v2, w1.v2 + w2.v1 + v1*v2)
	w=  q1.getW()*q2.getW() - q1.getX()*q2.getX() - q1.getY()*q2.getY() - q1.getZ()*q2.getZ();
	x = q1.getW()*q2.getX() + q1.getX()*q2.getW() + q1.getY()*q2.getZ() - q1.getZ()*q2.getY();
	y = q1.getW()*q2.getY() + q1.getY()*q2.getW() + q1.getZ()*q2.getX() - q1.getX()*q2.getZ();
	z = q1.getW()*q2.getZ() + q1.getZ()*q2.getW() + q1.getX()*q2.getY() - q1.getY()*q2.getX();
}


void Quaternion::mul(const Quaternion &q) {
  Quaternion q2;
  q2.set(*this);
  this->mul(q2,q);
}

Quaternion prog3d::operator *(const Quaternion &q1,const Quaternion &q2) {
    Quaternion res;
    res.mul(q1,q2);
    return res;
}

// initializer
void Quaternion::set(const Quaternion &q) {
  set(q.getW(),q.getX(),q.getY(),q.getZ());
}

// conjugate
void Quaternion::conjugate() {
  x=-x;
  y=-y;
  z=-z;
}

// square norme
double Quaternion::length2() {
  return w*w+x*x+y*y+z*z;
}

// from AxisAngle
void Quaternion::setFromAngleAxis(float angle,const Vector3d &v) {
  w=cos(angle/2);
  double ss=sin(angle/2);
  x=v.getX()*ss;
  y=v.getY()*ss;
  z=v.getZ()*ss;
  this->normalize();
}


// interpolation unit quaternion in [0,1]
void Quaternion::interpolate(double t,const Quaternion &q1, const Quaternion &q2) {
/*
  Quaternion q11;
  q11.set(q1);
  q11.sConjugate();
  Quaternion q22;
  q22.set(q2);
  Quaternion q3;
  q3.sMult(q11,q22);
  AxisAngle a;
  AxisAngle a1,a2;
  a1.set(q11);
  a2.set(q22);
  cout << a1 << endl;
  cout << a2 << endl;
  a.set(q3);
  cout << a << endl;
  a.sAngle(t*a.AngleDeg());
  this->set(a);
*/
}

// scale
void Quaternion::scale(double s) {
	w*=s;
	x*=s;
	y*=s;
	z*=s;
}

void Quaternion::add(const Quaternion &q1,const Quaternion &q2) {
	w=q1.getW()+q2.getW();
	x=q1.getX()+q2.getX();
	y=q1.getY()+q2.getY();
	z=q1.getZ()+q2.getZ();
}

Quaternion operator *(double k,const Quaternion &q) {
    Quaternion res(q);
    res.scale(k);
    return res;
}

void Quaternion::set(const Vector3d &v1,const Vector3d &v2) {
    Vector3d u;
    Vector3d vv1=v1;
    Vector3d vv2=0.5*(v1+v2);
    u.wedge(vv1,vv2);
    this->set(vv1.dot(vv2),u,1);
    this->normalize();
}
