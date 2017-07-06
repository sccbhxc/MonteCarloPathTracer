#ifndef __AABB_H
#define __AABB_H

#include "Ray.h"
#include "Intersection.h"
#include "Vec.h"

class Intersection;//为什么要加这句后，编译器才不报错(Error 47 error C2061: syntax error : identifier Intersection)

// Aix-Align Bounding Box
class AABB
{
public:
    Point3f low, high;//AABB的2个对角坐标点，以表示AABB

    AABB(){};
    AABB(Point3f _low, Point3f _high) :low(_low), high(_high){};
    
    //合并2个AABB
    static AABB merge(const AABB& bbox1, const AABB& bbox2);

    //得到对应坐标轴上的最小坐标
    inline float getMinCoord(int axis){ return low.num[axis]; }
    inline float getMaxCoord(int axis){ return high.num[axis]; }

    //计算ray与AABB交点
    bool intersect(Ray& ray, Intersection& intersection);


};

#endif