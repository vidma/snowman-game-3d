/*
 * collisions.h
 *
 *  Created on: Dec 15, 2009
 *      Author: vidma
 */

#ifndef COLLISIONS_H_
#define COLLISIONS_H_


#include "Vector3d.h"
#include "Matrix4d.h"
#include <vector>

using namespace std;
using namespace prog3d;


class BoundingBox {
public:
	/* construction -all the vertices should be in current PointofView */
	BoundingBox(vector<Vector3d>);
	bool intersects(BoundingBox*);

	Vector3d min, max;
	Vector3d min_win, max_win;
	Matrix4d mGBox;
	Matrix4d mBoxG;

	Vector3d getWinCoodinates(Vector3d vec);
	Vector3d getObjectCoodinates(Vector3d vec);

};

void drawbox(BoundingBox *b);
void drawbox_old(BoundingBox *b);

void setHeroBox(BoundingBox *hero);

BoundingBox *getHeroBox();

vector<BoundingBox> *getBoundingBoxesList();

#endif /* COLLISIONS_H_ */
