#include "Matrix4d.h"
#include <iostream>
#include <math.h>
#include <string>
#include "Point4d.h"
#include "Point3d.h"
#include "Vector3d.h"
#include "Error.h"
#include "Quaternion.h"



/*


 F. Aubert

*/
using namespace prog3d;
using namespace std;

float Matrix4d::mf[16];

void Matrix4d::init() {
    m.resize(16);
}

Matrix4d::Matrix4d() {
    init();
}

Matrix4d::~Matrix4d() {
}

Matrix4d::Matrix4d(const Matrix4d &m) {
    init();
    this->set(m);
}

/*
double Matrix4d::operator [](int i) const {
    return m[i];
}

void Matrix4d::set(int i,double v) {
    m[i]=v;
}
*/

void Matrix4d::set(const Matrix4d &a) {
    for(int i=0;i<16;i++) {
        m[i]=a[i];
    }
}

double Matrix4d::get(int i) const {
    return m[i];
}

const double *Matrix4d::dv() const {
    return &(m.front());
}

void Matrix4d::transform(Point3d *p) const {
//    cout << "Point A avant = " << *p << endl;
    Point4d temp;
    temp.set(*p);
    transform(&temp);
    p->project(temp);
//    cout << "Point A apr�s = " << *p << endl;
}

void Matrix4d::transform(Vector3d *p) const {
//    cout << "Vector A avant = " << *p << endl;
    Point4d temp;
    temp.set(*p);
    transform(&temp);
    p->project(temp);
//    cout << "Vector A apr�s = " << *p << endl;
}

void Matrix4d::transform(Point4d *p) const {
    Point4d temp;
//    this->print("MATRICE =");
    temp.set(*p);
    temp.print("POINT =");
    p->setX(m[0]*temp.getX()+m[4]*temp.getY()+m[8]*temp.getZ()+m[12]*temp.getW());
    p->setY(m[1]*temp.getX()+m[5]*temp.getY()+m[9]*temp.getZ()+m[13]*temp.getW());
    p->setZ(m[2]*temp.getX()+m[6]*temp.getY()+m[10]*temp.getZ()+m[14]*temp.getW());
    p->setW(m[3]*temp.getX()+m[7]*temp.getY()+m[11]*temp.getZ()+m[15]*temp.getW());
//    p->print("TRANSFORM =");
}

Point3d Matrix4d::transform(const Point3d &p) {
//    cout << "transform Point" << endl;
    Point3d res=p;
    transform(&res);
    return res;
}

Vector3d Matrix4d::transform(const Vector3d &p) {
//    cout << "transform Vector" << endl;
    Vector3d res=p;
    transform(&res);
    return res;
}

Point4d Matrix4d::transform(const Point4d &p) {
    Point4d res=p;
    transform(&res);
    return res;
}

void Matrix4d::setIdentity() {
    for(vector<double>::iterator a=m.begin();a!=m.end();a++) {
        *a=0.0;
    }

    for(int i=0;i<16;i+=5) {
      m[i]=1.0;
    }

}

void Matrix4d::set(double *v) {
    for(int i=0;i<16;i++) {
        m[i]=v[i];
    }
}

void Matrix4d::set(float *v) {
    for(int i=0;i<16;i++) {
        m[i]=v[i];
    }
}

void Matrix4d::print(string mesg) const {
    cout << "matrice " << mesg << endl;
    int index=0;
    for(int i=0;i<4;i++) {
        cout << "(";
        for(int j=0;j<4;j++) {
          cout << m[index] << " ";
          index+=4;
        }
        cout << ")" << endl;
        index-=15;
    }
}

void Matrix4d::swapColumn(int i,int j) {
    double swap;
    int c1=i*4;
    int c2=j*4;
    for(int k=0;k<4;k++) {
        swap=m[c1];
        m[c1]=m[c2];
        m[c2]=swap;
        c1++;c2++;
    }
}


void Matrix4d::scaleColumn(int i,double k) {
    int c=i*4;
    for(int j=0;j<4;j++) {
        m[c]*=k;
        c++;
    }
}

void Matrix4d::mul(const Matrix4d &a) {
    Matrix4d temp;
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            int tt=i+j*4;
            temp.set(tt,0);
            for(int k=0;k<4;k++) {
                temp.set(tt, temp[tt]+m[i+k*4]*a.get(k+j*4));
            }
        }
    }
    this->set(temp);
}

void Matrix4d::mulLeft(const Matrix4d &a) {
    Matrix4d temp;
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            int tt=i+j*4;
            temp.set(tt,0);
            for(int k=0;k<4;k++) {
                temp.set(tt, temp[tt]+a.get(i+k*4)*m[k+j*4]);
            }
        }
    }
    this->set(temp);
}



void Matrix4d::mul(const Matrix4d &a,const Matrix4d &b) {
    if ((this==&a) || (this==&b)) error("auto mul : use mul(const Matrix4d &)",__LINE__,__FILE__);
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            int tt=i+j*4;
            this->set(tt,0);
            for(int k=0;k<4;k++) {
                this->set(tt, (*this)[tt]+a[i+k*4]*b.get(k+j*4));
            }
        }
    }
}


void Matrix4d::transpose() {
    Matrix4d temp(*this);
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            m[i*4+j]=temp[j*4+i];
        }
    }
}

void Matrix4d::invert() {
    Matrix4d temp(*this);
    this->invert(temp);
}


void Matrix4d::subScaleColumn(int i,int j,double s) {
    int c1=i*4;int c2=j*4;
    for(int k=0;k<4;k++) {
        m[c1]-=(m[c2]*s);
        c1++;c2++;
    }
}

void Matrix4d::subScaleLine(int i,int j,double s) {
    int l1=i;int l2=j;
    for(int k=0;k<4;k++) {
        m[l1]-=(m[l2]*s);
        l1+=4;l2+=4;
    }
}

void Matrix4d::setRow(int i,double x,double y,double z,double w) {
    m[i]=x;m[i+4]=y;m[i+8]=z;m[i+12]=w;
}

void Matrix4d::setColumn(int i,double x,double y,double z,double w) {
    int i4=i*4;
    m[i4]=x;m[i4+1]=y;m[i4+2]=z;m[i4+3]=w;
}

void Matrix4d::invert(const Matrix4d &a) {


  Matrix4d temp;
  temp.set(a);
  this->setIdentity();

  double t,t2;
  int i,j,k;
  int swap;

  // descente
  for(i=0;i<4;i++) {
    double max=temp[i*4+i];
    swap=i;
    for(j=(i+1);j<4;j++) {
        if (fabs(temp[j*4+i])>fabs(max)) {
            max=temp[j*4+i];
            swap=j;
        }
    }
    if (fabs(max)<1e-08) throw Error("matrice inverse",__LINE__,__FILE__);
    if (swap!=i) {
        temp.swapColumn(i,swap);
        this->swapColumn(i,swap);
    }
    t=temp[i*4+i];

    this->scaleColumn(i,1.0/t);
    temp.scaleColumn(i,1.0/t);
    for(k=i+1;k<4;k++) {
        t2=temp[k*4+i];
        this->subScaleColumn(k,i,t2);
        temp.subScaleColumn(k,i,t2);
    }
  }

  // remont�e
  for(i=3;i>=0;i--) {
    for(k=i-1;k>=0;k--) {
        t2=temp[i+k*4];
        this->subScaleColumn(k,i,t2);
        temp.subScaleColumn(k,i,t2);
    }
  }




}


const float *Matrix4d::fv() const {
    for(int i=0;i<16;i++) {
        mf[i]=m[i];
    }
    return mf;
}

void Matrix4d::set(const Quaternion &q) {
  double x=q.getX(),y=q.getY(),z=q.getZ(),w=q.getW();
  double x2=x*x,y2=y*y,z2=z*z,w2=w*w;
  double xy=2.0*x*y,xz=2.0*x*z,xw=2.0*x*w,yz=2.0*y*z,yw=2.0*y*w,zw=2.0*z*w;
  this->setColumn(0,w2+x2-y2-z2,xy+zw,xz-yw,0);
  this->setColumn(1,xy-zw,w2-x2+y2-z2,yz+xw,0);
  this->setColumn(2,xz+yw,yz-xw,w2-x2-y2+z2,0);
  this->setColumn(3,0,0,0,1);
}

void Matrix4d::setRotation(const Vector3d &v1,const Vector3d &v2) {
    Quaternion q;
    q.set(v1,v2);
    this->set(q);
}

void Matrix4d::setRotation(float angle,const Vector3d &axis) {
    Quaternion q;
    q.setFromAngleAxis(angle,axis);
    this->set(q);
}

void Matrix4d::setRotationDegree(float angle,const Vector3d &axis) {
    Quaternion q;
    q.setFromAngleAxis(angle*180.0/M_PI,axis);
    this->set(q);
}

void Matrix4d::setScale(double kx,double ky,double kz) {
	setRow(0,kx,0,0,0);
	setRow(1,0,ky,0,0);
	setRow(2,0,0,kz,0);
	setRow(3,0,0,0,1);
}

void Matrix4d::setTranslation(const Vector3d &t) {
    setRow(0,1,0,0,t.getX());
    setRow(1,0,1,0,t.getY());
    setRow(2,0,0,1,t.getZ());
    setRow(3,0,0,0,1);
}

void Matrix4d::setProjectionPlan(const Plan &p,const Vector3d &u) {
    double un=u.dot(p.getN());
    double an=p.getA().dot(p.getN());
    Vector3d n=p.getN();
    setRow(0,un-n.getX()*u.getX(),-n.getY()*u.getX(),-n.getZ()*u.getX(),an*u.getX());
    setRow(1,-n.getX()*u.getY(),un-n.getY()*u.getY(),-n.getZ()*u.getY(),an*u.getY());
    setRow(2,-n.getX()*u.getZ(),-n.getY()*u.getZ(),un-n.getZ()*u.getZ(),an*u.getZ());
    setRow(3,0,0,0,un);
}

void Matrix4d::setProjectionPlan(const Plan &p,const Point3d &u) {
    double lan=(p.getA()-u).dot(p.getN());
    double an=p.getA().dot(p.getN());
    double un=u.dot(p.getN());
    Vector3d n=p.getN();
    setRow(0,lan+n.getX()*u.getX(),n.getY()*u.getX(),n.getZ()*u.getX(),-an*u.getX());
    setRow(1,n.getX()*u.getY(),lan+n.getY()*u.getY(),n.getZ()*u.getY(),-an*u.getY());
    setRow(2,n.getX()*u.getZ(),n.getY()*u.getZ(),lan+n.getZ()*u.getZ(),-an*u.getZ());
    setRow(3,n.getX(),n.getY(),n.getZ(),-un);
}

Point4d Matrix4d::getRow(unsigned int i) {
	Point4d res(m[i],m[i+4],m[i+8],m[i+12]);
	return res;
}

