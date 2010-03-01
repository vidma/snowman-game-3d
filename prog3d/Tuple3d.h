#ifndef TUPLE3D_H_INCLUDED
#define TUPLE3D_H_INCLUDED

#include <vector>
#include <string>
#include <ostream>

/**
@file
@author F. Aubert
@brief Opérations sur les triplets (x,y,z)

*/


namespace prog3d {
/**
@class Tuple3d
@brief Représentation des triplets (x,y,z)
*/
class Tuple3d {
    std::vector<double> c;
    static std::vector<float> fc; // for casting

    void cnew();
    public:
    /// @brief construction à partir de x,y,z
    Tuple3d(double x,double y,double z);
    /// @brief construction par recopie
    Tuple3d(const Tuple3d &t);
    Tuple3d();

    /// @brief donne X
    double getX() const;
    /// @brief donne Y
    double getY() const;
    /// @brief donne Z
    double getZ() const;

    double* getDv();

    /// @brief Donne un pointeur de float sur (x,y,z). Ex : glVertex3fv(p.fv())
    float *fv() const;
    /// @brief Donne un pointeur de double sur (x,y,z). Ex : glVertex3dv(p.dv())
    const double *dv() const;

    /// @brief copie le triplet dans a. Ex : a_copier.copyTo(copie)
    void copyTo(Tuple3d *a);

    /// @brief copie a dans le triplet. Ex : copie.copyFrom(a_copier)
    void copyFrom(const Tuple3d &a);

    /// @brief Ex : p1+=p2
    void operator+=(const Tuple3d &a);
    /// @brief Ex : p1*=3.0;
    void operator*=(double k);
    /// @brief affectation par recopie. Ex : p1=p2
    Tuple3d& operator=(const Tuple3d &a);
    /// @brief Ex : p=p1+p2
    friend Tuple3d operator +(const Tuple3d &a,const Tuple3d &b);
    /// @brief Ex : p=p1-p2
    friend Tuple3d operator -(const Tuple3d &a,const Tuple3d &b);
    /// @brief Ex : p1=3.0*p2
    friend Tuple3d operator *(double k,const Tuple3d &b);
    /// @brief Ex : p1=p2*3.0
    friend Tuple3d operator *(const Tuple3d &b,double k);
    /// @brief Ex : p1=-p2
    friend Tuple3d operator -(const Tuple3d &a);

    /// @brief affecte coordonnée X
    void setX(double a);
    /// @brief affecte coordonnée Y
    void setY(double a);
    /// @brief affecte coordonnée Z
    void setZ(double a);
    /// @brief affecte le triplet par copie
    void set(const Tuple3d &copy);
    /// @brief affecte la i-ième coordonnée du triplet (i=0 correspond à x, i=1 à y, et i=2 à z)
    void set(int i,double coordinate);

    /// @brief affectation de x,y,z
    void set(double x,double y,double z);
    /// @brief ajoute (x,y,z) au triplet. Ex : p.add(1,1,1)
    void add(double x,double y,double z);
    /// @brief ajoute a au triplet. Ex : p.add(a)
    void add(const Tuple3d &a);
    /// @brief soustrait a au triplet. Ex : p.sub(a)
    void sub(const Tuple3d &a);

    /// @brief affecte le triplet avec a+b. Ex : p.add(a,b)
    void add(const Tuple3d &a,const Tuple3d &b);
    /// @brief affecte le triplet avec a-b. Ex : p.sub(a,b)
    void sub(const Tuple3d &a,const Tuple3d &b);

    /// @brief donne le carré de la norme du triplet
    double length2() const;
    /// @brief donne la norme du triplet
    double length() const;
    /// @brief normalise le triplet
    const Tuple3d &normalize();
    /// @brief multiplie le triplet par k
    void scale(double k);
    /// @brief modifie le triplet en multipliant (x,y,z) par (kx,ky,kz)
    void scale(double kx,double ky,double kz);
    /// @brief affecte le triplet avec a+k*this
    void scaleAdd(double k,const Tuple3d &a);
    /// @brief donne le produit scalaire entre le triplet et a
    double dot(const Tuple3d &a) const;
    /// @brief donne le carré de la distance entre le triplet et t
    double distance2(const Tuple3d &t) const;

    /// @brief affecte le triplet avec \f$ \frac{n1+n2}{2}\f$
    void moyenne(const Tuple3d& n1,const Tuple3d &n2);
    /// @brief le triplet devient (le triplet+n1)/2
    void moyenne(const Tuple3d& n1);

    /// @brief donne un triplet résultant de la rotation de angle (en radian) autour de Y
    Tuple3d rotationY(float angle) const;

    /// @brief affiche les coordonnées du triplet
    void print(std::string mesg="") const;

    /// @brief compatibilité avec cout (affiche les coordonnées).
    friend std::ostream& operator <<(std::ostream &s,const Tuple3d &t);

    /// destructeur
    ~Tuple3d();
};

}
#endif // TUPLE3D_H_INCLUDED
