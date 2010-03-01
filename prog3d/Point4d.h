#ifndef POINT4D_H_INCLUDED
#define POINT4D_H_INCLUDED

#include <vector>
#include <string>
//#include "Point3d.h"

/**
@file
@author F. Aubert
@brief op�rations sur les points (x,y,z,w) en coordonn�es homog�nes
*/

namespace prog3d {

class Point3d;
class Vector3d;

/**
@class Point4d
@brief Repr�sentation des points en coordonn�es homog�nes (x,y,z,w)
*/
class Point4d {
    std::vector<double> c;
    static std::vector<float> fc; // for casting

    void init();
    public:
    /// destructeur
    ~Point4d();
    /// constructeur par d�faut
    Point4d();
    /// construction par un Point3d (w affect� � 1)
    Point4d(const Point3d &p);
    /// construction par un Vector3d (w affect� � 0)
    Point4d(const Vector3d &p);
    /// construction par recopie
    Point4d(const Point4d &p);
    /// construction par Point4d(x,y,z,w)
    Point4d(double x,double y,double z,double w=1.0);

    /// affecte le point avec p (w mis � 1)
    void set(const Point3d &p);
    /// affecte le point avec u (w mis � 0)
    void set(const Vector3d &u);
    /// affecte le point en recopiant p
    void set(const Point4d &p);

    /// affecte x
    void setX(double x);
    /// affecte y
    void setY(double y);
    /// affecte z
    void setZ(double z);
    /// affecte w
    void setW(double w);

    /// donne x
    double getX() const;
    /// donne y
    double getY() const;
    /// donne z
    double getZ() const;
    /// donne w
    double getW() const;

    /// donne un pointeur sur les coordonn�es (double)
    double *dv();
    /// donne un pointeur sur les coordonn�es (float)
    float *fv() const;

    /// affiche sur la console les coordonn�es
    void print(std::string mesg) const;
    /// compatibilit� avec cout
    friend std::ostream& operator<<(std::ostream &s,const Point4d &p);

};

}

#endif // POINT4D_H_INCLUDED
