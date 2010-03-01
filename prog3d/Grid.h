#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "Point3d.h"
#include "Vector3d.h"

/*!
*
* @file
*
* @brief opérations sur une grille de nbU x nbV points
* @author F. Aubert
*
*/


namespace prog3d {
/**
@class Grid
@brief représentation d'une grille de nbU x nbV points. Les indices (i,j) qui suivent sont respectivement dans la direction U et dans la direction V.
*/
class Grid {
    /// les points
    VPoint3d p;
    /// les normales
    VVector3d n;
    /// le nombre de points dans la direction U
    int nbU;
    /// le nombre de points dans la direction V
    int nbV;
    public:
    /// constructeur par défaut
    Grid();
    /// destructeur (rien à libérer : les champs sont autogérés)
    ~Grid();

    /// donne le pointeur sur le point(i,j)
    Point3d *getPoint(unsigned int i,unsigned int j);
    /// donne le pointeur sur la normale(i,j)
    Vector3d *getNormal(unsigned int i,unsigned int j);

    /// donne la valeur du point(i,j)
    Point3d point(unsigned int,unsigned int);
    /// donne la valeur de la normale(i,j)
    Vector3d normal(unsigned int,unsigned int);
    /// affecte le point(i,j) avec p. Ex : g.setPoint(2,3,p1)
    void setPoint(unsigned int,unsigned int,const Point3d &p);
    /// affecte la normale(i,j) avec n. Ex : g.setNormal(2,3,n)
    void setNormal(unsigned int,unsigned int,const Vector3d &n);
    /// donne le nombre de points dans la direction U (direction de premier indice)
    int getNbU();
    /// donne le nombre de points dans la direction V (direction du second indice)
    int getNbV();
    /// initialise la grille comme un quadrilatère de 4 points (p1,p2,p3,p4)
    void init(const Point3d &p1,const Point3d &p2,const Point3d &p3,const Point3d &p4);
    /// initialise la grille avec nu points dans la direction U, nv points dans la direction V. La grille est plane (dans le plan Z=0), centrée sur l'origine et de longueur (lu,lv)
    void init(int nu,int nv,float lu,float lv);

    VPoint3d *getVPoint3d();

    /// insertion d'une ligne de nbU points entre la ligne v et v+1 (médiane)
    void insertVMiddle(int v);
    /// insertion d'une ligne de nbV points entre la ligne u et u+1 (médiane)
    void insertUMiddle(int u);

    /// trace le ruban entre la ligne u1 et u2
    void drawU(int u1,int u2);
    /// trace (par un segment) les normales aux points (k permet de controler la longueur des segments)
    void drawNormal(float k=1.0);
};

}



#endif // GRID_H_INCLUDED
