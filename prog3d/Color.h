#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include "Tuple3d.h"

/*!
*
* @file
*
* @brief opérations sur les couleurs
* @author F. Aubert
*
*/



namespace prog3d {
/**
@class Color
@brief Représentation des couleurs (r,v,b)
*/

class Color : public Tuple3d {
    public:
    Color();
    Color(const Tuple3d &t);
    Color(double r,double g,double b);
   ~Color();

    /// affecter la couleur avec le tableau c (valeurs supposées entre 0 et 255)
    void setBytev(unsigned char *c);

    unsigned char getByteR() const;
    unsigned char getByteG() const;
    unsigned char getByteB() const;

    float getR() const;
    float getG() const;
    float getB() const;
    Color &operator *(const Color &c);
    const Color &addSature(const Color &c);
};

}

#endif // COLOR_H_INCLUDED
