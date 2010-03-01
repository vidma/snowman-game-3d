#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include "Point2d.h"
#include "Point3d.h"
#include <string>

/**
@file
@author F. Aubert
@brief opérations sur les segments [a,b]
*/


namespace prog3d {

/**
@class Segment
@brief représentation des segments [a,b]
*/
class Segment {
	Point3d a,b;
	enum Entite {A,B,D};
	Entite resultatDistance;

	void init();
    public:
    /// constructeur par défaut
    Segment();
    /// constructeur par Segment(a,b)
	Segment(const Point3d &aa,const Point3d &bb);
    /// constructeur par Segment(a,b) du plan
	Segment(const Point2d &aa,const Point2d &bb);
    /// affiche sur la console (a=...,b=...)
    void print(std::string mesg);
    /// affecte le segment avec [aa,bb]
	void setAB(const Point3d &aa,const Point3d &bb);
    /// affecte le segment dans le plan avec [aa,bb]
	void setAB(const Point2d &aa,const Point2d &bb);
    /// donne le carré de la distance entre le point et p
	double distance2(const Point3d &p);

    /// donne le carré de la distance entre le point et p (dans le plan)
	double distance2(const Point2d &p);
    /// donne le Point3d=(1-k)A+kB
	Point3d interp(double k);

};

}

#endif // SEGMENT_H_INCLUDED
