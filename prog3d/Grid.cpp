#include "Grid.h"
#include "Segment.h"
#include <GL/gl.h>
/*


 F. Aubert

*/
using namespace prog3d;
using namespace std;

Grid::~Grid() {
}

Grid::Grid() {
    nbU=0;
    nbV=0;
    p.clear();
}

VPoint3d *Grid::getVPoint3d() {
    return &p;
}

/*
Point3d* Grid::operator()(int i,int j) {
    return p[i+j*nbU];
}
*/

Point3d* Grid::getPoint(unsigned int i,unsigned int j) {
    return p[i+j*nbU];
}

int Grid::getNbU() {
    return nbU;
}

int Grid::getNbV() {
    return nbV;
}

Vector3d* Grid::getNormal(unsigned int i,unsigned int j) {
    return n[i+j*nbU];
}

Point3d Grid::point(unsigned int i,unsigned int j) {
    return *(getPoint(i,j));
}

Vector3d Grid::normal(unsigned int i, unsigned int j) {
    return *(getNormal(i,j));
}

void Grid::setPoint(unsigned int i,unsigned int j,const Point3d &p) {
    *(getPoint(i,j))=p;
}

void Grid::setNormal(unsigned int i,unsigned int j,const Vector3d &n) {
    *(getNormal(i,j))=n;
}

void Grid::init(const Point3d &p1,const Point3d &p2,const Point3d &p3,const Point3d &p4) {
  p.push_back(new Point3d(p1));
  p.push_back(new Point3d(p2));
  p.push_back(new Point3d(p3));
  p.push_back(new Point3d(p4));
  nbU=2;nbV=2;
}

void Grid::init(int nu,int nv,float lu,float lv) {
    p.clean();
    n.clean();
    Point3d a;
    Vector3d v;
    float pasu=lu/(nu-1);
    float xu=-lu/2.0;float yu=-lv/2.0;
    float pasv=lv/(nv-1);
    for(int i=0;i<nu;i++) {
        for(int j=0;j<nv;j++) {
          a.set(xu,yu,0);
          v.set(0,0,1);
          p.push_back(new Point3d(a));
          n.push_back(new Vector3d(v));
          yu+=pasv;
        }
        xu+=pasu;
        yu=-lv/2.0;
    }
    nbU=nu;
    nbV=nv;
}

void Grid::insertVMiddle(int v) {
  APoint3d lineV;
  for(int i=0;i<nbU;i++) {
    Segment ab(point(i,v),point(i,v+1));
    lineV.push_back(ab.interp(0.5));
  }
  for(int i=0;i<nbU;i++) {
    ItVPoint3d iInsert = p.begin()+(v+1)*nbU;
      p.insert(iInsert,new Point3d(lineV[nbU-i-1]));
  }
  nbV++;
}

void Grid::insertUMiddle(int u) {
  APoint3d lineU;
  for(int j=0;j<nbV;j++) {
    Segment ab(point(u,j),point(u+1,j));
    lineU.push_back(ab.interp(0.5));
  }
  for(int j=0;j<nbV;j++) {
    ItVPoint3d iInsert = p.begin()+(u+1)+j*(nbU+1);
    p.insert(iInsert,new Point3d(lineU[j]));
  }
  nbU++;
}

void Grid::drawU(int u1,int u2) {
    glBegin(GL_QUAD_STRIP);
    for(int j=0;j<getNbV();j++) {
        glVertex3fv(getPoint(u1,j)->fv());
        glVertex3fv(getPoint(u2,j)->fv());
    }
    glEnd();
}

void Grid::drawNormal(float k) {
    for(int i=0;i<getNbU();i++) {
        for(int j=0;j<getNbV();j++) {
            point(i,j).drawTo(point(i,j)+k*normal(i,j));
        }
    }
}



