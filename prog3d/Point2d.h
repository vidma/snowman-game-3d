#ifndef POINT2D_H_INCLUDED
#define POINT2D_H_INCLUDED

#include "Tuple3d.h"
#include "Vector2d.h"
#include <vector>

/*!
*
* @file
*
* @brief opérations sur les point (x,y) du plan
* @author F. Aubert
*
*/

namespace prog3d {
/**
@class Point2d
@brief représentation d'un vecteur (x,y) du plan
*/
class Vector2d;
class Point2d:public Tuple2d {
    void cnew();
    public:
    /// constructeur par défaut
    Point2d();
    /// constructeur par recopie
    Point2d(const Tuple2d &t);
    /// constructeur par Point2d(x,y)
    Point2d(double x,double y);

    /// donne un vecteur orthogonal au segment [le point,p2]
    Vector2d normaleSegment(const Point2d &p2);

    /// donne le carré de la distance entre le point et a.
    double distance2(const Point2d &a) const;

    /// destructeur
    ~Point2d();

};

/**
@class VPoint2d
@brief tableau de pointeurs sur VPoint2d
*/
class VPoint2d:public std::vector<Point2d *> {
    public:
    VPoint2d() {clear();}
};

typedef VPoint2d::iterator ItVPoint2d;

}


#endif // POINT2D_H_INCLUDED
