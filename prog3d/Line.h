#ifndef DROITE_H_INCLUDED
#define DROITE_H_INCLUDED

#include "Point3d.h"
#include "Vector3d.h"
#include <string>
#include <ostream>

/*!
*
* @file
*
* @brief opérations sur les droites \f$P=A+\lambda u\f$
* @author F. Aubert
*
*/

namespace prog3d {
/**
@class Line
@brief représentation d'une droite \f$P=A+\lambda u\f$
*/
class Line {
	Vector3d u; ///< un vecteur directeur
	Point3d a; ///< un point

	public:

    /// destructeur
    ~Line();
    /// constructeur par défaut
    Line();
    /// construction Line(point,vecteur)
	Line(const Point3d &aa,const Vector3d &uu);
	/// construction Line(point,point)
	Line(const Point3d &aa,const Point3d &bb);

    /// donne le point initial
	Point3d getA() const;
	/// donne le vecteur directeur
	Vector3d getU() const;

    /// donne le point de la droite a+ku
    Point3d point(double k) const;

    /// affecte le point initial
	void setA(const Point3d &aa);
	/// affecte le vecteur directeur
	void setU(const Vector3d &uu);

    /// affecte le point et le vecteur
	void set(const Point3d &aa,const Vector3d &uu);
	/// affecte le point=aa et le vecteur=(bb-aa)
	void set(const Point3d &aa,const Point3d &bb);
    /// donne le carré de la distance entre le point m et la droite. Ex : dist=d.distance2(m)
	double distance2(const Point3d &m);
    /// affiche sur la console la droite : mesg (A=(x,y,z),U=(ux,uy,uz))
	void print(std::string mesg) const;
	/// Ex : cout << droite << endl; (affiche (A=...,U=...))
	friend std::ostream& operator<<(std::ostream &s,const Line &l);


};
}

#endif // DROITE_H_INCLUDED
