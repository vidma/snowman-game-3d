/*
 * collisions.cpp
 *
 *  Created on: Dec 15, 2009
 *      Author: vidma
 */

// --------- bounding boxes
/* 
Used to represent all the object bounding-box coordinates normalizes in screen coordinates (I guess so..?) [ for collisions]
TODO: move everything to global scene coordinates; screen coordinates are not releable enough; it dependend on the movement and sometimes it's infinity; when the collitions and both navigation fails

*/

#include "collisions.h"
#include "Vector3d.h"
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>

using namespace std;

static vector<BoundingBox> *boundingBoxes = new vector<BoundingBox> ();
static BoundingBox *heroBox;

void setHeroBox(BoundingBox *hero) {
	heroBox = hero;
}
BoundingBox *getHeroBox() {
	return heroBox;
}
vector<BoundingBox> *getBoundingBoxesList() {
	return boundingBoxes;
}

/* constructs a bounding box from a given list of points */
BoundingBox::BoundingBox(vector<Vector3d> coords) {
	int i;
	double x, y, z;
	double much = 1.0e+20f;
	this->min = Vector3d(much, much, much);
	this->max = Vector3d(-much, -much, -much);

	this->min_win = Vector3d(much, much, much);
	this->max_win = Vector3d(-much, -much, -much);

	for (i = 0; i < coords.size(); i++) {
		x = coords.at(i).getX();
		y = coords.at(i).getY();
		z = coords.at(i).getZ();

		if (this->min.getX() > x)
			this->min.setX(x);
		if (this->min.getY() > y)
			this->min.setY(y);
		if (this->min.getZ() > z)
			this->min.setZ(z);

		if (this->max.getX() < x)
			this->max.setX(x);
		if (this->max.getY() < y)
			this->max.setY(y);
		if (this->max.getZ() < z)
			this->max.setZ(z);

		Vector3d win_cords = getWinCoodinates(Vector3d(x, y, z));
		//TODO: this doesn't work then it's not possible to see the object
		x = win_cords.getX();
		y = win_cords.getY();
		z = win_cords.getZ();

		if (this->min_win.getX() > x)
			this->min_win.setX(x);
		if (this->min_win.getY() > y)
			this->min_win.setY(y);
		if (this->min_win.getZ() > z)
			this->min_win.setZ(z);

		if (this->max_win.getX() < x)
			this->max_win.setX(x);
		if (this->max_win.getY() < y)
			this->max_win.setY(y);
		if (this->max_win.getZ() < z)
			this->max_win.setZ(z);

	}

	drawbox_old(this);

}

void drawbox_old(BoundingBox *b) {

	cout << "Box min: " << b->min.getX() << " " << b->min.getY() << " "
			<< b->min.getZ() << endl;
	cout << "Box max: " << b->max.getX() << " " << b->max.getY() << " "
			<< b->min.getZ() << endl;

	glColor3f(1, 0, 0);

	glBegin(GL_LINE_LOOP);
	glVertex3f(b->max.getX(), b->max.getY(), b->min.getZ()); // 0
	glVertex3f(b->min.getX(), b->max.getY(), b->min.getZ()); // 1
	glVertex3f(b->min.getX(), b->min.getY(), b->min.getZ()); // 2
	glVertex3f(b->max.getX(), b->min.getY(), b->min.getZ()); // 3
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(b->max.getX(), b->min.getY(), b->max.getZ()); // 4
	glVertex3f(b->max.getX(), b->max.getY(), b->max.getZ()); // 5
	glVertex3f(b->min.getX(), b->max.getY(), b->max.getZ()); // 6
	glVertex3f(b->min.getX(), b->min.getY(), b->max.getZ()); // 7
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(b->max.getX(), b->max.getY(), b->min.getZ()); // 0
	glVertex3f(b->max.getX(), b->max.getY(), b->max.getZ()); // 5
	glVertex3f(b->min.getX(), b->max.getY(), b->max.getZ()); // 6
	glVertex3f(b->min.getX(), b->max.getY(), b->min.getZ()); // 1
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(b->max.getX(), b->min.getY(), b->max.getZ()); // 4
	glVertex3f(b->min.getX(), b->min.getY(), b->max.getZ()); // 7
	glVertex3f(b->min.getX(), b->min.getY(), b->min.getZ()); // 2
	glVertex3f(b->max.getX(), b->min.getY(), b->min.getZ()); // 3

	glEnd();

}

void drawbox(BoundingBox *b) {
	glDisable(GL_LIGHTING);

	cout << "Box min: " << b->min.getX() << " " << b->min.getY() << " "
			<< b->min.getZ() << endl;
	cout << "Box max: " << b->max.getX() << " " << b->max.getY() << " "
			<< b->min.getZ() << endl;

	Vector3d min_, max_;
	min_ = b->getObjectCoodinates(b->min_win);
	max_ = b->getObjectCoodinates(b->max_win);

	glColor3f(1, 0, 0);

	glBegin(GL_LINE_LOOP);
	glVertex3f(max_.getX(), max_.getY(), min_.getZ()); // 0
	glVertex3f(min_.getX(), max_.getY(), min_.getZ()); // 1
	glVertex3f(min_.getX(), min_.getY(), min_.getZ()); // 2
	glVertex3f(max_.getX(), min_.getY(), min_.getZ()); // 3
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(max_.getX(), min_.getY(), max_.getZ()); // 4
	glVertex3f(max_.getX(), max_.getY(), max_.getZ()); // 5
	glVertex3f(min_.getX(), max_.getY(), max_.getZ()); // 6
	glVertex3f(min_.getX(), min_.getY(), max_.getZ()); // 7
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(max_.getX(), max_.getY(), min_.getZ()); // 0
	glVertex3f(max_.getX(), max_.getY(), max_.getZ()); // 5
	glVertex3f(min_.getX(), max_.getY(), max_.getZ()); // 6
	glVertex3f(min_.getX(), max_.getY(), min_.getZ()); // 1
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(max_.getX(), min_.getY(), max_.getZ()); // 4
	glVertex3f(min_.getX(), min_.getY(), max_.getZ()); // 7
	glVertex3f(min_.getX(), min_.getY(), min_.getZ()); // 2
	glVertex3f(max_.getX(), min_.getY(), min_.getZ()); // 3

	glEnd();

	glEnable(GL_LIGHTING);

}

bool BoundingBox::intersects(BoundingBox *other) {
	/* calculate the screen coordinates;
	 * v =  M.inverse() * p */

	Vector3d this_min_t = this->min_win;
	Vector3d other_min_t = other->min_win;

	Vector3d this_max_t = this->max_win;
	Vector3d other_max_t = other->max_win;

	cout << endl << endl << "-------" << endl;

	this->mGBox.print("This matrix is:");

	other->mGBox.print("Other! matrix is:");

	cout << "This min t:" << this_min_t << " original: " << this->min << endl;
	cout << "This max t:" << this_max_t << endl << " original: " << this->max
			<< endl;

	cout << "other min t:" << other_min_t << " original: " << other->min
			<< endl;
	cout << "other max t:" << other_max_t << " original: " << other->max
			<< endl;

	return (min_win.getX() < other->max_win.getX()) && (max_win.getX()
			> other->min_win.getX())
			&& (min_win.getY() < other->max_win.getY()) && (max_win.getY()
			> other->min_win.getY())
			&& (min_win.getZ() < other->max_win.getZ()) && (max_win.getZ()
			> other->min_win.getZ());

}
Vector3d BoundingBox::getWinCoodinates(Vector3d vec) {
	Vector3d result = Vector3d();
	GLdouble mat_modelview[16], mat_projection[16];
	GLint view[4];
	GLdouble windv[3];
	glGetIntegerv(GL_VIEWPORT, view);

	glGetDoublev(GL_MODELVIEW_MATRIX, mat_modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, mat_projection);
	if (gluProject(vec.getX(), vec.getY(), vec.getZ(), mat_modelview,
			mat_projection, view, &windv[0], &windv[1], &windv[2]) != GLU_TRUE) {
		cout << "!!!!!!!!!!!!!!!!ERROR IN GLUPROJECT" << endl;
		return result;
	}
	result.set(windv[0], windv[1], windv[2]);
	return result;
}
Vector3d BoundingBox::getObjectCoodinates(Vector3d vec) {
	Vector3d result = Vector3d();
	GLdouble mat_modelview[16], mat_projection[16];
	GLint view[4];
	GLdouble windv[3];
	glGetIntegerv(GL_VIEWPORT, view);

	glGetDoublev(GL_MODELVIEW_MATRIX, mat_modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, mat_projection);
	if (gluUnProject(vec.getX(), vec.getY(), vec.getZ(), mat_modelview,
			mat_projection, view, &windv[0], &windv[1], &windv[2]) != GLU_TRUE) {
		cout << "ERROR IN GLUUNPROJECT" << endl;
		return result;
	}
	result.set(windv[0], windv[1], windv[2]);
	return result;
}

