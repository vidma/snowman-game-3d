#ifndef VPOINT3DGL_H_INCLUDED
#define VPOINT3DGL_H_INCLUDED

#include <vector>
#include "Point3d.h"
#include "Point2d.h"
#include "Segment.h"
#include "ViewportUtil.h"

namespace prog3d {

class VPoint3dGL {
	std::vector<Point3d *> *l;          // array of *point that is attached
	std::vector<Point3d> l_backup;      // in case we want to backup the points (undo motion)

	VPoint3d l_inde;                    // points that can be controled independantly to l

	ViewportUtil *view;                 // contains the tool to transform 2d screen in 3d local
	Point3d *selectedPoint3d;           // the point that can be moved by dragging
	Point3d startingMouse;              // where the mouse is pressed in local coordinate

	protected:
	ViewportUtil *getView();

	public:
	VPoint3dGL();

	ItVPoint3d indexOf(Point3d *p);

    void setView();
    void setVPoint3d(VPoint3d *v);

    Point3d *get(int i);

    void backup();
    void restore();

    int size();
	void add(Point3d *p);
	void addAll(VPoint3d &liste);
    void add(const Point2d &mouse);
    void addEnd(const Point2d &mouse);
    void insert(const Point2d &mouse,Point3d *p);
    void insert(Point2d mouse,Point3d *a,Point3d *b);
    void insertNearest(const Point2d &mouse);
    void erase(Point3d *v);
    void clear();

    Point3d* nearestPoint(const Point2d &m);
    void nearestSegment(const Point2d &m,Point3d **a,Point3d **b);

    void controlMouse(Point3d *p,const Point2d &m);

    void selectNearest(const Point2d &m);

    void controlSelected(const Point2d &m);
    void controlTranslate(const Point2d &m);
    void controlScale(const Point2d &m);

    void startMouse(const Point2d &m);


    void draw();


	~VPoint3dGL();

};


}

#endif // LISTVERTEXGL_H_INCLUDED
