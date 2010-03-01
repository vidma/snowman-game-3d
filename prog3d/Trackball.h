#ifndef TRACKBALL_H_INCLUDED
#define TRACKBALL_H_INCLUDED

#include "Quaternion.h"
#include "Vector3d.h"

namespace prog3d {

/**
@file
@author F. Aubert
@brief trackball par quaternion (cible = origine du rep�re courant; extr�mit� = plan �cran d�cal�)
*/


/**
@class Trackball
@brief trackball par quaternion (cible = origine du rep�re courant; extr�mit� = plan �cran d�cal�)
*/
class Trackball {
    Quaternion qTotal;
    Quaternion qLatent;

    Vector3d vInit;
    Vector3d vFin;

    int width,height;

    bool isStarted;

    void _toVector3d(int x,int y, Vector3d *u);

public:
  /// constructeur par d�faut (quaternion (1,(0,0,0)))
  Trackball();
  /// destructeur
  ~Trackball();

  /// � appeler en cas de reshape
  void reshape(int width,int height);
  /// applique la rotation du trackball
  void apply();
  /// initialise le point de d�part du track (� appeler au moment du click)
  void start(int x,int y);
  /// g�re le mouvement de la souris en motion (calcule une rotation latente)
  void motion(int x,int y);
  /// arr�te le mouvement (� appeler lorsqu'on relache; la rotation latente est cumul�e � la rotation totale)
  void stop();
  void setIdentity();

};

}

#endif // TRACKBALL_H_INCLUDED
