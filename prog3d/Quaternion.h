#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include <iostream>

/**
@file
@author F. Aubert
@brief opérations sur les quaternions (w,(x,y,z))
*/


namespace prog3d {

class Matrix4d;
class Vector3d;

/**
@class Quaternion
@brief représentation des quaternions (w,(x,y,z))
*/
class Quaternion {
  double w,x,y,z;

public:
  /// constructeur par recopie
  Quaternion(const Quaternion &q);
  /// affectation par recopie
  Quaternion &operator=(const Quaternion &q);

  /// construction par chacune des composantes (par défaut (1,(0,0,0)))
  Quaternion(double w=1.0,double x=0.0,double y=0.0,double z=0.0);

  /// donne w
  double getW() const {return w;}
  /// donne x
  double getX() const {return x;}
  /// donne y
  double getY() const {return y;}
  /// donne z
  double getZ() const {return z;}

  /// affectation pour (w,(x,y,z))
  void set(double w=1.0,double x=0.0,double y=0.0,double z=0.0);
  /// affectation par (v1,v2) (produit vectoriel et demi-angle)
  void set(const Vector3d &v1,const Vector3d &v2);
  /// affectation selon (scalar,u)
  void set(float scalar,const Vector3d &u,int verif);
  /// affectation selon angle-axis
  void setFromAngleAxis(float angle,const Vector3d &v);
  /// affecte l'angle et l'axe selon le quaternion (doit être une rotation)
  void copyToAngleAxis(float *angle,Vector3d *u);

  /// donne la norme du quaternion
  double length() const;
  /// donne le carré de la norme du quaternion
  double length2();
  /// donne la norme du vecteur du quaternion
  double lengthXYZ() const;
  /// normalise le quaternion
  void normalize();

  /// affecte la matrice de rotation m selon le quaternion
  void copyTo(Matrix4d *m);

  /// affecte le quaternion de rotation selon la matrice src
  void set(Matrix4d src);
  /// multiplie à droite le quaternion par q
  void mul(const Quaternion &q);
  /// affecte le quaternion avec le produit q1*q2
  void mul(const Quaternion &q1,const Quaternion &q2);
  /// affectate le quaternion avec la recopie de q
  void set(const Quaternion &q);
  /// conjugue le quaternion
  void conjugate();
  /// affecte le quaternion avec l'interpolation ((1-t)q1+tq2).normalize()
  void interpolate(double t,const Quaternion &q1, const Quaternion &q2);
  /// affecte le quaternion avec q1+q2
  void add(const Quaternion &q1,const Quaternion &q2);
  /// modifie le quaternion en le multipliant par s
  void scale(double s);

  /// donne le produit de q1*q2
  friend Quaternion operator*(const Quaternion &q1,const Quaternion &q2);
  /// donne k*q
  friend Quaternion operator *(double k,const Quaternion &q);
  /// compatibilité avec cout
  friend std::ostream& operator<<(std::ostream &s,const Quaternion &q);

};
}

#endif // QUATERNION_H_INCLUDED
