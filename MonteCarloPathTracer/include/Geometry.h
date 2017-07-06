#ifndef __GEOMETRY_H
#define __GEOMETRY_H

#include "Intersection.h"
#include "AABB.h"
#include "Ray.h"
#include "Material.h"

class Intersection;
class AABB;

//各种几何形状的基类，方便类型转换
class Geometry
{
public:
    Material material;

    //得到包围盒
    virtual AABB getAABB() = 0;

    //计算与Ray的交点
    virtual bool intersect(Ray& ray, Intersection& intersection) = 0;

    //光线ray和交点之间是否有遮挡
    virtual bool shadowRayIntersect(Ray& ray, Intersection& intersection)
    {
        return intersect(ray, intersection);
    }

};

#endif