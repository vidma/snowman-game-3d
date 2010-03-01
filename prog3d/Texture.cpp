#include "Texture.h"
#include <iostream>

using namespace std;
using namespace prog3d;

#include <stdio.h>
#include "Error.h"

bool Texture::isILInit=false;

void Texture::init() {
    imgId=0;
    texId=0;
    if (!isILInit) {
        ilInit();
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
        isILInit=true;
    }
}

Texture::Texture() {
    this->init();
}

void Texture::setBorder(unsigned int b) {
	border=b;
}

void Texture::init(int w,int h) {
  if (imgId==0) {
    ilGenImages(1,&imgId);
    glGenTextures(1,&texId);
  }
  width=w;height=h;bpp=3;
  ilBindImage(imgId);
  glBindTexture(GL_TEXTURE_2D,texId);

  ilTexImage(w,h,1,3,IL_RGB,IL_UNSIGNED_BYTE,NULL);



///////////////////////////////////////////////////////
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
  this->filtre=GL_NEAREST;
  this->niveau=0;
  ////////////////////////////////////////////////

  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,border,GL_RGB,GL_UNSIGNED_BYTE,ilGetData());

  width=ilGetInteger(IL_IMAGE_WIDTH);
  height=ilGetInteger(IL_IMAGE_HEIGHT);
  format=ilGetInteger(IL_IMAGE_FORMAT);
  bpp=ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
}

Texture::Texture(string nom) {
	border=0;
	this->read(nom);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D,texId);
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}

unsigned char *Texture::getImageCopy() {
    ilBindImage(imgId);
    GLubyte *result=new GLubyte[width*height*bpp];
    ilCopyPixels(0,0,0,width,height,1,IL_RGB,IL_UNSIGNED_BYTE,result);
    return result;
}

void Texture::copyFrom(GLubyte *img,unsigned int w,unsigned int h) {
    if (w==0) w=width;
    if (h==0) h=height;
    if ((h>height) || (w>width)) error("copyFrom size",__LINE__,__FILE__);


    ilBindImage(imgId);
    ilSetPixels(0,0,0,w,h,0,IL_RGB,IL_UNSIGNED_BYTE,img);
    glBindTexture(GL_TEXTURE_2D,texId);
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,w,h,GL_RGB,GL_UNSIGNED_BYTE,img);
}

void Texture::read(string nom) {
  if (imgId==0) {
    ilGenImages(1,&imgId);
    glGenTextures(1,&texId);
  }
  ilBindImage(imgId);
  bool ok=ilLoadImage((char *)nom.c_str());
  if (!ok) {
    error("initTexture("+nom+")",__LINE__,__FILE__);
  }
  width=ilGetInteger(IL_IMAGE_WIDTH);
  height=ilGetInteger(IL_IMAGE_HEIGHT);
  format=ilGetInteger(IL_IMAGE_FORMAT);
  bpp=ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);


  glBindTexture(GL_TEXTURE_2D,texId);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glTexImage2D(GL_TEXTURE_2D,0,bpp,width,height,border,format,GL_UNSIGNED_BYTE,ilGetData());
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
  this->filtre=GL_NEAREST;
  this->niveau=0;
}

void Texture::envMode(GLenum m) {
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,m);
}

void Texture::wrap(GLenum wr) {
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wr);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wr);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,wr);
}

void Texture::disable() const {
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
}

void Texture::sphere() const {
    glBindTexture(GL_TEXTURE_2D,texId);

	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_T);

	glEnable(GL_TEXTURE_2D);
}

void Texture::linearObject() const {
  glBindTexture(GL_TEXTURE_2D,texId);

 glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
 glEnable(GL_TEXTURE_GEN_S);

 glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
 glEnable(GL_TEXTURE_GEN_T);

 glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
 glEnable(GL_TEXTURE_GEN_R);

 glTexGeni(GL_Q,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
 glEnable(GL_TEXTURE_GEN_Q);

 glEnable(GL_TEXTURE_2D);
}


void Texture::linearEye() const {
  glBindTexture(GL_TEXTURE_2D,texId);

 glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
 glEnable(GL_TEXTURE_GEN_S);

 glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
 glEnable(GL_TEXTURE_GEN_T);

 glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
 glEnable(GL_TEXTURE_GEN_R);

 glTexGeni(GL_Q,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
 glEnable(GL_TEXTURE_GEN_Q);

 glEnable(GL_TEXTURE_2D);
}


void Texture::draw(int x,int y) const {
    ilBindImage(imgId);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();glLoadIdentity();glOrtho(-1,1,-1,1,-1,1);

    glRasterPos3i(x,y,0);

    glDrawPixels(width,height,GL_RGB,GL_UNSIGNED_BYTE,ilGetData());
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Texture::draw(int x,int y,int w,int h) {
    int view[4];
    glGetIntegerv(GL_VIEWPORT,view);
    glViewport(x,y,w,h);
    ilBindImage(imgId);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();glLoadIdentity();glOrtho(-1,1,-1,1,-1,1);

    glRasterPos3i(x,y,0);

    glDrawPixels(width,height,GL_RGB,GL_UNSIGNED_BYTE,ilGetData());
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glViewport(view[0],view[1],view[2],view[3]);
}

void Texture::direct() const {
	glBindTexture(GL_TEXTURE_2D,texId);
	glEnable(GL_TEXTURE_2D);
}

Color Texture::getColor(const Point2d &p) const {
    ilBindImage(imgId);
    Color res;
    int s,t;
    if ((p.getX()>=0) && (p.getX()<=1) && (p.getY()>=0) && (p.getY()<=1)) {
    unsigned char pixel[3];
    s=int(p.getX()*(width-1));
    t=int(p.getY()*(height-1));
    ilCopyPixels(s,t,0,1,1,1,IL_RGB,IL_UNSIGNED_BYTE,pixel);
    res.setBytev(pixel);
    return res;
    } else {
        return Color(0,0,0);
    }
}

void Texture::copyFrame(int x0,int y0,int width,int height) {
    bind();
    glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB,x0,y0,width,height,0);
    disable();
}

void Texture::drawIndirect() {
    bind();
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    direct();
    glOrtho(-1,1,-1,1,-1,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(-1,-1);
    glTexCoord2f(1,0);
    glVertex2f(1,-1);
    glTexCoord2f(1,1);
    glVertex2f(1,1);
    glTexCoord2f(0,1);
    glVertex2f(-1,1);
    glEnd();
    disable();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    disable();
}

void Texture::drawIndirect(int x,int y,int w,int h) {
    int view[4];
    glGetIntegerv(GL_VIEWPORT,view);
    glViewport(x,y,w,h);
    drawIndirect();
    glViewport(view[0],view[1],view[2],view[3]);
}
