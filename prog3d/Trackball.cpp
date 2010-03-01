#include "Trackball.h"

#include "Matrix4d.h"
#include <GL/gl.h>

/*


 F. Aubert
*/

using namespace prog3d;
using namespace std;

void Trackball::setIdentity() {
    qTotal.set(1,0,0,0);
    qLatent.set(1,0,0,0);
    isStarted=false;
}


Trackball::Trackball() {
    qTotal.set(1,0,0,0);
    qLatent.set(1,0,0,0);
    isStarted=false;
}

Trackball::~Trackball() {
}

void Trackball::apply() {
    Matrix4d m;
    Quaternion qCumul=qLatent*qTotal;
    qCumul.normalize();
    m.set(qCumul);
    glMultMatrixf(m.fv());
}

void Trackball::reshape(int width,int height) {
    this->width=width;
    this->height=height;
}

void Trackball::_toVector3d(int x,int y,Vector3d *v) {
    v->set((float)x/width-1.0/2,-(float)y/height+1.0/2,0.1);
}

void Trackball::start(int x,int y) {
    _toVector3d(x,y,&vInit);
    isStarted=true;
}

void Trackball::motion(int x,int y) {
    if (isStarted) {
        _toVector3d(x,y,&vFin);
        qLatent.set(vInit,vFin);
    }
}

void Trackball::stop() {
    qLatent.mul(qTotal);
    qTotal.set(qLatent);
    qLatent.set(1,0,0,0);
    isStarted=false;
}
