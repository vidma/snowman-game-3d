#include "UtilGL.h"

#include <string>
#include <sstream>
#include <GL/glut.h>

#include "Point3d.h"
#include "Vector3d.h"
#include "Matrix4d.h"

/*


 F. Aubert

*/

using namespace prog3d;
using namespace std;

APoint3d UtilGL::debugPoint;
vector<string> UtilGL::debugMess;


void UtilGL::drawDebug() {
        glPointSize(8);
        glBegin(GL_POINTS);
        for(unsigned int i=0;i<debugPoint.size();i++) {
            glVertex3fv(debugPoint[i].fv());
        }
        glEnd();
        glPointSize(1);
        for(unsigned int i=0;i<debugPoint.size();i++) {
            draw(debugMess[i],debugPoint[i]);
        }

        //debugPoint.clear();
}

void UtilGL::add(const Point3d &p,string s) {
   debugPoint.push_back(p);
   debugMess.push_back(s);
}


    void UtilGL::debugClear() {
        debugPoint.clear();
        debugMess.clear();
    }

    void UtilGL::draw(string s,const Point3d &p) {
        float mat[16];
        glGetFloatv(GL_MODELVIEW_MATRIX,mat);
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(0.02,0.02,0);
        glMultMatrixf(mat);
        glRasterPos3fv(p.fv());
        for(unsigned int i=0;i<s.size();i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
        }
        glPopMatrix();
    }

    void UtilGL::draw(string s,float x,float y) {
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(-1,1,-1,1,-1,1);
        glRasterPos3f(x,y,0);
        for(unsigned int i=0;i<s.size();i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,s[i]);
        }
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

    void UtilGL::draw(int n,const Point3d &p) {
        ostringstream oss;
        oss << n;
        draw(oss.str(),p);
    }


void UtilGL::drawDart(const Point3d &a,const Vector3d &u,float taille,string s0,string s1) {
    Point3d to;
    to.set(a+u);
    glLineWidth(5);
    glPushMatrix();
    glScalef(taille,taille,taille);
    glBegin(GL_LINES);
    glVertex3fv(a.fv());
    glVertex3fv(to.fv());
    glEnd();
    glLineWidth(1);

    glPushMatrix();
    glTranslatef(to.getX(),to.getY(),to.getZ());

    Matrix4d m;
    m.setIdentity();
    m.setRotation(Vector3d(0,0,1),u);

    glMultMatrixf(m.fv());

    glutSolidCone(0.2,1,4,4);
    if (!s1.empty()) {
        draw(s1,Point3d(0,0.01,1));
    }
    glPopMatrix();
    glPopMatrix();
}

void UtilGL::drawAxes(float taille) {
    Point3d o(0,0,0);
    Vector3d u;
    glPushMatrix();
    u.set(1,0,0);glColor3f(1,0,0);
    drawDart(o,u,taille,"","X");
    u.set(0,1,0);glColor3f(0,1,0);
    drawDart(o,u,taille,"","Y");
    u.set(0,0,1);glColor3f(0,0,1);
    drawDart(o,u,taille,"","Z");
    glPopMatrix();
}

void UtilGL::drawCube(float taille) {
    glPushMatrix();
    glScalef(taille,taille,taille);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);

    glNormal3f(0,0,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);

    glNormal3f(0,1,0);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
   glEnd();
    glPopMatrix();
}
