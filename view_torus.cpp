/*  
 Left mouse: rotate;
 Right mouse:   menu;
 ESC to quit
 */

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#include "navigation_and_presentation.h"
#include "objects.h"

#include <vector>
#include "Vector3d.h"
#include "Texture.h"

#include "collisions.h"

#include <iostream>

using namespace prog3d;
using namespace std;

int displayMenu, mainMenu, cameraMenu, navigationMenu;

void MyIdleFunc(void) {
	glutPostRedisplay();
} /* things to do while idle */
void RunIdleFunc(void) {
	glutIdleFunc(MyIdleFunc);
}
void PauseIdleFunc(void) {
	glutIdleFunc(NULL);
}

GLfloat off[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat deep_blue[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat shiny[] = { 50.0 };
GLfloat dull[] = { 0.0 };


//light characteristics
GLfloat ldif[] = { 1, 1, 1, 1 };
Point3d lpos_init(1, 1, 0); // position initiale de la lumiere
Point3d lpos(3, 7, 0);
bool _debug = false;

Texture textureGround, textureSmoothSurf;


// ----- stufff --------

// Variables globales pour la cin�matique de la sc�ne (voir myIdle)
GLfloat angScene = 60.0; // angle de rotation de la scene
GLfloat angSource = 0.0; // angle de rotation pour la source lumineuse
GLfloat deplaceZ = 0.0; // position de l'objet en Z
GLfloat incrZ = -0.01; // increment pour la position de l'objet
GLfloat ang_avion = 0.0;
GLfloat incr_ang = 0.05;


void drawGround() {
	glPushMatrix();
	{

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glScalef(3.0, 3.0, 3.0);
		//glutSolidCube(1.0);
		// Draw ground
		glColor3f(0.8f, 0.8f, 0.5f);

		//create ground

		//glActiveTexture(GL_TEXTURE0);
		textureGround.direct();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		//glColor4f(0.8, 0.8, 0.8, 1);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-1.0f, 0.0f, -1.0f);

			glTexCoord2f(0.0, 10.0);
			glVertex3f(-1.0f, 0.0f, 1.0f);

			glTexCoord2f(10.0, 10.0);
			glVertex3f(1.0f, 0.0f, 1.0f);

			glTexCoord2f(10.0, 0.0);
			glVertex3f(1.0f, 0.0f, -1.0f);
		}
		glEnd();
		textureGround.disable();

	}
	glPopMatrix();
}

BoundingBox *drawBrilliantAndStand() {
	BoundingBox* box = 0;

	glPushMatrix();
	{
		glScalef(0.2, 0.2, 0.2);
		//rotate the stand
		//glRotatef(90, 0.0, 0.0, 1.0);


		glColor3f(1.0f, 0.5f, 0.5f);
		glTranslatef(0.0, 1.5, 0.0);
		//stand
		glPushMatrix();
		{
			glScalef(1.0, 1.5, 1.0);
			vector<Vector3d> vertices = vector<Vector3d> ();
			vertices.push_back(Vector3d(-0.5, -0.5, -0.5));
			vertices.push_back(Vector3d(0.5, 1.0, 0.5));
			box = new BoundingBox(vertices);
			glutSolidCube(1.0);
		}
		glPopMatrix();

		//brilliant
		glTranslatef(0.0, 1.2, 0.0);
		glScalef(0.5, 0.5, 0.5);
		drawBrilliant();
	}
	glPopMatrix();
	return box;
}

bool testIntersections() {
	BoundingBox *hero = getHeroBox();
	vector<BoundingBox> *obj_boxes = getBoundingBoxesList();
	int i;

	for (i = 0; i < obj_boxes->size(); i++) {
		//Test for intersections

		//skip the points we cannot see, because this cause the trouble
		//if (obj_boxes->at(i).min_win.getZ() < -0.005)
		//	continue;

		bool intersects = hero->intersects(&(obj_boxes->at(i)));

		cout << "Intersection ?" << intersects << endl;

		if (intersects)
			return true;
	}
	return false;
}


Point3d mouvementSource(const Point3d &lposinit) {
	Point3d res(lposinit);
	res = lposinit.rotationY(5.0 * angSource * M_PI / 180.0);
	return res;
}

void drawLight(const Point3d &lpos) {
	glPushMatrix();
	{

		glTranslatef(-lpos.getX(), lpos.getY(), -lpos.getZ());
		glDisable(GL_LIGHTING);
		glColor3f(1, 0, 0);
		glutWireSphere(0.03, 8, 8);
	}
	glPopMatrix();

	//** partie � commenter lors de l'application de la depth map en placage lin�aire.

	/*

	 // trac� de la diapo
	 glPushMatrix();
	 glMultMatrixd(mGTexture.dv());

	 diapo.direct();


	 glBegin(GL_POLYGON);
	 glVertex3f(-1,-1,0);
	 glVertex3f(1,-1,0);
	 glVertex3f(1,1,0);
	 glVertex3f(-1,1,0);
	 glEnd();

	 diapo.disable();

	 // trac� des droites partant de la diapo
	 glBegin(GL_LINES);
	 glVertex3f(0, 0, -100);
	 glVertex3f(1, 1, 1);
	 glVertex3f(0, 0, -100);
	 glVertex3f(-1, 1, 1);
	 glVertex3f(0, 0, -100);
	 glVertex3f(-1, -1, 1);
	 glVertex3f(0, 0, -100);
	 glVertex3f(1, -1, 1);
	 glEnd();
	 glPopMatrix();
	 */
	glEnable(GL_LIGHTING);
}

void drawScene() {
	lpos = mouvementSource(lpos_init);
	drawLight(lpos);

	glLightfv(GL_LIGHT1, GL_POSITION, Point4d(lpos).fv());
	glEnable(GL_LIGHT1);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


	/* calculer tous les matrices inclus M, M inverse 	*/
	//setupMatrice(lpos);



	//clean the objects
	getBoundingBoxesList()->clear();

	drawGround();

	glPushMatrix();
	{
		glTranslatef(1.0, 0.5, 0.0);
		glScalef(0.1, 0.1, 0.1);
		textureSmoothSurf.direct();

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_T);

		getBoundingBoxesList()->push_back(*drawSmoothSurface(50, 50,
				GL_QUAD_STRIP));

		textureSmoothSurf.disable();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.4, 0.0, 0.0);
		getBoundingBoxesList()->push_back(*drawBrilliantAndStand());
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-1.5, 0.0, 0.0);
		getBoundingBoxesList()->push_back(*drawBrilliantAndStand());
	}
	glPopMatrix();

	/* draw a snowman - the main hero */
	glPushMatrix();
	{
		Vector3d snoman_pos = getPosition();
		//TODO: quite strange!
		glTranslated(snoman_pos.getX(), snoman_pos.getY(), snoman_pos.getZ());
		glRotatef(180 - getAngle(), 0.0, 1.0, 0.0);
		glScalef(0.3, 0.3, 0.3);

		if (getCameraType() == CAMERA_EYE) {
			//we have to turn off the changement of color buffer and deph buffers
			glColorMask(false, false, false, false);
			glDisable(GL_DEPTH_TEST);

		}
		BoundingBox *snowMenBox = drawSnowMan();
		setHeroBox(snowMenBox);
		if (getCameraType() == CAMERA_EYE) {
			//return to the normal state
			glColorMask(true, true, true, true);
			glEnable(GL_DEPTH_TEST);
		}

	}
	glPopMatrix();

}

void DisplayCallback_Move(void) {
	drawScene();

	//cout<<"Intersection 2?"<< getBoundingBoxesList()->at(0).intersects(getHeroBox())<<endl;
	if (testIntersections()) {
		undoMove();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawScene();

	} else
		commitMove();

	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SetNavigationMenu(int value) {
	setNavigationMode(value);
	glutPostRedisplay();
}

void SetCameraMenu(int value) {
	setCameraType(value);
	glutPostRedisplay();
}

void SetMainMenu(int value) {
	switch (value) {
	case 99:
		exit(0);
		break;
	}
}

void myIdle(void) {
	if (true) {
		angScene += 1;
		angSource += 0.5;
		deplaceZ += incrZ;
		ang_avion += incr_ang;
		if (deplaceZ > 4.0 || deplaceZ < -4.0) {
			incrZ = -incrZ;
			incr_ang = -incr_ang;
		}

	}
	glutPostRedisplay();
}

void InitGL() {
	glutInitDisplayMode(GLUT_ALPHA | GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH
			| GLUT_STENCIL);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Task 3");
	glEnable(GL_LIGHTING); // new
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutIdleFunc(myIdle);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	/*
	 glEnable(GL_COLOR_MATERIAL);
	 glColorMaterial(GL_FRONT, GL_DIFFUSE);
	 glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	 glEnable(GL_LIGHT0);
	 glEnable(GL_LIGHT1);
	 */

	glutDisplayFunc(DisplayCallback_Move);

	initNavigationMode();

}

void InitMenu() {

	cameraMenu = glutCreateMenu(SetCameraMenu);
	glutAddMenuEntry("Besmegenio kailyje", CAMERA_EYE);
	glutAddMenuEntry("Uz besmegenio", CAMERA_HERO_BACK);
	//TODO: glutAddMenuEntry("Virs besmegenio", CAMERA_HERO_TOP);
	glutAddMenuEntry("Virsuje", CAMERA_SCENE_TOP);

	navigationMenu = glutCreateMenu(SetNavigationMenu);
	glutAddMenuEntry("Judeti", NAVIG_MOVE);
	glutAddMenuEntry("Apziureti, pvz deimanta", NAVIG_EXAMINE);

	mainMenu = glutCreateMenu(SetMainMenu);
	glutAddSubMenu("Kamera", cameraMenu);
	glutAddSubMenu("Navigacijos rezimas", navigationMenu);

	glutAddMenuEntry("Exit", 99);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void initTextures() {
	ilInit();
	glewInit();
	glEnable(GL_TEXTURE_2D);

	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//glActiveTexture(GL_TEXTURE0);
	textureGround.read("data/grass.jpg");

	//glActiveTexture(GL_TEXTURE3);
	textureSmoothSurf.read("data/metal.jpg");

	glDisable(GL_TEXTURE_2D);

	//glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

	GLfloat lam[] = { 0.3, 0.3, 0.3, 0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ldif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lam);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_NORMALIZE); // les normales sont renormalisï¿œes en cas de glScale
}



int main(int argc, char **argv) {
	glutInit(&argc, argv);
	InitGL();
	initTextures();
	/* WTF! :) this MUST BE CALLED AFTER THE INITIALISATION OF TEXTURES!!! */
	InitMenu();
	glutMainLoop();
}

