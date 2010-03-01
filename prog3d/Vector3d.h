#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED

#include "Tuple3d.h"
#include "Point3d.h"
#include "Point4d.h"
#include <vector>

/**
@file
@author F. Aubert
@brief opérations sur les vecteurs 3D (x,y,z)

*/

namespace prog3d {
/**
@class Vector3d
@brief représentation des vecteurs 3d (x,y,z)
*/
class Vector3d:public Tuple3d {
public:
    /// construction par défaut (vecteur nul)
    Vector3d();
    /// construction par recopie
    Vector3d(const Tuple3d &t);
    /// construction par Vector3d(a,b) (le vecteur est b-a)
    Vector3d(const Point3d &a,const Point3d &b);
    /// construction par Vector3d(x,y,z)
    Vector3d(double x,double y, double z);

    /// affecte le vecteur avec le point en coordonnées homogènes p
    void project(const Point4d &p);
    /// affecte le vecteur avec b-a
    void setVector(const Point3d &a,const Point3d &b);
    /// affecte le vecteur avec le produit vectoriel \f$ a \wedge b \f$
    void wedge(const Vector3d &a,const Vector3d &b);
};

/**
@class VVector3d
@brief tableau de pointeurs sur Vector3d (destruction de tous les vecteurs à la destruction du tableau, sauf appel à clear())
*/
typedef VCollection<Vector3d> VVector3d;
typedef VVector3d::iterator ItVVector3d;
/**
@class AVector3d
@brief tableau de Vector3d
*/
class AVector3d : public ACollection<Vector3d> {
};

typedef AVector3d::iterator ItAVector3d;

}

#endif // VECTOR3D_H_INCLUDED
