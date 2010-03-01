#ifndef VIEWPORTUTIL_H_INCLUDED
#define VIEWPORTUTIL_H_INCLUDED

#include "Matrix4d.h"
#include "Point2d.h"

/**
@file
@author F. Aubert
@brief les passages des différents systèmes de coordonnées openGL (local,normalized,window). Il faut appeler setView() dans le display (mémorisation de MODELVIEW et PROJECTION)
*/
namespace prog3d {

/**
@class ViewportUtil
@brief permet de passer entre les différents systèmes de coordonnées openGL (local,normalized,window). Il faut appeler setView() dans le display (mémorisation de MODELVIEW et PROJECTION)
*/

class ViewportUtil {
    Matrix4d localWindow; // matrix M_Local_Window
	Matrix4d normalizedLocal;
	Matrix4d windowNormalized;
	Matrix4d normalizedWindow;
	Matrix4d eyeLocal;

	public:
	/// constructeur par défaut
	ViewportUtil();

	/// donne le point 2d (en coordonnées pixels) du point 3d p (donné dans le repère local)
    Point2d windowCoordinate(const Point3d &p) const;
    /// donne le point 3d, exprimé dans le repère local courant, correspondant au point 2d (en pixels) mouse. Le point 3d donné sera tel que sa profondeur (i.e. z dans Eye) sera la même que le point référence
    Point3d applyLocalWindow(const Point2d &mouse,const Point3d &reference);
    /// donne le point 3d, exprimé dans le repère local courant, correspondant au point 2d (en pixels). Le point 3d donné sera tel que sa profondeur normalisée (dans Eye) soit depth
    Point3d applyLocalWindow(const Point2d &mouse,double depth);
    /// affecte les matrices de passages correspondantes au repère local et à la projection courants (à appeler dans le display pour mémoriser les matrices openGL courantes).
    void setView();
    /// donne le point 3D de l'observateur exprimé dans le repère local courant
	Point3d cameraLocal();
	/// donne le point 3D en coordonnées observateur de p (supposé en coordonnées locales).
	Point3d applyEyeLocal(const Point3d &p) const;
	/// donne le vecteur 3D en coordonnées observateur de u (supposé en coordonnées locales).
	Point3d applyEyeLocal(const Vector3d &u) const;
	/// donne la matrice eye->local (i.e. la modelview au moment du setView() ).
	const Matrix4d &getEyeLocal() const;

	~ViewportUtil();

};

}

#endif // VIEWPORTUTIL_H_INCLUDED
