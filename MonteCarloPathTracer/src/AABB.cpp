#include "AABB.h"
#include <algorithm>

#include "Vec.h"

using namespace std;

AABB AABB::merge(const AABB& box1, const AABB& box2)
{
    Point3f pt1, pt2;

    pt1.x = min(box1.low.x, box2.low.x);
    pt1.y = min(box1.low.y, box2.low.y);
    pt1.z = min(box1.low.z, box2.low.z);

    pt2.x = max(box1.high.x, box2.high.x);
    pt2.y = max(box1.high.y, box2.high.y);
    pt2.z = max(box1.high.z, box2.high.z);

    return AABB(pt1, pt2);
}

//需要注意浮点误差引起的自遮挡
bool AABB::intersect(Ray& ray, Intersection& result)
{
    Vec3f& inverseDirection = ray.getInverseDirection();

    float t1 = (low.x - ray.origin.x)*inverseDirection.x;//与box的yoz平面相交，x较小
    float t2 = (high.x - ray.origin.x)*inverseDirection.x;

    float t3 = (low.y - ray.origin.y)*inverseDirection.y;//与box的xoz平面相交，y较小
    float t4 = (high.y - ray.origin.y)*inverseDirection.y;

    float t5 = (low.z - ray.origin.z)*inverseDirection.z;//与box的xoy平面相交，z较小
    float t6 = (high.z - ray.origin.z)*inverseDirection.z;

    //与立体box的前后2个交点的距离t
    float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
    if (tmax < 0) return false;

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax) return false;

    //！！！很关键，可能因为没有交点而t太大；也可能因为浮点误差，与自己相交而太小
    return (tmin < ray.getUpperBound() && tmax > ray.getLowerBound());
    //return true;
}