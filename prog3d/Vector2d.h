#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED

#include "Tuple2d.h"
#include "Point2d.h"

/**
@file
@author F. Aubert
@brief opérations sur les vecteurs 2D

*/

namespace prog3d {
class Point2d;
/**
@class Point2d
@brief les vecteurs 2D (x,y)
*/
class Vector2d:public Tuple2d {
public:
    /// constructeur par défaut
    Vector2d();
    /// constructeur par recopie
    Vector2d(const Tuple2d &t);
    /// constructeur par Vector2d(a,b) (le vecteur est b-a)
    Vector2d(const Point2d &a,const Point2d &b);
    /// constructeur par Vector2d(x,y)
    Vector2d(double x,double y);

    /// affecte le vecteur avec b-a
    void setVector(const Point2d &a,const Point2d &b);
};
}


#endif // VECTOR2D_H_INCLUDED
