#include <stdlib.h>
#include "Snapshot.h"

#include <GL/glut.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <IL/il.h>

/*

F. Aubert

*/

using namespace std;



string numero4(int num) {
  string res="";
  if (num<9999) {
    ostringstream o;
    o << num;
    res=o.str();
    for(unsigned int i=0;i<4-o.str().size();i++) {
      res="0"+res;
    }
  }
  return res;
}

void SnapShot::init() {
  pixel.resize(0);
  width=0;height=0;
  num=0;
  numgif=0;
  requested=false;
  imgId=0;
}

SnapShot::SnapShot() {
    this->init();
}

SnapShot::SnapShot(int w,int h) {
  this->init();
  pixel.resize(3*w*h);
  width=w;height=h;
}

SnapShot::~SnapShot() {
    if (imgId) {
      ilDeleteImages(1,&imgId);
    }
}


void SnapShot::resize(int w,int h) {
  width=w;height=h;
  pixel.resize(w*h*3);
}

void SnapShot::shot() {
  string nom;
  bool find_num=false;
  ifstream f;
  while (!find_num) {
    nom="./snap/snapshot"+numero4(num)+".jpg";
    f.open(nom.c_str());
    if (f.is_open()) {
      num++;f.close();
    }
    else
      find_num=true;
  }


  glReadPixels(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE, &(pixel.front()));
  if (imgId==0) {
      ilGenImages(1,&imgId);
  }
  ilBindImage(imgId);
  ilTexImage(width,height,1,3,IL_RGB,IL_UNSIGNED_BYTE,&(pixel.front()));
  ilSaveImage((char *)nom.c_str());
  cout << "Image " << nom << " is saved" << endl;
}

void SnapShot::shotIfRequested() {
    if (requested) {
        shot();
        requested=false;
    }
}

void SnapShot::request() {
    requested=true;
}



