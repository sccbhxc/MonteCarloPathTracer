#ifndef __SCENE_H
#define __SCENE_H

#include "Geometry.h"
#include "Light.h"
#include "Camera.h"
#include "KdTree.h"
#include "Model.h"

using std::vector;

class Light;

class Scene
{
public:
    vector<Geometry*> pGeometrys;//需要外部输入model
    KdTree kdTree;
    vector<Light> lights;//光源需要在类外进行添加,用于直接光照
    Camera* pCamera;
    float* colors;//整个窗口的color，在RayTracer中计算
    int width, height;

    Scene();
    ~Scene();
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void setSize(int _width, int _height);

    void init();
    Ray* getRays(float x, float y, int pxSampleNum);
    bool intersect(Ray& ray, Intersection& intersection);
    bool isInShadow(Ray& ray);//判断直接光照，在交点和光源点之间是否有遮挡
    Color3f directIllumination(Intersection& intersection, Ray& ray);

};

#endif