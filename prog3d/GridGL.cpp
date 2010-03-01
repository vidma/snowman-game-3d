#include "GridGL.h"
#include "UtilGL.h"
#include <iostream>
#include "Point4d.h"
#include "Plan.h"

/*


 F. Aubert

*/
using namespace std;
using namespace prog3d;

GridGL::~GridGL() {
}

GridGL::GridGL() {
    g=NULL;
}

void GridGL::setGrid(Grid *g) {
    this->g=g;
    this->setVPoint3d(g->getVPoint3d());
}



double GridGL::distance2SegV(const Point2d &m,int i,int j) {
    Point4d p1,p2;
    p1=getView()->applyLocalWindow(m,-0.99);
    p2=getView()->applyLocalWindow(m,0.99);
    Point3d pk1,pk2;
    pk1.project(p1);
    pk2.project(p2);
    Plan pl;
    pl.set(g->point(i+1,j),g->point(i,j),g->point(i,j+1));
    Point3d mpr;
    mpr=pl.project(pk1,pk2-pk1);
    UtilGL::add(mpr,"");
    Point3d a,b;
    a=g->point(i,j);b=g->point(i,j+1);
    Segment ab(a,b);
    return ab.distance2(mpr);
}

double GridGL::distance2SegU(const Point2d &m,int i,int j) {
    Point4d p1,p2;
    p1=getView()->applyLocalWindow(m,-0.99);
    p2=getView()->applyLocalWindow(m,0.99);
    Point3d pk1,pk2;
    pk1.project(p1);
    pk2.project(p2);
    Plan pl;
    pl.set(g->point(i+1,j),g->point(i,j),g->point(i,j+1));
    Point3d mpr;
    mpr=pl.project(pk1,pk2-pk1);
    UtilGL::add(mpr,"");
    Point3d a,b;
    a=g->point(i,j);b=g->point(i+1,j);
    Segment ab(a,b);
    return ab.distance2(mpr);
}

int GridGL::nearestSegmentV(const Point2d &m) {
    int res=0;

    double d_min=distance2SegV(m,0,0);
    double d;
    int i,j;
    for(i=0;i<g->getNbU()-1;i++) {
        for(j=0;j<g->getNbV()-1;j++) {
        d=distance2SegV(m,i,j);
        if (d<d_min) {
            res=j;d_min=d;
        }
        }
    }
    return res;
}

int GridGL::nearestSegmentU(const Point2d &m) {
    int res=0;

    double d_min=distance2SegU(m,0,0);
    double d;
    int i,j;
    for(i=0;i<g->getNbU()-1;i++) {
        for(j=0;j<g->getNbV()-1;j++) {
        d=distance2SegU(m,i,j);
        if (d<d_min) {
            res=i;d_min=d;
        }
        }
    }
    return res;
}



void GridGL::insertNearestV(const Point2d &m) {
    int v=this->nearestSegmentV(m);
    g->insertVMiddle(v);
}


void GridGL::insertNearestU(const Point2d &m) {
    int u=this->nearestSegmentU(m);
    g->insertUMiddle(u);
}
