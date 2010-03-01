#include "Vector3d.h"
#include <vector>

using namespace prog3d;
using namespace std;

enum {
	CAMERA_EYE, CAMERA_HERO_BACK, CAMERA_HERO_TOP, CAMERA_SCENE_TOP
};

enum {
	NAVIG_EXAMINE, NAVIG_MOVE
};



/* Orients the viewer as well as the camera from the viewing point
 * rotated by the angle */
void orientMe(float angle);

/* Just move to the direction to viewing angle by offset */

void moveMe(float offset);

/* rotates the viewing angle */
void rotateMe(float rotation_offset);

/* rotates on X axis allowing to look up and down */
void lookUp(float rotation_offset);

void reshapewinInitNavigation(int w, int h);

/* returns the current position of our hero */
Vector3d getPosition();
float getAngle();

void setCameraType(int type);
int getCameraType();

/* +=============== NAVIGATION MODE ============ */
void setNavigationMode(int mode);
int getNavigationMode();

void initNavigationMode();



void undoMove();
void commitMove();
