#ifndef __INTERSECTION_H
#define __INTERSECTION_H

#include "Geometry.h"
#include "Vec.h"
class Geometry;

class Intersection
{
public:
    Geometry* pGeometry;//用于记录交点所在几何体，比如三角面片
    Point3f point;//交点
    Vec3f normal;//交点所在位置的法线

    Intersection() :pGeometry(NULL){};
};

#endif