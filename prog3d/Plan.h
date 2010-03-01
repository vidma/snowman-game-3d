#ifndef PLAN_H_INCLUDED
#define PLAN_H_INCLUDED

#include "Point3d.h"
#include "Vector3d.h"
#include "Line.h"
/*!
*
* @file
*
* @brief opérations sur les plans am.n=0
* @author F. Aubert
*
*/

namespace prog3d {
/**
@class Plan
@brief représentation des plans am.n=0
*/
class Plan {
    Vector3d n; ///< vecteur normal
    Point3d a;  ///< point du plan

    public:
    /// destructeur
    ~Plan();
    /// constructeur par défaut
    Plan();
    /// constructeur par Plan(a,n)
    Plan(const Point3d &a,const Vector3d &n);

    /// affectation du point et de la normale du plan
    void set(const Point3d &a,const Vector3d &n);
    /// affectation en définissant le plan par 3 points
    void set(const Point3d &p1,const Point3d &p2,const Point3d &p3);
    /// donne la projection orthogonale de p sur le plan
    Point3d project(const Point3d &p);
    /// donne la projection suivant u de p sur le plan
    Point3d project(const Point3d &p,const Vector3d &u);
    /// donne le coefficient k de l'intersection I=A+ku de la droite d=(A,u) et du plan
    double interK(const Line &d);

    /// donne la normale
    Vector3d getN() const;
    /// donne le point
    Point3d getA() const;

};

}


#endif // PLAN_H_INCLUDED
