#include "Facet.h"
#include "Error.h"
#include <GL/gl.h>
#include <iostream>
#include "Soup.h"
#include "UtilGL.h"
#include <math.h>


using namespace std;
using namespace prog3d;


/** Tableau de facettes */
void VFacet::draw() {
  ItVFacet itf;
  if (drawMode & DRAW_GRID) {
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
  }
  for(itf=begin();itf!=end();itf++) {
  	(*itf)->setDrawMode(drawMode);
    (*itf)->draw();
  }
  if (drawMode & DRAW_GRID) {
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDisable(GL_LIGHTING);
    glColor3f(0.0,0.0,0.0);
    glLineWidth(2.0);
    for(itf=begin();itf!=end();itf++) {
      (*itf)->draw();
    }
    glLineWidth(1.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glPopAttrib();
  }
}

void VFacet::drawNormal(float k) {
	ItVFacet itf;
  for(itf=begin();itf!=end();itf++) {
    (*itf)->drawNormal(k);
  }
}

void VFacet::setDrawMode(unsigned int mode) {
	drawMode=mode;
}


void VFacet::computeNormal() {
   ItVFacet itf;
   for(itf=begin();itf!=end();itf++) {
     (*itf)->computeNormal();
   }
}


/** Les facettes */
Facet::~Facet() {
   vv.clear(); // !!!!! do not delete the vertices in vv (can be shared vertices)
}


void Facet::print(const string &mesg) {
	cout << "Facet " << mesg << " =(";
	for(int i=0;i<nbVertex();i++) {
		cout << vv[i]->point();
	}
	cout << ")" << endl;
}

void Facet::triangulate() {
    if (nbVertex()>3) {
        Vertex *s0=*(vertexBegin());
        ItVVertex i=vertexBegin()+2;
        Facet *f;
        do {
            f=creator()->createFacet();
            f->addVertex(s0);
            f->addVertex(*i);
            f->addVertex(*(i+1));
            i++;
        } while ((i+1)!=vertexEnd());
        vv.erase(vertexBegin()+3,vertexEnd());

    }
}

bool Facet::isEmpty() const {
	return (vv.size()==0);
}

int Facet::nbVertex() const {
	return vv.size();
}

void Facet::setNormal(const Vector3d &v) {
	n=v;
}

void Facet::setDrawMode(unsigned int mode) {
	drawMode=mode;
}

void Facet::clearVVertex() {
    vv.clear();
}

void Facet::clearVNormal() {
    vn.clear();
}

void Facet::clear() {
	vv.clear();
	vn.clear();
}

Facet::Facet() {
    vv.clear();
    vn.clear();
    drawMode = NORMAL_VERTEX | DRAW_FILL;
}


Facet::Facet(const Point3d &a,const Vector3d &n) {
    vv.clear();
    vn.clear();
    this->a=a;
    this->n=n;
    drawMode = NORMAL_VERTEX | DRAW_FILL;
}

Vertex *Facet::createVertex(const Point3d &p) {
	Vertex *v=new Vertex();
	v->setCreator(this->creator());
	v->setPoint(p);
	addVertex(v);
	return v;
}

ItVVertex Facet::vertexBegin() {
    return vv.begin();
}

ItVVertex Facet::vertexEnd() {
    return vv.end();
}

void Facet::addVertex(Vertex *v) {
    vv.push_back(v);
}

const Vector3d &Facet::normal() const {
    return n;
}

Vector3d *Facet::getNormal(int i) const {
    return vn[i];
}

Vertex *Facet::getVertex(unsigned int i) const {
	return vv[i];
}

const Point3d &Facet::point(unsigned int i) const {
	return vv[i]->point();
}

VVertex &Facet::getAllVertex() {
    return vv;
}

void Facet::addNormal(Vector3d *v) {
    vn.push_back(v);
}

void Facet::computeNormal() {
  Point3d s1;
  Point3d s2;
  Point3d s3;

  double dist=0;

  ItVVertex it1=vv.begin();
  ItVVertex it2=vv.begin()+1;
  ItVVertex it3=vv.begin()+2;
  bool stop=false;
  while ((dist<1e-05) && !stop) {
    if (it3!=vv.end()) {
        s1=(*(it1))->point();
        s2=(*(it2))->point();
        s3=(*(it3++))->point();
        Vector3d v1(s1,s2);
        Vector3d v2(s2,s3);
        n.wedge(v1,v2);
        dist=n.length();
        if (it3==vv.end()) {
            it2++;
            if (it2==vv.end()) {
                it1++;
                it2=it1+1;
            }
            it3=it2+1;
        }
    } else {
        stop=true;
        //throw Error("Normal problem",__LINE__,__FILE__);
    }
  }

  if (stop) n.set(0,0,0); else  n.scale(1.0/dist);
}


void Facet::draw() {
    ItVVertex itv;
    glBegin((drawMode & DRAW_FILL)?GL_POLYGON:GL_LINE_LOOP);
    int k=0;
    for(itv=vv.begin();itv!=vv.end();itv++) {
      Vertex *v=*itv;
      if (drawMode & NORMAL_FACE) {
      	glNormal3dv(n.dv());
      } else
      if (vn.size()!=0) {
        glNormal3dv(vn[k]->dv());
        k++;
      }
      else {
        glNormal3dv(v->normal().dv());
      }
      glVertex3dv(v->point().dv());
     }
     glEnd();
}


const Vertex &Facet::vertex(unsigned int i) const {
	return *(vv[i]);
}

void Facet::drawNormal(float c) {
    ItVVertex itv;
    int k=0;
    for(itv=vv.begin();itv!=vv.end();itv++) {
      Vertex *v=*itv;
      Point3d p=v->point();
      Vector3d u;
      if (drawMode & NORMAL_FACE) {
      	u=n;
      } else
      if (vn.size()!=0) {
        u=*vn[k];
        k++;
      }
      else {
        u=v->normal();
      }
      v->point().drawTo(p+c*u);
     }

}

ESigne Facet::signe(Vertex *v) const {
	return signe(v->point());
}


void Facet::erase(ItVVertex v) {
	vv.erase(v);
}


/// un peu pas clair : ajoute la facette non vide en éliminant les arêtes trop petites
void AFacet::addEndValidate(Facet *f) {
	if (!f->isEmpty()) {
	ItVVertex new_s=f->vertexBegin()+1;
	ItVVertex old_s=f->vertexBegin();
	Vector3d u;
	while (new_s!=f->vertexEnd()) {
		u.setVector((*old_s)->point(),(*(new_s))->point());
		if (u.length2()<1e-5) {f->erase(new_s);}
		else old_s++;
		new_s=old_s+1;
	}
	old_s=f->vertexEnd()-1;
	new_s=f->vertexBegin();
	u.setVector((*old_s)->point(),(*(new_s))->point());
	if (u.length2()<1e-5) {f->erase(new_s);}

	if (f->nbVertex()>2) {
		addEnd(*f);
	}
	}
}


ESigne Facet::signe(const Point3d &p) const {
	/// méthodes utiles :
	/// - point(0) : vous donnera un point de la face
	/// - normal() : vous donnera la normale à la face
	/// - v1.dot(v2) : produit scalaire entre 2 Vector3d (ou Point3d)
	/// - Vector3d v(p1,p2) ou v.setVector(p1,p2) : construit v par p2-p1


	ESigne res=MOINS;


	return res;
}


/// Donne le point d'intersection
Point3d Facet::intersection(const Point3d &p1,const Point3d &p2) const {
	/// il suffit de résoudre AI.n=0 (plan (A,n)) et I=p1+k*p1p2 (droite (p1,p2))
	/// - point(0) : vous donne le Point3d de la facette
	/// - normal() : vous donne la normale de la facette
	/// - on peut utiliser les opérateurs sur les Point3d et Vector3d. Exemple : p=a+k*u (avec a,p:Point3d et u:Vector3d)
	/// - u.setVector(p1,p2) : u= le vecteur p1p2
	/// - u1.dot(u2) : produit scalaire
	Point3d res;
/*
*/
	return res;
}


/// coupe la facette selon f1
void Facet::cut(const Facet &f1,Facet *moins,Facet *plus) const {
	/// nbVertex() : nombre de sommets
	/// v=getVertex(i) : donne le sommet numéro i (pointeur), i dans [0..nbVertex()-1]
	/// v->point() : donne le Point3d du sommet v
	/// la création d'un nouveau sommet (sommet d'intersection) se fera par v=new Vertex(un Point3d)  (memory leak, mais tant pis pour simplifier)
	/// moins->addVertex(v) : ajoute le sommet v (pointeur) à la facette moins

	plus->clear();moins->clear(); // initialisation à vide
/*
	ESigne sgn_old,sgn_new;
	Vertex *s_old,*s_new;
	Point3d p_inter;
*/




	moins->setNormal(normal());plus->setNormal(normal()); // les normales sont les mêmes que la normale de la facette coupée (évite de recalculer et les erreurs numériques)
}


