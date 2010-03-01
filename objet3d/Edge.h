#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include "Feature.h"
#include "Vertex.h"

/**
@file
@author F. Aubert
@brief Opérations sur les arêtes (lien entre 2 sommets)
*/
namespace prog3d {

/**
@class Edge
@brief représentation d'une arête (contient 2 références aux sommets).
*/
class Edge:public Feature {

	/// références sur les deux sommets de l'arête
	Vertex *a,*b;
    public:
    /// constructeur par défaut
	Edge();
	/// construction en affectant les deux références de sommets avec aa et bb
	Edge(Vertex *aa,Vertex *bb);

	/// donne la référence du premier sommet
	Vertex* getA() const;
	/// donne la référence du second sommet
	Vertex* getB() const;
	/// affecte la référence du premier sommet
	void setA(Vertex *aa);
	/// affecte la référence du second sommet
	void setB(Vertex *bb);
	/// affecte les deux références de sommet
	void setAB(Vertex *aa,Vertex *bb);
	/// trace le segment de l'arête
    void draw();
	/// donne la distance entre le segment de l'arête et le point aa
	double distance2(const Point3d &aa);
	/// donne le carré de la longueur de l'arête
	double length2();
	/// destructeur
	~Edge();
};

/**
@class VEdge
@brief tableau de références d'arête
*/
class VEdge:public std::vector<Edge *> {
    public:
    void draw();
};

typedef VEdge::iterator ItVEdge;

}

#endif // EDGE_H_INCLUDED
