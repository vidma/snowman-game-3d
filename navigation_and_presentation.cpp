/*
 * navigation.c
 *
 *  Created on: Dec 14, 2009
 *      Author: vidma
 */

#include "navigation_and_presentation.h"
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "Vector3d.h"
#include <vector>

#include "collisions.h"

using namespace prog3d;

static float angle = 0.0, ratio;

static float x = 0.0f, y = 0.0f, z = 0.5f; //y=1.75

static float lookat_x = 0.0f, lookat_y = 0.0f, lookat_z = -1.0f;

/* Last good coordinates */
/* TODO: last good lookat,angle */
static float lg_x = x, lg_y = y, lg_z = z, lg_angle = angle;

static int cameraType = CAMERA_EYE;
static int navigationMode = NAVIG_MOVE;
/*
 * =================
 *
 * Provides usual Quake type navigation
 *
 * ==============
 */

/* "examine" mode */
float sphi = 0.0, stheta = 0.0;
float sdepth = 0.0;
/* mouse */
int downX, downY;
bool leftButton = false, middleButton = false;

void orientTheCamera() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (navigationMode == NAVIG_EXAMINE) {
		glTranslatef(0.0, 0.0, -sdepth);
		glRotatef(-stheta, 1.0, 0.0, 0.0);
		glRotatef(sphi, 0.0, 0.0, 1.0);
	}

	if (navigationMode == NAVIG_MOVE) {
		if (cameraType == CAMERA_EYE) {
			gluLookAt(x, y + 0.5, z, x + lookat_x, y + 0.5 + lookat_y, z
					+ lookat_z, 0.0f, 1.0f, 0.0f);
		}
		if (cameraType == CAMERA_HERO_BACK) {
			/* The camera should turn together with the hero */
			float camera_offset_x = sin(angle) * -0.5f;
			float camera_offset_z = -cos(angle) * -0.5f;
			float camera_top = 0.8;

			gluLookAt(x + camera_offset_x, y + camera_top, z + camera_offset_z,
					x + camera_offset_x + lookat_x, y + camera_top / 2
							+ lookat_y, z + +camera_offset_z + lookat_z, 0.0f,
					1.0f, 0.0f);
		}

		if (cameraType == CAMERA_HERO_TOP) {
			/* The camera should turn together with the hero */
			float camera_offset_x = sin(angle) * -0.5f * 2;
			float camera_offset_z = -cos(angle) * -0.5f * 1.5;
			float camera_top = 0.8;

			gluLookAt(x + camera_offset_x, y + camera_top, z + camera_offset_z,
					x + camera_offset_x + lookat_x, y + camera_top / 2
							+ lookat_y, z + +camera_offset_z + lookat_z, 0.0f,
					1.0f, 0.0f);
		}

		//TODO: This one doesn't work well
		if (cameraType == CAMERA_HERO_TOP) {
			/* The camera should turn together with the hero */
			float camera_offset_x = sin(angle) * -0.5f * 2;
			float camera_offset_z = -cos(angle) * -0.5f * 1.5;
			float camera_top = 1.8;

			gluLookAt(x + camera_offset_x, y + camera_top, z + camera_offset_z,
					x + camera_offset_x + lookat_x, y + camera_top / 2
							+ lookat_y, z + camera_offset_z + lookat_z, 0.0f,
					1.0f, 0.0f);
		}
		if (cameraType == CAMERA_SCENE_TOP) {
			float camera_offset_x = 0;
			float camera_offset_z = 3;
			float camera_top = 1.5;

			gluLookAt(camera_offset_x, camera_top, camera_offset_z,
					camera_offset_x, camera_top / 2, -1.0f, 0.0f, 1.0f, 0.0f);
		}

	}
}

/* Orients the viewer as well as the camera from the viewing point
 * rotated by the angle */
void orientMe(float ang) {
	lookat_x = sin(ang);
	lookat_z = -cos(ang);
	orientTheCamera();
}

void undoMove() {
	x = lg_x;
	y = lg_y;
	z = lg_z;
	angle = lg_angle;
	orientTheCamera();
}

void commitMove() {
	lg_x = x;
	lg_y = y;
	lg_z = z;
	lg_angle = angle;
}

/* Just move to the direction to viewing angle by offset */
void moveMe(float offset) {

	x = x + offset * (lookat_x);
	z = z + offset * (lookat_z);
	orientTheCamera();
}

void rotateMe(float rotation_offset) {
	orientMe(angle += rotation_offset);
}

void reshapewinInitNavigation(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
	orientTheCamera();

	/* clean up the stuff */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
/* points the camera to look up and down */
void lookUp(float rotation_offset) {
	lookat_y += rotation_offset;

	orientTheCamera();
}

/* returns the current position of our hero */
Vector3d getPosition() {
	return Vector3d(x, y, z);
}

float getAngle() {
	return angle * 180.0 / M_PI;
}

void setCameraType(int type) {
	cameraType = type;
	orientTheCamera();
}

int getCameraType() {
	return cameraType;
}

int getNavigationMode() {
	return navigationMode;
}

// ============================================

void KeyboardCallback(unsigned char ch, int x, int y) {
	switch (ch) {
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void KeyboardSpecialKeyCallback_Move(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
		moveMe(0.1);
		break;

	case GLUT_KEY_DOWN:
		moveMe(-0.1);
		break;

	case GLUT_KEY_LEFT:
		rotateMe(-0.05);
		break;

	case GLUT_KEY_RIGHT:
		rotateMe(0.05);
		break;
	}

	glutPostRedisplay();
}

void MouseCallback(int button, int state, int x, int y) {
	downX = x;
	downY = y;
	leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
	middleButton = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));
	glutPostRedisplay();
}

void MotionCallback_Examine(int x, int y) {
	if (leftButton) {
		sphi += (float) (x - downX) / 4.0;
		stheta += (float) (downY - y) / 4.0;
	} // rotate
	if (middleButton) {
		sdepth += (float) (downY - y) / 10.0;
	} // scale
	downX = x;
	downY = y;

	orientTheCamera();

	glutPostRedisplay();
}

void MotionCallback_Move(int x, int y) {
	/* rotate left, right */
	rotateMe(float(x - downX) / 400.0);

	/* look up and down */
	lookUp(float(y - downY) / 400.0);

	downX = x;
	downY = y;

	glutPostRedisplay();
}

void setNavigationMode(int mode) {
	navigationMode = mode;
	glutSpecialFunc(KeyboardSpecialKeyCallback_Move);

	if (mode == NAVIG_EXAMINE) {
		sphi = 90.0;
		stheta = 45.0;
		sdepth = 1;
		glutMotionFunc(MotionCallback_Examine);

	}

	if (mode == NAVIG_MOVE) {
		glutMotionFunc(MotionCallback_Move);
	}

	orientTheCamera();
	//glutPostRedisplay();
}

void initNavigationMode() {
	glutMouseFunc(MouseCallback);
	glutKeyboardFunc(KeyboardCallback);
	glutReshapeFunc(reshapewinInitNavigation);

	setNavigationMode(NAVIG_MOVE);
	setCameraType(CAMERA_SCENE_TOP);
}
