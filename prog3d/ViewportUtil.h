#ifndef VIEWPORTUTIL_H_INCLUDED
#define VIEWPORTUTIL_H_INCLUDED

#include "Matrix4d.h"
#include "Point2d.h"

/**
@file
@author F. Aubert
@brief les passages des diff�rents syst�mes de coordonn�es openGL (local,normalized,window). Il faut appeler setView() dans le display (m�morisation de MODELVIEW et PROJECTION)
*/
namespace prog3d {

/**
@class ViewportUtil
@brief permet de passer entre les diff�rents syst�mes de coordonn�es openGL (local,normalized,window). Il faut appeler setView() dans le display (m�morisation de MODELVIEW et PROJECTION)
*/

class ViewportUtil {
    Matrix4d localWindow; // matrix M_Local_Window
	Matrix4d normalizedLocal;
	Matrix4d windowNormalized;
	Matrix4d normalizedWindow;
	Matrix4d eyeLocal;

	public:
	/// constructeur par d�faut
	ViewportUtil();

	/// donne le point 2d (en coordonn�es pixels) du point 3d p (donn� dans le rep�re local)
    Point2d windowCoordinate(const Point3d &p) const;
    /// donne le point 3d, exprim� dans le rep�re local courant, correspondant au point 2d (en pixels) mouse. Le point 3d donn� sera tel que sa profondeur (i.e. z dans Eye) sera la m�me que le point r�f�rence
    Point3d applyLocalWindow(const Point2d &mouse,const Point3d &reference);
    /// donne le point 3d, exprim� dans le rep�re local courant, correspondant au point 2d (en pixels). Le point 3d donn� sera tel que sa profondeur normalis�e (dans Eye) soit depth
    Point3d applyLocalWindow(const Point2d &mouse,double depth);
    /// affecte les matrices de passages correspondantes au rep�re local et � la projection courants (� appeler dans le display pour m�moriser les matrices openGL courantes).
    void setView();
    /// donne le point 3D de l'observateur exprim� dans le rep�re local courant
	Point3d cameraLocal();
	/// donne le point 3D en coordonn�es observateur de p (suppos� en coordonn�es locales).
	Point3d applyEyeLocal(const Point3d &p) const;
	/// donne le vecteur 3D en coordonn�es observateur de u (suppos� en coordonn�es locales).
	Point3d applyEyeLocal(const Vector3d &u) const;
	/// donne la matrice eye->local (i.e. la modelview au moment du setView() ).
	const Matrix4d &getEyeLocal() const;

	~ViewportUtil();

};

}

#endif // VIEWPORTUTIL_H_INCLUDED
