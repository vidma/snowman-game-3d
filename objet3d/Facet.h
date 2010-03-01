#ifndef FACET_H_INCLUDED
#define FACET_H_INCLUDED

#include "Feature.h"
#include "Vector3d.h"
#include "Vertex.h"
#include <vector>

namespace prog3d {

/**
@file
@author F. Aubert
@brief Opérations sur les facettes
*/

typedef enum {NORMAL_FACE=0x1,NORMAL_VERTEX=0x0,DRAW_GRID=0x10,DRAW_FILL=0x100,DRAW_NO_GRID=0x00,DRAW_NO_FILL=0x000} EDrawFace;
typedef enum {MOINS,PLUS} ESigne;


/**
@class Facet
@brief Représentation d'une facette (liste de références sur sommet).
*/
class Facet : public Feature {
	/// ensemble des sommets
	VVertex vv;
	/// normale à la facette
	Vector3d n;
	/// ensemble des normales
	VVector3d vn;

	unsigned int drawMode;
	Point3d a;
public:
	/// constructeur par défaut
	Facet();

	Facet(const Point3d &a,const Vector3d &n);

	/// vacuité de la facette (vide si 0 sommet)
	bool isEmpty() const;

	/// création et adjonction du sommet construit à partir du point3d p
	Vertex *createVertex(const Point3d &p);

	/// mode d'affichage. Exemple : DRAW_GRID | DRAW_FILL
	void setDrawMode(unsigned int mode);

	/// nombre de sommets de la facette
	int nbVertex() const;

	/// calcul la normale au polygone
	void computeNormal();
	/// trace la facette (remplissage si line = false)
	void draw();
	///
	void drawNormal(float k);

	/// donne la normale à la facette
	const Vector3d &normal() const;

	/// affecte la normale à la facette (normale du polygone)
	void setNormal(const Vector3d &n);

	/// donne la normale au sommet i (référence)
	Vector3d *getNormal(int i) const;

	/// donne le sommet i (référence)
	Vertex *getVertex(unsigned int i) const;

	/// donne la valeur du Point3d du vertex i
	const Point3d &point(unsigned int i) const;

	const Vertex &vertex(unsigned int i) const;

	/// donne le tableau des sommets
	VVertex &getAllVertex();
	/// ajoute un sommet au tableau des sommets
	void addVertex(Vertex *v);
	/// ajoute une normale au tableau des normales
	void addNormal(Vector3d *n);

	/// enleve un sommet de la face
	void erase(ItVVertex v);

	/// détruit les sommets et normales (prudence : delete)
	void clean();
	/// remet à zéro les sommets (la facette ne détruira pas ses vertices)
	void clearVVertex();
	/// remet à zéro les normales (la facette ne détruira pas ses normales)
	void clearVNormal();

	/// remet à zéro les tableaux sommets et normales
	void clear();

	/// donne l'itérateur correspondant au premier sommet
	ItVVertex vertexBegin();
	/// donne l'itérateur correspondant au dernier sommet
	ItVVertex vertexEnd();

	/// donne le signe du point p par rapport à la facette
	ESigne signe(const Point3d &p) const;
	/// donne le signe du sommet v par rapport à la facette
	ESigne signe(Vertex *v) const;

	/// donne le point d'intersection entre la droite (p1p2) et le plan de la facette
	Point3d intersection(const Point3d &p1,const Point3d &p2) const;
	/// coupe la facette en deux par rapport à f1 (CU : moins et plus doivent être créées avant appel; la facette instance doit être convexe)
	void cut(const Facet &f1,Facet *moins,Facet *plus) const;

	/// print
	void print(const std::string &mesg);

	/// triangule (sommet par sommet). CU : doit être convexe pour un résultat correct
	void triangulate();

	~Facet();
};

/**
@class VFacet
@brief représentation d'une tableau de références de facette
*/


class VFacet:public VCollection<Facet> {
	unsigned int drawMode;
    public:
    /// calcule toutes les normales aux facettes
    void computeNormal();
    ///
    void setDrawMode(unsigned int mode);
    /// trace toutes les facettes
    void draw();
    void drawNormal(float k);
};

typedef VFacet::iterator ItVFacet;

/**
@class AFacet
@brief représentation d'un tableau de facettes
*/
class AFacet:public ACollection<Facet> {
	public:
	void addEndValidate(Facet *f);
};

typedef AFacet::iterator ItAFacet;


}




#endif // FACET_H_INCLUDED
