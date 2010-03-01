#ifndef UTILGL_H_INCLUDED
#define UTILGL_H_INCLUDED

#include "Point3d.h"

namespace prog3d {
/**
@file
@author F. Aubert
@brief quelques trac�s utiles

*/

/**
@class UtilGL
@brief quelques fonctionnalit�s de trac�s (toutes les m�thodes sont statiques)
*/
class UtilGL {
    static APoint3d debugPoint;
    static std::vector<std::string> debugMess;
    public:
    /// trace la liste des points qui ont �t� sauvegard�s par add (� appeler lors du display). Remarque : les points ne sont plus dans la liste apr�s le trac�
    static void drawDebug();
    /// permet de m�moriser le point p qui sera affich� lors du display (permet de d�porter l'affichage lorsqu'on veut afficher un point hors de la routine display)
    static void add(const Point3d &p,std::string s);
    /// enl�ve tous les points m�moris�s dans la liste
    static void debugClear();
    /// affiche une chaine de caract�re � la position 3d donn�e par p (avec un petit d�calage)
    static void draw(std::string s,const Point3d &p);
    /// affiche le nombre n � la position 3d donn�e par p
    static void draw(int n,const Point3d &p);
    /// affiche la chaine de caract�re � la position �cran (x,y) (compris entre [-1,1])
    static void draw(std::string s,float x,float y);
    /// affiche une fl�che (d�part sur a, direction u, longueur taille : s0 est la chaine affich�e au d�but, s1 la chaine affich�e � la fin)
    static void drawDart(const Point3d &a,const Vector3d &u,float taille,std::string s0="",std::string s1="");
    /// affiche le rep�re local
    static void drawAxes(float taille);
    /// trace un cube avec normal aux faces
    static void drawCube(float taille);


};


}

#endif // UTILGL_H_INCLUDED
