#ifndef TRACKBALL_H_INCLUDED
#define TRACKBALL_H_INCLUDED

#include "Quaternion.h"
#include "Vector3d.h"

namespace prog3d {

/**
@file
@author F. Aubert
@brief trackball par quaternion (cible = origine du repère courant; extrémité = plan écran décalé)
*/


/**
@class Trackball
@brief trackball par quaternion (cible = origine du repère courant; extrémité = plan écran décalé)
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
  /// constructeur par défaut (quaternion (1,(0,0,0)))
  Trackball();
  /// destructeur
  ~Trackball();

  /// à appeler en cas de reshape
  void reshape(int width,int height);
  /// applique la rotation du trackball
  void apply();
  /// initialise le point de départ du track (à appeler au moment du click)
  void start(int x,int y);
  /// gère le mouvement de la souris en motion (calcule une rotation latente)
  void motion(int x,int y);
  /// arrête le mouvement (à appeler lorsqu'on relache; la rotation latente est cumulée à la rotation totale)
  void stop();
  void setIdentity();

};

}

#endif // TRACKBALL_H_INCLUDED
