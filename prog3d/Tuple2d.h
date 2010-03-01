#ifndef TUPLE2D_H_INCLUDED
#define TUPLE2D_H_INCLUDED

/*!
*
* @file
*
* @brief opérations sur les couples (x,y)
* @author F. Aubert
*
*/

#include <vector>
#include <iostream>

namespace prog3d {
/**
@class Tuple2d
@brief Représentation des couples (x,y)
*/
class Tuple2d {
    std::vector<double> c;
    static std::vector<float> fc;

    void cnew();
    public:

    /// constructeur par défaut
    Tuple2d();

    /// constructeur par Tuple2d(x,y)
    Tuple2d(double x,double y);

    /// donne x
    double getX() const;
    /// donne y
    double getY() const;
    /// donne un pointeur de double sur les coordonnées. Ex : glVertex2dv(p.dv());
    const double *dv() const;
    /// donne un pointeur de float sur les coordonnées. Ex : glVertex2fv(p.fv());
    const float *fv() const;

    /// affecte x
    void setX(double a);
    /// affecte y
    void setY(double a);
    /// affectation par recopie
    void set(const Tuple2d &copy);
    /// affectation de (x,y)
    void set(double x,double y);

    /// this devient this+a. Ex : p.add(a)
    void add(const Tuple2d &a);
    /// this devient this-a. Ex : p.sub(a)
    void sub(const Tuple2d &a);
    /// affectation de this avec a+b. Ex : p.add(a,b)
    void add(const Tuple2d &a,const Tuple2d &b);
    /// affectation de this avec a-b. Ex : p.sub(a,b)
    void sub(const Tuple2d &a,const Tuple2d &b);
    /// affectation par recopie. Ex : p1=p2
    Tuple2d& operator=(const Tuple2d &a);
    /// Ex : p1+=p2
    void operator+=(const Tuple2d &a);
    /// Ex : p*=3.0
    void operator*=(double k);

    /// Ex : p=a+b
    friend Tuple2d operator +(const Tuple2d &a,const Tuple2d &b);
    /// Ex : p=a-b
    friend Tuple2d operator -(const Tuple2d &a,const Tuple2d &b);
    /// Ex : p=3.0*a
    friend Tuple2d operator *(double k,const Tuple2d &b);
    /// Ex : p=a*3.0
    friend Tuple2d operator *(const Tuple2d &b,double k);


    /// donne le carré de la norme
    double length2();
    /// donne la norme
    double length();
    /// normalise
    void normalize();
    /// this devient k*this. Ex : p.scale(3.0)
    void scale(double k);
    /// donne le produit scalaire entre this et a. Ex : p1.dot(p2)
    double dot(const Tuple2d &a);

    /// affecte this à \f$\frac{(n1+n2)}{2}\f$
    void moyenne(const Tuple2d& n1,const Tuple2d &n2);
    /// this devient \f$\frac{this+n1}{2}\f$
    void moyenne(const Tuple2d& n1);

    /// affiche sur la console (x,y,z)
    void print();

    /// @brief compatibilité avec cout (affiche les coordonnées).
    friend std::ostream& prog3d::operator <<(std::ostream &s,const Tuple2d &t);


    /// destructeur
    ~Tuple2d();
};

}
#endif // TUPLE2D_H_INCLUDED
