#include "Color.h"

using namespace prog3d;
using namespace std;

Color::~Color() {
}

Color::Color() {
}

Color::Color(const Tuple3d &t) : Tuple3d(t) {}

Color::Color(double r,double g,double b) : Tuple3d(r,g,b) {
}

unsigned char Color::getByteR() const {
    return (unsigned char)(getX()*255);
}

unsigned char Color::getByteG() const {
    return (unsigned char)(getY()*255);
}

unsigned char Color::getByteB() const {
    return (unsigned char)(getZ()*255);
}

void Color::setBytev(unsigned char *c) {
    set((double)c[0]/255.0,(double)c[1]/255.0,(double)c[2]/255.0);
}

float Color::getR() const {
    return getX();
}

float Color::getG() const {
    return getY();
}

float Color::getB() const {
    return getZ();
}

Color &Color::operator *(const Color &c) {
    setX(getX()*c.getX());
    setY(getY()*c.getY());
    setZ(getZ()*c.getZ());
    return *this;
}

const Color &Color::addSature(const Color &c) {
    this->add(c);
    if (this->getX()>1) this->setX(1);
    if (this->getY()>1) this->setY(1);
    if (this->getZ()>1) this->setZ(1);
    if (this->getX()<0) this->setX(0);
    if (this->getY()<0) this->setY(0);
    if (this->getZ()<0) this->setZ(0);
    return *this;
}
