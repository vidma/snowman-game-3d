#include <math.h>
#include <GL/glut.h>
#include "collisions.h"
#include <vector>
#include <iostream>
using namespace std;

/* Definitions for the brilliant */

// >>> print ",\n".join([", ".join(a.strip().split()) for a in coords.split(',\n')])

static GLfloat BRILL_VERTICES[] = { //0.0, 0.0, 0.0,
		-0.989457, -0.058970, 0.132279, -0.983821, -0.006237, -0.179044,
				-0.908633, 0.060616, 0.413173, -0.893879, 0.198674, -0.401882,
				-0.884807, -0.249940, 0.361000, -0.870052, -0.111882,
				-0.454054, -0.772222, 0.306844, 0.556345, -0.753985, 0.477493,
				-0.451117, -0.709843, -0.506202, 0.419756, -0.691606,
				-0.335552, -0.587706, -0.632328, 0.585663, 0.507110, -0.617574,
				0.723721, -0.307945, -0.542386, 0.790574, 0.284272, -0.536750,
				0.843308, -0.027051, -0.531397, -0.729873, 0.286104, -0.527678,
				0.394693, 0.735831, -0.516643, -0.591814, -0.528950, -0.503805,
				0.618076, -0.582954, -0.450573, -0.610287, 0.566998, -0.426701,
				-0.386903, -0.751788, -0.417628, -0.835518, 0.011094,
				-0.411993, -0.782784, -0.300229, -0.292206, 0.931157, 0.152435,
				-0.268408, 0.290608, 0.883073, -0.238899, 0.566725, -0.747036,
				-0.206029, -0.522437, 0.746484, -0.176521, -0.246320,
				-0.883625, -0.152723, -0.886869, -0.152987, -0.093444,
				0.034347, 0.941829, -0.069618, -0.276209, 0.889656, -0.060453,
				0.343055, -0.880688, -0.036627, 0.032499, -0.932860, 0.022652,
				0.953714, 0.161955, 0.046450, 0.313166, 0.892593, 0.075958,
				0.589283, -0.737515, 0.108828, -0.499880, 0.756004, 0.138337,
				-0.223763, -0.874105, 0.162135, -0.864312, -0.143467, 0.281922,
				0.849629, 0.309197, 0.287557, 0.902363, -0.002126, 0.296630,
				0.453749, 0.760756, 0.320502, 0.677132, -0.558030, 0.373734,
				-0.551231, 0.591922, 0.386572, 0.658660, 0.537918, 0.397607,
				-0.327848, -0.726863, 0.401326, 0.796718, -0.277136, 0.406679,
				-0.776462, 0.036019, 0.412315, -0.723729, -0.275304, 0.487503,
				-0.656876, 0.316913, 0.502257, -0.518818, -0.498142, 0.561535,
				0.402398, 0.596674, 0.579772, 0.573047, -0.410788, 0.623914,
				-0.410648, 0.460085, 0.642151, -0.239999, -0.547377, 0.677640,
				-0.617402, 0.067866, 0.683276, -0.564668, -0.243457, 0.739981,
				0.178727, 0.463022, 0.754736, 0.316785, -0.352032, 0.763808,
				-0.131829, 0.410850, 0.778562, 0.006229, -0.404204, 0.814052,
				-0.371174, 0.211039, 0.823170, -0.285849, -0.292692, 0.853750,
				0.073082, 0.188012, 0.859386, 0.125815, -0.123311, 0.903994,
				-0.166263, -0.011798 };

/* indices are stored similarly as in VRML, just each polygon was initially separated by -1 which was later removed  */

static GLubyte BRILL_VERTEX_COORD_INDICES[] = { 31, 26, 19, 9, 5, 3, 7, 17, 24,
		30, 34, 30, 24, 59, 53, 44, 36, 31, 30, 34, 41, 51, 57, 45, 51, 41, 36,
		26, 31, 37, 27, 21, 16, 19, 26, 36, 44, 49, 47, 53, 49, 44, 16, 9, 19,
		8, 4, 0, 1, 5, 9, 16, 21, 20, 14, 27, 20, 21, 1, 3, 5, 10, 12, 13, 11,
		7, 3, 1, 0, 2, 6, 4, 2, 0, 11, 17, 7, 39, 45, 41, 34, 24, 17, 11, 13,
		22, 32, 12, 22, 13, 50, 40, 33, 28, 29, 35, 42, 52, 58, 56, 62, 56, 58,
		45, 39, 38, 43, 50, 56, 62, 63, 57, 51, 59, 57, 63, 43, 40, 50, 12, 10,
		15, 23, 33, 40, 43, 38, 32, 22, 39, 32, 38, 23, 28, 33, 4, 8, 18, 25,
		29, 28, 23, 15, 6, 2, 10, 6, 15, 25, 35, 29, 27, 37, 46, 48, 42, 35,
		25, 18, 14, 20, 8, 14, 18, 48, 52, 42, 47, 46, 37, 60, 54, 55, 61, 64,
		54, 60, 52, 48, 54, 48, 46, 55, 54, 46, 47, 55, 47, 49, 61, 55, 49, 53,
		61, 53, 59, 64, 61, 59, 63, 62, 64, 63, 60, 64, 62, 58, 60, 58, 52 };

//count of vertices per face
static int BRILL_VERTEX_PER_POLYGON[] = { 10, 3, 10, 3, 3, 10, 3, 3, 10, 3, 3,
		10, 3, 3, 10, 3, 10, 3, 10, 3, 3, 10, 3, 3, 10, 3, 3, 10, 3, 3, 3, 5,
		4, 3, 4, 3, 4, 3, 4, 3, 4, 3 };
//print ",\n".join([", ".join(c.strip().split()) for c in colors.split(",")])
static GLfloat brill_colors[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0, 0.72, 0.6,
		0.9, 0.7, 0.3, 0.8, 0.8, 1.0, 0.5, 0.0, 0.05, 0.6, 0.2, 0.9, 0.3, 0.2,
		0.2, 0.4, 0.4, 1, 0.0, 0.3, 0.0 //the ones with 10 vertexes
		};
static int BRILL_NUM_POLYGONS = 42;

void drawBrilliant() {
	//glScalef(2.0, 2.0, 2.0);

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, BRILL_VERTICES);

	//TODO: not available prior GL 1.4 glMultiDrawElements(GL_POLYGON, vertex_counts, GL_UNSIGNED_BYTE, indices, 42);
	int vertice_index = 0;
	int ipolyg;
	// draw each of the polygons, speficy the color regarding its number of vertices
	for (ipolyg = 0; ipolyg < BRILL_NUM_POLYGONS; ipolyg++) {
		int vert_count = BRILL_VERTEX_PER_POLYGON[ipolyg];
		glColor3fv(&brill_colors[vert_count * 3]);

		//we want to add the border - this will prepare the Z buffer
		glEnable(GL_POLYGON_OFFSET_FILL); // Avoid Stitching!
		glPolygonOffset(1.0, 1.0);
		glDrawElements(GL_POLYGON, vert_count, GL_UNSIGNED_BYTE,
				BRILL_VERTEX_COORD_INDICES + vertice_index);
		glDisable(GL_POLYGON_OFFSET_FILL);

		//this will the the border
		glColor3f(1.0f, 1.0f, 0.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_POLYGON, vert_count, GL_UNSIGNED_BYTE,
				BRILL_VERTEX_COORD_INDICES + vertice_index);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		vertice_index += vert_count;
	}

	// de-activate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
}

Vector3d smooth_surf_coor_function(float u, float v) {
	/*
	 returns Vector3d coordinates [u-; v-rotation]

	 (u, t): u = 0..Pi/4, v = 0..2*Pi
	 */
	float x, y, z;

	x = 4 * pow(cos(u), 3) * sin(u) * cos(v) + 4 * cos(u) * pow(sin(u), 3)
			* cos(v);
	y = 6 * pow(cos(u), 3) * sin(u) * sin(v) - 6 * cos(u) * pow(sin(u), 3)
			* sin(v);
	z = 2 * pow(cos(u), 4) - 2 * pow(sin(u), 4);

	return Vector3d(x, y, z);
}

/* returns a boundingBox */
BoundingBox *drawSmoothSurface(int rotations, int height_steps, GLint mode) {
	/* draws the according to mathematical equation */
	float rot_full = 2.0f * M_PI;
	float h_full = M_PI_4;

	float rot, rot_step = rot_full / rotations;
	float h, h_step = h_full / height_steps;
	Vector3d coord;

	vector<Vector3d> vertices = vector<Vector3d> ();

	for (rot = 0.0; rot < rot_full - rot_step; rot += rot_step) {

		glBegin(mode);
		for (h = 0.0; h <= h_full; h += h_step) {
			/* get the coordinates */

			coord = smooth_surf_coor_function(h, rot);
			vertices.push_back(coord);
			glVertex3fv(coord.fv());

			coord = smooth_surf_coor_function(h, rot + rot_step);
			vertices.push_back(coord);
			glVertex3fv(coord.fv());

		}

		glEnd();
	}

	// finish up to resove some deviations while "rotating" - join the first and last strips...
	glBegin(mode);
	for (h = 0.0; h <= h_full; h += h_step) {
		/* get the coordinates */

		coord = smooth_surf_coor_function(h, rot);
		vertices.push_back(coord);
		glVertex3fv(coord.fv());

		coord = smooth_surf_coor_function(h, 0.0);
		vertices.push_back(coord);
		glVertex3fv(coord.fv());

	}

	glEnd();

	cout << "Smooth Surface!!!" << vertices.size() << endl;

	BoundingBox *box = new BoundingBox(vertices);

	return box;

}

BoundingBox *drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);
	vector<Vector3d> vertices = vector<Vector3d> ();

	//the bottom coordinate of the body
	vertices.push_back(Vector3d(-0.75, -1.5+2, -0.75));
	vertices.push_back(Vector3d(0.75, 0+2, 0.75));

	glPushMatrix();
	{
		// Draw Body
		glTranslatef(0.0f, 0.75f, 0.0f);
		glutSolidSphere(0.75f, 20, 20);

		// Draw Head
		glTranslatef(0.0f, 1.0f, 0.0f);
		glutSolidSphere(0.25f, 20, 20);
		//the top of body
		//vertices.push_back(Vector3d(0.75, -1.5, -0.75));


		// Draw Eyes
		glPushMatrix();
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(0.05f, 0.10f, 0.18f);
			glutSolidSphere(0.05f, 10, 10);
			glTranslatef(-0.1f, 0.0f, 0.0f);
			glutSolidSphere(0.05f, 10, 10);
		}
		glPopMatrix();

		// Draw Nose
		glColor3f(1.0f, 0.5f, 0.5f);
		//glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(0.08f, 0.5f, 10, 2);
	}
	glPopMatrix();

	cout << "SnowMan!!!" << vertices.size() << endl;

	BoundingBox *box = new BoundingBox(vertices);



	return box;
}
