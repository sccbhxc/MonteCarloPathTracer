#ifndef __LIGHT_H
#define __LIGHT_H

#include "Intersection.h"
#include "Scene.h"

class Scene;


class Light
{
public:
    Point3f origin;
    Vec3f dx, dy;
    Vec3f normal;
    Vec3f emission;
    float area;
    int lightSamples;

    Light(Point3f _origin, Vec3f _dx, Vec3f _dy, Color3f _emission);

    Color3f render(Intersection& intersection, Ray& ray, Scene* scene);


};

#endif