#include "Edge.h"
#include "Segment.h"
#include <GL/gl.h>
using namespace prog3d;


Edge::~Edge() {
    // NON GERE ENCORE : memory leak inside (ne pas delete bourrinement le a et le b car grande chance d'être partagés)
}

Edge::Edge() {
}

Edge::Edge(Vertex *aa,Vertex *bb) {
		a=aa;b=bb;
}

Vertex* Edge::getA() const { return a;}
Vertex* Edge::getB() const { return b;}
void Edge::setA(Vertex *aa) { a=aa;}
void Edge::setB(Vertex *bb) { b=bb;}
void Edge::setAB(Vertex *aa,Vertex *bb) { a=aa;b=bb;}

double Edge::distance2(const Point3d &aa) {
    Segment s(a->point(),b->point());
    return s.distance2(aa);
}

double Edge::length2() {
    Vector3d u(a->point(),b->point());
    return u.length2();
}

void Edge::draw() {
    glBegin(GL_LINES);
    glVertex3dv(getA()->point().dv());
    glVertex3dv(getB()->point().dv());
    glEnd();

}


void VEdge::draw() {
    glBegin(GL_LINES);
    for(ItVEdge i=begin();i!=end();i++) {
        glVertex3dv((*i)->getA()->point().dv());
        glVertex3dv((*i)->getB()->point().dv());
    }
    glEnd();
}
