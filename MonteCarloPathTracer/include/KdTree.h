#ifndef __KDTREE_H
#define __KDTREE_H
#include "Geometry.h"
#include "AABB.h"
#include <vector>

enum AXIS
{
    X, Y, Z
};

class KdTree :public Geometry
{
public:

    KdTree();
    KdTree(std::vector<Geometry*>& geometry_list, int _split_axis = AXIS::Z);

    void build(std::vector<Geometry*>& geometry_list, int _split_axis = AXIS::Z);
    void partition(int axis, const std::vector<Geometry*>& all, 
        std::vector<Geometry*>* lowVec, std::vector<Geometry*>* highVec);


    //继承Geometry
    AABB getAABB();
    bool intersect(Ray& ray, Intersection& intersection);
    bool shadowRayIntersect(Ray& ray, Intersection& intersection);

private:
    AABB box;
    int split_axis;//切分的坐标标记，AXIS::XYZ
    Geometry *low, *high;
};

#endif