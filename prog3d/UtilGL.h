#ifndef UTILGL_H_INCLUDED
#define UTILGL_H_INCLUDED

#include "Point3d.h"

namespace prog3d {
/**
@file
@author F. Aubert
@brief quelques tracés utiles

*/

/**
@class UtilGL
@brief quelques fonctionnalités de tracés (toutes les méthodes sont statiques)
*/
class UtilGL {
    static APoint3d debugPoint;
    static std::vector<std::string> debugMess;
    public:
    /// trace la liste des points qui ont été sauvegardés par add (à appeler lors du display). Remarque : les points ne sont plus dans la liste après le tracé
    static void drawDebug();
    /// permet de mémoriser le point p qui sera affiché lors du display (permet de déporter l'affichage lorsqu'on veut afficher un point hors de la routine display)
    static void add(const Point3d &p,std::string s);
    /// enlève tous les points mémorisés dans la liste
    static void debugClear();
    /// affiche une chaine de caractère à la position 3d donnée par p (avec un petit décalage)
    static void draw(std::string s,const Point3d &p);
    /// affiche le nombre n à la position 3d donnée par p
    static void draw(int n,const Point3d &p);
    /// affiche la chaine de caractère à la position écran (x,y) (compris entre [-1,1])
    static void draw(std::string s,float x,float y);
    /// affiche une flêche (départ sur a, direction u, longueur taille : s0 est la chaine affichée au début, s1 la chaine affichée à la fin)
    static void drawDart(const Point3d &a,const Vector3d &u,float taille,std::string s0="",std::string s1="");
    /// affiche le repère local
    static void drawAxes(float taille);
    /// trace un cube avec normal aux faces
    static void drawCube(float taille);


};


}

#endif // UTILGL_H_INCLUDED
