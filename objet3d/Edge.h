#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include "Feature.h"
#include "Vertex.h"

/**
@file
@author F. Aubert
@brief Op�rations sur les ar�tes (lien entre 2 sommets)
*/
namespace prog3d {

/**
@class Edge
@brief repr�sentation d'une ar�te (contient 2 r�f�rences aux sommets).
*/
class Edge:public Feature {

	/// r�f�rences sur les deux sommets de l'ar�te
	Vertex *a,*b;
    public:
    /// constructeur par d�faut
	Edge();
	/// construction en affectant les deux r�f�rences de sommets avec aa et bb
	Edge(Vertex *aa,Vertex *bb);

	/// donne la r�f�rence du premier sommet
	Vertex* getA() const;
	/// donne la r�f�rence du second sommet
	Vertex* getB() const;
	/// affecte la r�f�rence du premier sommet
	void setA(Vertex *aa);
	/// affecte la r�f�rence du second sommet
	void setB(Vertex *bb);
	/// affecte les deux r�f�rences de sommet
	void setAB(Vertex *aa,Vertex *bb);
	/// trace le segment de l'ar�te
    void draw();
	/// donne la distance entre le segment de l'ar�te et le point aa
	double distance2(const Point3d &aa);
	/// donne le carr� de la longueur de l'ar�te
	double length2();
	/// destructeur
	~Edge();
};

/**
@class VEdge
@brief tableau de r�f�rences d'ar�te
*/
class VEdge:public std::vector<Edge *> {
    public:
    void draw();
};

typedef VEdge::iterator ItVEdge;

}

#endif // EDGE_H_INCLUDED
