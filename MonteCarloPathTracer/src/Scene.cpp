#include "Scene.h"
#include <iostream>

using namespace std;

Scene::Scene()
{
    pCamera = NULL;
    //colors = NULL;
    width = 0, height = 0;
}

Scene::~Scene()
{
    if (colors != NULL)
    {
        delete[] colors;
        colors = NULL;
    }
}

void Scene::setSize(int _width, int _height)
{
    if (!_width || !_height)return;
    if (width == _width&&height == _height)return;

    width = _width;
    height = _height;


    if (colors != NULL)delete[] colors;
    colors = new float[3*width*height];
}

void Scene::init()
{
    this->setSize(pCamera->width, pCamera->height);
    kdTree.build(pGeometrys);
}

Ray* Scene::getRays(float x, float y, int pxSampleNum)
{
    float dx = 1.0f / width, dy = 1.0f / height;
    Ray* rays = new Ray[pxSampleNum ? pxSampleNum : 1];
    if (pxSampleNum == 0) rays[0] = pCamera->getRay(x*dx, y*dy);
    else
    {
        for (int i = 0; i < pxSampleNum; ++i)
        {
            float randomX = (float)rand() / RAND_MAX;
            float randomY = (float)rand() / RAND_MAX;
            rays[i] = pCamera->getRay((x + randomX)*dx, (y + randomY)*dy);
            //cout << endl;
        }
    }
    
    return rays;
}

bool Scene::intersect(Ray& ray, Intersection& intersection)
{
    return kdTree.intersect(ray, intersection);
}

bool Scene::isInShadow(Ray& ray)
{
    Intersection intersection;
    return kdTree.shadowRayIntersect(ray, intersection);
}


Color3f Scene::directIllumination(Intersection& intersection, Ray& ray)
{
    Color3f color;
    for (int i = 0, len = lights.size(); i < len; ++i)
    {
        color += lights[i].render(intersection, ray, this);
    }
    //cout << "color:" << color.r << "," << color.g << "," << color.b << endl;
    //cout << endl;
    return color;
}

