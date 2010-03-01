#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED


#include "Point3d.h"
#include <vector>
#include "Feature.h"
#include "Vector3d.h"
namespace prog3d {

class Vertex:public Feature {
    Point3d p;
    Vector3d n;
    int number;
    int nbNormal;
    void init();
    public:
    Vertex(double x,double y,double z);
    Vertex(const Point3d &p);
    Vertex();

    Point3d &getPoint();
    Vector3d &getNormal();

    const Point3d &point() const;
    const Vector3d &normal() const;
    void setPoint(const Point3d &p);
    void setNormal(const Vector3d &n);
    void set(const Vertex &s);

    void setNumber(int i);
    int getNumber();

    void averageNormalBegin();
    void averageNormalAdd(const Vector3d &n);
    void averageNormalEnd();

    void translate(double x,double y,double z);
    void scale(double k);
    void scale(double kx,double ky,double kz);


    ~Vertex();
};

class VVertex : public VCollection<Vertex> {};
typedef VVertex::iterator ItVVertex;

}

#endif // VERTEX_H_INCLUDED
