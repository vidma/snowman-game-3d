#ifndef SOUP_H_INCLUDED
#define SOUP_H_INCLUDED

#include "Facet.h"
#include "Vertex.h"

/**
@file
@author F. Aubert
@brief Opération sur les soupes de polygones
*/

namespace prog3d {

/**
@class Soup
@brief Représentation des polyèdres par un ensemble de sommets et ensemble de facettes
*/
class Soup {

	/// ensemble des facettes
  VFacet vf;
	/// ensemble des sommets
  VVertex vv;
	/// ensemble des normales aux sommets
  VVector3d vn;

  unsigned int drawMode;

public:

  void eraseFacet(int i);
  void eraseFacet(Facet *f);
  void eraseFacet(ItVFacet i);


  Soup();
  void setDrawMode(unsigned int mode);
  void draw();
  void dilate(float k);
  void drawNormal();
  float minBox(int coord);
  float maxBox(int coord);

  void setNumber();

  void extract(VPoint3d &liste);

  void adaptBox(float x1,float x2, float y1, float y2, float z1, float z2);

  Vertex *getVertex(int i);
  Vector3d *getNormal(int i);

	Vertex *createVertex();
	Vertex *createVertex(const Point3d &p);
	Facet *createFacet();

  const VFacet &getAllFacet() const;
  VVertex getAllVertex() const;

  Facet *getFacet(unsigned int i);

  int nbFacet();

  void addFacet(Facet* f);
  void addVertex(Vertex *v);
  void addNormal(Vector3d *n);

	void print(const std::string &mesg);

  void translate(float x,float y,float z);
  void scale(float k);
  void scale(double kx,double ky,double kz);

  void writeOBJ(std::string nom);
  void readOBJ(std::string nom);

  void computeVertexNormal();
  void opposeNormal();

  /// triangule les facettes.
  void triangulate();

  ~Soup();
};


}

#endif // SOUP_H_INCLUDED
