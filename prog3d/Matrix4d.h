#ifndef MATRIX4D_H_INCLUDED
#define MATRIX4D_H_INCLUDED

#include <vector>
#include <string>
#include "Plan.h"

/*!
*
* @file
*
* @brief op�rations sur les matrices 4x4
* @author F. Aubert
*
*/

namespace prog3d {

class Point4d;
class Point3d;
class Vector3d;
class Quaternion;

/**
@class Matrix4d
@brief Repr�sentation des matrices 4x4
*/
class Matrix4d {
    std::vector<double> m; ///< les coefficients (d�crits en colonne d'abord)

    static float mf[16]; ///< pour cast en pointeur de float (� �viter car lourd)

    void init();

    public:
    /// constructeur par d�faut
    Matrix4d();
    /// construceur par recopie
    Matrix4d(const Matrix4d &m);

    /// donne la i-i�me coordonn�e (colonne d'abord : m.get(i+j*4) donne \f$M_{ij}\f$)
    double get(int i) const;
    /// donne la i-i�me ligne (retourne un Point4d)
    Point4d getRow(unsigned int i);
    /// donne le pointeur sur les coefs en double. Ex : glMultMatrixd(m.dv())
    const double *dv() const;
    /// donne le pointeur sur les coefs en float. Ex : glMultMatrixf(m.fv())
    const float *fv() const;

    /// Ex : m[i] donne le i-i�me coefficient (valeur seulement)
    inline double operator[](int i) const {return *(m.begin()+i);}

    /// affectation par copie
    void set(const Matrix4d &a);
    /// affectation en recopiant les 16 valeurs du tableau v (double)
    void set(double *v);
    /// affectation en recopiant les 16 valeurs du tableau v (float)
    void set(float *v);
    /// affecter le i-i�me avec val
    inline void set(int i,double val) {*(m.begin()+i)=val;}
    /// affecte la matrice avec la matrice de rotation d�crite par le quaternion q
    void set(const Quaternion &q);
    /// transpose la matrice
    void transpose();
    /// inverse la matrice
    void invert();
    /// affecte la matrice avec la matrice de rotation issue de (v1,v2) (d'axe \f$ v1\wedge v2\f$, d'angle (v1,v2))
    void setRotation(const Vector3d &v1,const Vector3d &v2);
    /// affecte la matrice avec la matrice de rotation d'axe axis, et d'angle angle (en radian)
    void setRotation(float angle,const Vector3d &axis);
    /// affecte la matrice avec la matrice de rotation d'axe axis, et d'angle angle (en degr�)
    void setRotationDegree(float angle,const Vector3d &axis);
    /// affecte la matrice avec la matrice de scale (kx,ky,kz)
    void setScale(double kx,double ky,double kz);
    /// affecte la matrice avec la matrice de translation de vecteur t
    void setTranslation(const Vector3d &t);

    /// affecte la matrice avec la projection suivant une direction u sur le plan P
    void setProjectionPlan(const Plan &p,const Vector3d &u);
    /// affecte la matrice avec la projection suivant le point u sur le plan P
    void setProjectionPlan(const Plan &p,const Point3d &u);
    /// applique la matrice au point 3d p (modifie p). Ex : m.transform(&p1)
    void transform(Point3d *p) const;
    /// applique la matrice au vecteur 3d v (modifie v). Ex : m.transform(&v1)
    void transform(Vector3d *v) const;
    /// applique la matrice au vecteur en coordonn�es homog�nes p (modifie p). Ex : m.transform(&p1)
    void transform(Point4d *p) const;

    /// donne le transform� de p (\f$ w \neq 1\f$) par la matrice. Ex : p2=M21.transform(p1)
    Point3d transform(const Point3d &p);
    /// donne le transform� de v (w=0) par la matrice.
    Vector3d transform(const Vector3d &p);
    /// donne le transform� de p (coordonn�es homog�nes) par la matrice.
    Point4d transform(const Point4d &p);

    /// modifie la matrice en �changeant les colonnes i et j
    void swapColumn(int i,int j);
    /// multiplie les coefficients de la colonne i par k
    void scaleColumn(int i,double k);
    /// Mi=Mi-k*Mj (indices de colonnes)
    void subScaleColumn(int i,int j,double k);
    /// Mi=Mi-k*Mj (indices de lignes)
    void subScaleLine(int i,int j,double s);
    /// affecte la i-i�me ligne
    void setRow(int i,double x,double y,double z,double w);
    /// affecte la i-i�me colonne
    void setColumn(int i,double x,double y,double z,double w);


    /// affecte la matrice avec l'identit�
    void setIdentity();
    /// multiplie � droite la matrice par a (M=MA)
    void mul(const Matrix4d &a);
    /// multiplie � gauche la matrice par a (M=AM)
    void mulLeft(const Matrix4d &a);
    /// affecte la matrice avec le produit AB
    void mul(const Matrix4d &a,const Matrix4d &b);

    /// affiche sur la console les 16 coefficients de la matrice
    void print(std::string mesg) const;
    /// affecte la matrice avec l'inversion de a
    void invert(const Matrix4d &a);
    /// destructeur
    ~Matrix4d();
};


}

#endif // MATRIX4D_H_INCLUDED
