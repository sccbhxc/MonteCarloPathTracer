#include "KdTree.h"
#include <algorithm>

using namespace std;

KdTree::KdTree() :low(NULL), high(NULL)
{

}

KdTree::KdTree(vector<Geometry*>& geometry_list, int _split_axis)
{
    build(geometry_list, _split_axis);
}

void KdTree::build(vector<Geometry*>& geometry_list, int _split_axis)
{
    //this->split_axis = _split_axis;
    split_axis = _split_axis;
    unsigned int length = geometry_list.size();

    if (length == 1) {
        low = geometry_list[0];
        high = NULL;
        box = low->getAABB();
    }
    else if (length == 2) {
        low = geometry_list[0];
        high = geometry_list[1];
        box = AABB::merge(low->getAABB(), high->getAABB());
    }
    else {
        vector<Geometry*> lowVec;
        vector<Geometry*> highVec;
        partition(split_axis, geometry_list, &lowVec, &highVec);

        //递归创建kd-tree，需要注意的是：Geometry是KdTree的基类
        low = lowVec.size() > 0 ? new KdTree(lowVec, (split_axis + 1) % 3) : NULL;
        high = highVec.size() > 0 ? new KdTree(highVec, (split_axis + 1) % 3) : NULL;

        if (low == NULL)
            box = high->getAABB();
        else if (high == NULL)
            box = low->getAABB();
        else box = AABB::merge(low->getAABB(), high->getAABB());
    }
}


void KdTree::partition(int axis, const vector<Geometry*>& all, vector<Geometry*>* lowVec, vector<Geometry*>* highVec) {

    float minVal, maxVal;
    minVal = FLT_MAX;
    maxVal = -FLT_MAX;

    for (unsigned int i = 0; i < all.size(); i++) 
    {
        AABB bbox = all[i]->getAABB();
        minVal = min(minVal, bbox.getMinCoord(axis));
        maxVal = max(maxVal, bbox.getMaxCoord(axis));
    }

    float pivot = (maxVal + minVal) / 2;

    for (unsigned int i = 0; i < all.size(); i++) 
    {
        AABB bbox = all[i]->getAABB();
        float centerCoord = (bbox.getMaxCoord(axis) + bbox.getMinCoord(axis)) / 2;
        if (centerCoord < pivot)
            lowVec->push_back(all[i]);
        else highVec->push_back(all[i]);
    }

    // Check to see if we failed to make a partition. If so, grab the closest thing
    // that isn't on the other side of the partition and throw it into the empty list.

    // CASE: Everything ended up in highVec
    if (highVec->size() == all.size()) 
    {
        float minCoord = FLT_MAX;
        unsigned int index;
        //int index = -1;
        Geometry* obj;
        for (unsigned int i = 0; i < highVec->size(); i++) 
        {
            AABB bbox = (*highVec)[i]->getAABB();
            float centerCoord = (bbox.getMaxCoord(axis) + bbox.getMinCoord(axis)) / 2;
            if (centerCoord < minCoord) 
            {
                minCoord = centerCoord;
                index = i;
                obj = (*highVec)[i];
            }
        }
        highVec->erase(highVec->begin() + index);
        lowVec->push_back(obj);
        /*if (index >= 0)
        {
            highVec->erase(highVec->begin() + index);
            lowVec->push_back(obj);
        }*/
    }
    // CASE: Everything ended up in lowVec
    else if (lowVec->size() == all.size()) 
    {
        float maxCoord = -FLT_MAX;
        unsigned int index;
        //int index = -1;
        Geometry* obj;
        for (unsigned int i = 0; i < lowVec->size(); i++)
        {
            AABB bbox = (*lowVec)[i]->getAABB();
            float centerCoord = (bbox.getMaxCoord(axis) + bbox.getMinCoord(axis)) / 2;
            if (centerCoord > maxCoord)
            {
                maxCoord = centerCoord;
                index = i;
                obj = (*lowVec)[i];
            }
        }
        lowVec->erase(lowVec->begin() + index);
        highVec->push_back(obj);
        /*if (index >= 0)
        {
            lowVec->erase(lowVec->begin() + index);
            highVec->push_back(obj);
        }*/
    }
}


AABB KdTree::getAABB()
{
    return box;
}

bool KdTree::intersect(Ray& ray, Intersection& intersection)
{
    //递归得到的最后结果为，ray与aabb(box)的交点
    //递归在与场景无相交时结束（与box无相交点，也更加不会与其中的triangle相交），
    //box为对应层次的triangle的aabb
    if (!box.intersect(ray, intersection)) return false;

    bool hit = false;

    if (ray.direction.num[split_axis] >= 0)//ray方向为正方向
    {
        //递归求交
        if (low != NULL) hit |= low->intersect(ray, intersection);
        if (high != NULL) hit |= high->intersect(ray, intersection);
    }
    else
    {
        if (high != NULL) hit |= high->intersect(ray, intersection);
        if (low != NULL) hit |= low->intersect(ray, intersection);
    }

    return hit;
}

bool KdTree::shadowRayIntersect(Ray& ray, Intersection& intersection)
{
    if (!box.intersect(ray, intersection)) return false;

    bool hit = false;

    if (ray.direction.num[split_axis] >= 0)//ray方向为正方向
    {
        if (low != NULL) hit |= low->shadowRayIntersect(ray, intersection);
        if (!hit&&high != NULL) hit |= high->shadowRayIntersect(ray, intersection);
    }
    else
    {
        if (high != NULL) hit |= high->shadowRayIntersect(ray, intersection);
        if (!hit&&low != NULL) hit |= low->shadowRayIntersect(ray, intersection);
    }

    return hit;
}
