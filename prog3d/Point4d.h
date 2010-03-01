#ifndef POINT4D_H_INCLUDED
#define POINT4D_H_INCLUDED

#include <vector>
#include <string>
//#include "Point3d.h"

/**
@file
@author F. Aubert
@brief opérations sur les points (x,y,z,w) en coordonnées homogènes
*/

namespace prog3d {

class Point3d;
class Vector3d;

/**
@class Point4d
@brief Représentation des points en coordonnées homogènes (x,y,z,w)
*/
class Point4d {
    std::vector<double> c;
    static std::vector<float> fc; // for casting

    void init();
    public:
    /// destructeur
    ~Point4d();
    /// constructeur par défaut
    Point4d();
    /// construction par un Point3d (w affecté à 1)
    Point4d(const Point3d &p);
    /// construction par un Vector3d (w affecté à 0)
    Point4d(const Vector3d &p);
    /// construction par recopie
    Point4d(const Point4d &p);
    /// construction par Point4d(x,y,z,w)
    Point4d(double x,double y,double z,double w=1.0);

    /// affecte le point avec p (w mis à 1)
    void set(const Point3d &p);
    /// affecte le point avec u (w mis à 0)
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

    /// donne un pointeur sur les coordonnées (double)
    double *dv();
    /// donne un pointeur sur les coordonnées (float)
    float *fv() const;

    /// affiche sur la console les coordonnées
    void print(std::string mesg) const;
    /// compatibilité avec cout
    friend std::ostream& operator<<(std::ostream &s,const Point4d &p);

};

}

#endif // POINT4D_H_INCLUDED
