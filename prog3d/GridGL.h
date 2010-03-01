#ifndef GRIDGL_H_INCLUDED
#define GRIDGL_H_INCLUDED

#include "Grid.h"
#include "VPoint3dGL.h"

/*!
*
* @file
*
* @brief contrôle des points d'une grille
* @author F. Aubert
*
*/


namespace prog3d {

class GridGL : public prog3d::VPoint3dGL {
    Grid *g;
    public:
    GridGL();
    ~GridGL();
    void setGrid(Grid *g);
    int nearestSegmentV(const Point2d &m);
    void insertNearestV(const Point2d &m);
    double distance2SegV(const Point2d &m,int i,int j);

    int nearestSegmentU(const Point2d &m);
    void insertNearestU(const Point2d &m);
    double distance2SegU(const Point2d &m,int i,int j);
};

}

#endif // GRIDGL_H_INCLUDED
