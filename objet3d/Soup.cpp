#include "Soup.h"
#include <GL/gl.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include "ParserOBJ.h"


using namespace std;
using namespace prog3d;


Soup::~Soup() {
    ItVFacet it;
    int i=0;
    for(it=vf.begin();it!=vf.end();it++) {
//    	cout << "clear " << i << endl;
        (*it)->clearVVertex();
        (*it)->clearVNormal();
        i++;
    }
//    cout << "end clearing" << endl;
}

void Soup::eraseFacet(Facet *f) {
	ItVFacet i;
	i=find(vf.begin(),vf.end(),f);
	eraseFacet(i);
}

void Soup::eraseFacet(ItVFacet i) {
	(*i)->clearVVertex();
	(*i)->clearVNormal();
	delete (*i);
	vf.erase(i);
}

void Soup::eraseFacet(int i) {
	eraseFacet(vf.begin()+i);
}

Soup::Soup() {
	drawMode=DRAW_FILL;
}

void Soup::triangulate() {
    int fin=vf.size();
    for(int i=0;i<fin;i++) {
        vf[i]->triangulate();
    }
}


Vertex *Soup::createVertex() {
	Vertex *res=new Vertex();
	addVertex(res);
	res->setCreator(this);
	return res;
}

Vertex *Soup::createVertex(const Point3d &p) {
	Vertex *res=createVertex();
	res->setPoint(p);
	return res;
}

Facet *Soup::createFacet() {
	Facet *res=new Facet();
	addFacet(res);
	res->setCreator(this);
	return res;
}


void Soup::setDrawMode(unsigned int mode) {
	drawMode=mode;
}

void Soup::draw() {
  vf.setDrawMode(drawMode);
  vf.draw();
}

const VFacet &Soup::getAllFacet() const {
    return vf;
}

VVertex Soup::getAllVertex() const {
    return vv;
}

Facet *Soup::getFacet(unsigned int i) {
	return vf[i];
}

void Soup::extract(VPoint3d &liste) {
    for(ItVVertex i=vv.begin();i!=vv.end();i++) {
        liste.push_back(&(*i)->getPoint());
    }
}

void Soup::setNumber() {
    int index=0;
    for(ItVVertex i=vv.begin();i!=vv.end();i++) {
        (*i)->setNumber(index);
        index++;
    }
}

Vertex *Soup::getVertex(int i) {
    return vv[i];
}

Vector3d *Soup::getNormal(int i) {
    return vn[i];
}

void Soup::addVertex(Vertex *v) {
    vv.push_back(v);
}

void Soup::addNormal(Vector3d *n) {
    vn.push_back(n);
}

void Soup::addFacet(Facet *f) {
    vf.push_back(f);
}

int Soup::nbFacet() {
	return vf.size();
}


void Soup::dilate(float k) {
  ItVVertex ita;
  for(ita=vv.begin();ita!=vv.end();ita++) {
    Point3d p=(*ita)->normal();
    p.scaleAdd(k,(*ita)->point());
    (*ita)->setPoint(p);
  }
}


bool minx(Vertex *p1, Vertex *p2) {
  return p1->point().getX()<p2->point().getX();
}


float Soup::minBox(int coord) {
  ItVVertex ita;
  ita=min_element(vv.begin(),vv.end(),minx);
  return (*ita)->point().getX();
}

float Soup::maxBox(int coord) {
  ItVVertex ita;
  ita=max_element(vv.begin(),vv.end(),minx);
  return (*ita)->point().getX();
}

void Soup::adaptBox(float x1,float x2,float y1,float y2, float z1, float z2) {
  float min_x=minBox(0);
  float max_x=maxBox(0);
  this->translate(-(min_x+max_x)/2.0,0,0);
  float kscale=(x2-x1)/(max_x-min_x);
  this->scale(kscale);
  this->translate((x1+x2)/2.0,0,0);
}

void Soup::drawNormal() {
  ItVVertex ita;
  Point3d pp;
  for(ita=vv.begin();ita!=vv.end();ita++) {
    glBegin(GL_LINES);
      glVertex3dv((*ita)->point().dv());
      pp.set((*ita)->normal());
      pp.scaleAdd(0.1,(*ita)->point());
      glVertex3fv(pp.fv());
    glEnd();
  }
}

void Soup::scale(float k) {
  ItVVertex itv;
  for(itv=vv.begin();itv<vv.end();itv++) {
    (*itv)->scale(k);
  }
}

void Soup::scale(double kx,double ky,double kz) {
  ItVVertex itv;
  for(itv=vv.begin();itv<vv.end();itv++) {
    (*itv)->scale(kx,ky,kz);
  }
}

void Soup::translate(float x,float y, float z) {
  ItVVertex itv;
  for(itv=vv.begin();itv<vv.end();itv++) {
    (*itv)->translate(x,y,z);
  }
}

void Soup::writeOBJ(string nom) {
    fstream f;
    f.open(nom.c_str(),fstream::out);
    ItVVertex itv;
    f << "#vertices : " << endl;

    int compte=0;
    for(itv=vv.begin();itv!=vv.end();itv++) {
        (*itv)->setNumber(compte);
        Point3d p=(*itv)->point();
        f << "v " << p.getX() << " " << p.getY() << " " << p.getZ() << endl;
        compte++;
    }
    f << "# number of vertices " << compte << endl;

    f << endl;
    f << "#facets" << endl;
    ItVFacet itf;
    int comptef=0;
    for(itf=vf.begin();itf!=vf.end();itf++) {
        Facet *a=*itf;
        ItVVertex itv;
        f << "f ";
        for (itv=a->vertexBegin();itv!=a->vertexEnd();itv++) {
            f << (*itv)->getNumber()+1 << " ";
        }
        f << endl;
        comptef++;
    }
    f << "# number of facets :" << comptef << endl;
    f.close();
}

void Soup::readOBJ(string nom) {
    ParserOBJ parse(nom);
    parse.load(this);
}

void Soup::computeVertexNormal() {
  ItVFacet itf;
  ItVVertex itv;

  vf.computeNormal();
  for(itv=vv.begin();itv!=vv.end();itv++) {
    (*itv)->averageNormalBegin();
  }
   for(itf=vf.begin();itf!=vf.end();itf++) {
     for(itv=(*itf)->vertexBegin();itv!=(*itf)->vertexEnd();itv++) {
       (*itv)->averageNormalAdd((*itf)->normal());
     }
   }
   for(itv=vv.begin();itv!=vv.end();itv++) {
//  printf("%f,%f,%f\n",(*ita)->n.x,(*ita)->n.y,(*ita)->n.z);
      (*itv)->averageNormalEnd();
   }
}

void Soup::opposeNormal() {
	for(unsigned int i=0;i<vv.size();i++) {
		vv[i]->setNormal(-(vv[i]->normal()));
	}
}

void Soup::print(const string &mesg) {
	cout << "Objet : " << mesg << endl;
	for(int i=0;i<nbFacet();i++) {
		Facet *f=getFacet(i);
		cout << "face = (";
		for(int j=0;j<f->nbVertex();j++) {
			cout << f->getVertex(j )->point();
		}
		cout << ")" << endl;
	}
}


