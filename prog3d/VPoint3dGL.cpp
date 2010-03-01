#include "VPoint3dGL.h"
#include "ViewportUtil.h"
//#include "Edge.h"
#include "Segment.h"
#include "Point3d.h"
#include "Vector3d.h"
#include <algorithm>
#include <GL/gl.h>
#include <iostream>

/*
You have to initialize the view (transformation from local/eye/window...) by calling setView() from an OpenGL display
process (it sets the view from the current MODELVIEW and PROJECTION matrices)



Fabrice Aubert
*/


using namespace std;
using namespace prog3d;

VPoint3dGL::~VPoint3dGL() {
    delete view;
    l_inde.clear();
//    cout << "ok VPoint3dGL" << endl;
}

VPoint3dGL::VPoint3dGL() {
    view=new ViewportUtil();
    selectedPoint3d=NULL;
    l_inde.clear();
    l=&l_inde;
}


void VPoint3dGL::setVPoint3d(VPoint3d *v) {
    l=v;
}

ViewportUtil *VPoint3dGL::getView() {
    return view;
}


ItVPoint3d VPoint3dGL::indexOf(Point3d *p) {
    return find(l->begin(),l->end(),p);
}

void VPoint3dGL::setView() {
    view->setView();
}

void VPoint3dGL::clear() {
    l->clear();
}

void VPoint3dGL::backup() {
    l_backup.clear();
    for(ItVPoint3d i=l->begin();i!=l->end();i++) {
        l_backup.push_back(*(*i));
    }
}

int VPoint3dGL::size() {
    return l->size();
}

Point3d *VPoint3dGL::get(int i) {
    return (*l)[i];
}

void VPoint3dGL::restore() {
    vector<Point3d>::iterator j;
    j=l_backup.begin();
    for(ItVPoint3d i=l->begin();i!=l->end();i++,j++) {
        (*i)->set(*j);
    }
}


void VPoint3dGL::add(Point3d *p) {
		l->push_back(p);
}

void VPoint3dGL::addAll(VPoint3d &liste) {
    for(ItVPoint3d i=liste.begin();i!=liste.end();i++) {
        this->add((*i));
    }
}

void VPoint3dGL::add(const Point2d &mouse) {
    if (size()>1) {
		Point2d a=view->windowCoordinate(*(*l)[0]);
		double d=mouse.distance2(a);
		a=view->windowCoordinate(*(*l)[l->size()-1]);
		int i;
		if (mouse.distance2(a)<d) i=l->size(); else i=0;
		Point3d pointSouris=view->applyLocalWindow(mouse,*(*l)[l->size()-1]);
		ItVPoint3d it=l->begin();
		l->insert(it+i,new Point3d(pointSouris));
    } else {
        addEnd(mouse);
    }
}

void VPoint3dGL::addEnd(const Point2d &mouse) {
  		Point3d pointSouris=view->applyLocalWindow(mouse,-1.0);
		l->push_back(new Point3d(pointSouris));

}

void VPoint3dGL::insert(const Point2d &mouse,Point3d *p) {
		ItVPoint3d i=find(l->begin(),l->end(),p);
		Point3d pointSouris=view->applyLocalWindow(mouse,*p);
		l->insert(i+1,new Point3d(pointSouris));
}

void VPoint3dGL::erase(Point3d *p) {
		ItVPoint3d i=find(l->begin(),l->end(),p);
		l->erase(i);
		delete p;
}


void VPoint3dGL::insert(Point2d mouse,Point3d *a,Point3d *b) {
		ItVPoint3d ia=find(l->begin(),l->end(),a);
		ItVPoint3d ib=find(l->begin(),l->end(),b);
		ItVPoint3d i;
		if (ia>ib) i=ia; else i=ib;


		// compute an approximative (no perspective correction) depth for the inserted point (from the computation of the projected point mouse onto the edge in 2d)
		Point2d a2d(view->windowCoordinate(*a));
		Point2d b2d(view->windowCoordinate(*b));
		Vector2d u(b2d);
		u.sub(a2d);
		Vector2d am(mouse);
		am.sub(a2d);

		double lambda=am.dot(u)/u.dot(u);

		Point3d ref(*b);
		ref.sub(*a);
		ref.scaleAdd(lambda,*a);


		Point3d pointSouris=view->applyLocalWindow(mouse,ref);
		l->insert(i,new Point3d(pointSouris));
	}


void VPoint3dGL::insertNearest(const Point2d &mouse) {
        if (l->size()<2) add(mouse);
        else {
            Point3d *a,*b;
            nearestSegment(mouse,&a,&b);
            Point3d extreme1=*a;
            Point3d pointSouris(view->applyLocalWindow(mouse, extreme1));

            ItVPoint3d i=indexOf(a);
            l->insert(i+1,new Point3d(pointSouris));
        }

}

void VPoint3dGL::draw() {
		glColor3f(0,0,1);
		glBegin(GL_LINE_STRIP);
		for(ItVPoint3d a=l->begin();a!=l->end();a++) {
		  glVertex3dv((*a)->getDv());
		}
		glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
		for(ItVPoint3d a=l->begin();a!=l->end();a++) {
		  glVertex3dv((*a)->getDv());
//		  (*a)->print("Point = ");
		}
		glEnd();
		glPointSize(1);
}



void VPoint3dGL::nearestSegment(const Point2d &m,Point3d **aa,Point3d **bb) {
		Point3d *a;
		Point3d *b;
		ItVPoint3d it=l->begin();
		a=*(it++);
		b=*(it++);
		*aa=a;*bb=b;
		Point2d pA=view->windowCoordinate(*a);
		Point2d pB=view->windowCoordinate(*b);
		Segment ab(pA,pB);
		double dMin=ab.distance2(m);
		while (it!=l->end()) {
			a=b;b=*(it++);
			pA=pB;
			pB=view->windowCoordinate(*b);
			ab.setAB(pA,pB);
			double d=ab.distance2(m);
			if (d<dMin) {
				dMin=d;
				*aa=a;
				*bb=b;
			}
		}

}


Point3d* VPoint3dGL::nearestPoint(const Point2d &m) {
		Point3d *proche;
		Point2d pproche;
		ItVPoint3d it=l->begin();
		int index=0;
		int indexMin=0;
		proche=*(it++);
		pproche=view->windowCoordinate(*proche);
		double dMin=m.distance2(pproche);
		while (it!=l->end()) {
		    index++;
			Point3d *a=*(it++);
			pproche=view->windowCoordinate(*a);
			double d=m.distance2(pproche);
			if (d<dMin) {
			    indexMin=index;
				dMin=d;
				proche=a;
			}
		}
		return proche;
}


void VPoint3dGL::controlMouse(Point3d *p,const Point2d &m) {
        Point3d a;
        a.set(view->applyLocalWindow(m, *p));
		p->set(a);
}

void VPoint3dGL::startMouse(const Point2d &m) {
    Point3d *nearest;
    nearest=nearestPoint(m);
    startingMouse.set(view->applyLocalWindow(m,*nearest));
}

void VPoint3dGL::controlTranslate(const Point2d &m) {
//        if (!startingMouse) throw Error("no startingMouse (call startMouse in the mouse pressed callback)",__LINE__,__FILE__);
        Point3d where;
        where.set(view->applyLocalWindow(m,startingMouse));
        Vector3d t;
        t.setVector(startingMouse,where);
        restore();
        for(ItVPoint3d i=l->begin();i!=l->end();i++) {
            (*i)->translate(t.getX(),t.getY(),t.getZ());
        }
}

void VPoint3dGL::controlScale(const Point2d &m) {
//        if (!startingMouse) throw Error("no startingMouse (call startMouse in the mouse pressed callback)",__LINE__,__FILE__);
        Point3d where;
        where.set(view->applyLocalWindow(m,startingMouse));
        Vector3d t;
        restore();
//        startingMouse.print();
//        where.print();
        t.set(where.getX()/startingMouse.getX(),where.getY()/startingMouse.getY(),where.getZ()/startingMouse.getZ());
//        t.sVector(startingMouse,where);
//        t.scaleAdd(0.1,Vector3d(1,1,1));
        for(ItVPoint3d i=l->begin();i!=l->end();i++) {
            (*i)->scale(t.getX(),t.getY(),t.getZ());
        }
}


void VPoint3dGL::selectNearest(const Point2d &m) {
    if (l->size()==0) selectedPoint3d=NULL; else
    selectedPoint3d=nearestPoint(m);
}

void VPoint3dGL::controlSelected(const Point2d &m) {
    if (selectedPoint3d)
        controlMouse(selectedPoint3d,m);
}


