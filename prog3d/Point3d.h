#ifndef POINT3D_H_INCLUDED
#define POINT3D_H_INCLUDED

#include "Tuple3d.h"
#include "Collection.h"

/**
@file
@author F. Aubert
@brief op�rations sur les points 3d (x,y,z)

@mainpage prog3dlib


*/


namespace prog3d {

class Vector3d;
class Point4d;

/**
@class Point3d
@brief Point3d h�rite de Tuple3d (voir Tuple3d pour la majorit� des op�rations usuelles)
*/
class Point3d:public Tuple3d {
    void cnew();
    public:

    /// @brief Constructeur par d�faut
    Point3d();
    /// @brief Constructeur par recopie
    Point3d(const Tuple3d &t);
    /// @brief construction � partir des coordonn�es (x,y,z)
    Point3d(double x,double y,double z);

    /** @brief donne une normale au segment [le point,p2] dans le plan XY.
        Ex : p.normaleSegmentXY(p2)
    */
    Vector3d normaleSegmentXY(const Point3d &p2);

    /// @brief Applique une translation � this. Ex :
    void translate(double x,double y,double z);

    /// Affecte le point avec le point homog�ne p (division par w)
    void project(const Point4d &p);

    /// @brief Trace le segment joignant le point � p
    void drawTo(const Point3d &p) const;

    /// @brief Trace le point
    void draw();

    ~Point3d();

};

/**
@class VPoint3d
@brief tableau de pointeurs sur Point3d (remarque : tous les point sont lib�r�s � la destruction, sauf appel � clear())
*/
typedef VCollection<Point3d> VPoint3d;
typedef VPoint3d::iterator ItVPoint3d;
/**
@class APoint3d
@brief tableau de Point3d
*/
class APoint3d : public ACollection<Point3d> {
    public:
    /// trace un ruban de quadrilat�res entre le tableau et le tableau l
    void drawTo(APoint3d &l);
};


typedef APoint3d::iterator ItAPoint3d;

}


#endif // POINT3D_H_INCLUDED
