#include <iostream>

#include "Model.h"
#include "Scene.h"
#include "Camera.h"
#include "PathTracer.h"
#include "Display.h"
#include "Light.h"

using namespace std;

//面片较少的cornellbox scene01.obj
int render_scene01()
{
    //obj模型加载
    Model model("../models/scene01.obj");

    //cout << model.bbox.low.x << "," << model.bbox.low.y << "," << model.bbox.low.z << endl;
    //cout << model.bbox.high.x << "," << model.bbox.high.x << "," << model.bbox.high.x << endl;
    //相机设置
    Camera camera;
    int width = 800, height = 800;
    float fov = 70;

    Point3f center = (model.bbox.high + model.bbox.low) / 2;
    float scale = length(model.bbox.high - model.bbox.low) / 2;
    //camera.lookAt(0, 40, 0, 0, 5, 0, 0, 1, 0);//面片比较少的cornell box
    camera.lookAt(center.x, center.y, center.z + 1.5*scale, center.x, center.y, center.z, 0, 1, 0);

    camera.calcViewPort(fov, width, height);

    //场景设置
    Scene scene;
    scene.pGeometrys.push_back(&model);

    Point3f origin = Point3f(-1, 9.8, 1);
    Vec3f dy = Vec3f(2, 0, 0);
    Vec3f dx = Vec3f(0, 0, -2);
    Color3f emission = Color3f(50, 50, 50);
    scene.lights.push_back(Light(origin, dx, dy, emission));
    scene.lights.push_back(Light(origin + dx + dy, -dx, -dy, emission));

    //scene.lights = model.lights;


    scene.pCamera = &camera;
    scene.init();

    //路径跟踪
    PathTracer pathTracer(&scene);

    //显示
    Display display(&pathTracer);
    display.run();

    //system("pause");
    return 0;
}

//scene02.obj
int render_scene02()
{
    //obj模型加载
    Model model("../models/scene02.obj");

    //cout << model.bbox.low.x << "," << model.bbox.low.y << "," << model.bbox.low.z << endl;
    //cout << model.bbox.high.x << "," << model.bbox.high.y << "," << model.bbox.high.z << endl;
    //相机设置
    Camera camera;
    int width = 800, height = 600;
    float fov = 60;

    Point3f center = (model.bbox.high + model.bbox.low) / 2;
    float scale = length(model.bbox.high - model.bbox.low) / 2;
    //cout << "center:" << center.x << "," << center.y << "," << center.z << endl;
    //camera.lookAt(center.x, center.y, center.z + 1.5*scale, center.x, center.y, center.z, 0, 1, 0);
    //center += Point3f(2, -5.6, 0);

    //这个角度反射的倒影不太清楚
    //center += Point3f(2, 4, 0);
    //camera.lookAt(center.x, center.y + 2.5, center.z + 2, center.x, center.y, center.z, 0, 1, 0);

    center += Point3f(2, -1, 0);
    camera.lookAt(center.x, center.y + 2, center.z + 5, center.x, center.y, center.z, 0, 1, 0);


    camera.calcViewPort(fov, width, height);

    //场景设置
    Scene scene;
    scene.pGeometrys.push_back(&model);

    //Point3f origin = Point3f(0, 26, 0);
    //Vec3f dx = Vec3f(10, 0, 0);
    //Vec3f dy = Vec3f(0, 0, 10);
    //Color3f emission = Color3f(1, 1, 1);
    //scene.lights.push_back(Light(origin -dx -dy, 2*dx, 2*dy, emission));
    //scene.lights.push_back(Light(origin + dx + dy, -2*dx, -2*dy, emission));

    scene.lights = model.lights;


    scene.pCamera = &camera;
    scene.init();

    //路径跟踪
    PathTracer rayTracer(&scene);

    //显示
    Display display(&rayTracer);
    display.run();

    //system("pause");
    return 0;
}

//sportsCar.obj
int render_sportsCar()
{

    //obj模型加载
    Model model("../models/sportsCar.obj");

    //cout << model.bbox.low.x << "," << model.bbox.low.y << "," << model.bbox.low.z << endl;
    //cout << model.bbox.high.x << "," << model.bbox.high.x << "," << model.bbox.high.x << endl;
    //相机设置
    Camera camera;
    int width = 800, height = 600;
    float fov = 65;

    Point3f center = (model.bbox.high + model.bbox.low) / 2;
    float scale = length(model.bbox.high - model.bbox.low) / 2;
    center += Point3f(-0.6, -0.6, 0);
    //Point3f view_point = Point3f(center.x + 1.5*scale, center.y + 1.0*scale, center.z - 1.0*scale);
    Point3f view_point = Point3f(center.x + 0.7*scale, center.y + 0.5*scale, center.z + 1.2*scale);
    camera.lookAt(view_point.x, view_point.y, view_point.z, center.x, center.y, center.z, 0, 1, 0);

    camera.calcViewPort(fov, width, height);

    //场景设置
    Scene scene;
    scene.pGeometrys.push_back(&model);

    Point3f origin = center + Point3f(0, 5, 0);
    Vec3f dy = Vec3f(3, 0, 0);
    Vec3f dx = Vec3f(0, 0, -3);
    Color3f emission = Color3f(10, 10, 10);
    //scene.lights.push_back(Light(origin, dx, dy, emission));
    //scene.lights.push_back(Light(origin + dx + dy, -dx, -dy, emission));
    scene.lights.push_back(Light(origin -dx -dy, 2*dx, 2*dy, emission));
    scene.lights.push_back(Light(origin + dx + dy, -2*dx, -2*dy, emission));


    //scene.lights = model.lights;


    scene.pCamera = &camera;
    scene.init();

    //路径跟踪
    PathTracer pathTracer(&scene);

    //显示
    Display display(&pathTracer);
    display.run();

    return 0;


}

int render_CornellBox()
{

    //obj模型加载
    string obj_name = "CornellBox-Glossy.obj";
    Model model("../models/" + obj_name);

    //cout << model.bbox.low.x << "," << model.bbox.low.y << "," << model.bbox.low.z << endl;
    //cout << model.bbox.high.x << "," << model.bbox.high.x << "," << model.bbox.high.x << endl;
    //相机设置
    Camera camera;
    int width = 800, height = 600;
    float fov = 60;

    Point3f center = (model.bbox.high + model.bbox.low) / 2;
    float scale = length(model.bbox.high - model.bbox.low) / 2;
    //center += Point3f(-0.6, -0.6, 0);
    //Point3f view_point = Point3f(center.x + 1.5*scale, center.y + 1.0*scale, center.z - 1.0*scale);
    Point3f view_point = Point3f(center.x, center.y, center.z + 1.9*scale);
    camera.lookAt(view_point.x, view_point.y, view_point.z, center.x, center.y, center.z, 0, 1, 0);

    camera.calcViewPort(fov, width, height);

    //场景设置
    Scene scene;
    scene.pGeometrys.push_back(&model);

    //Point3f origin = center + Point3f(0, 5, 0);
    //Vec3f dx = Vec3f(3, 0, 0);
    //Vec3f dy = Vec3f(0, 0, -3);
    //Color3f emission = Color3f(10, 10, 10);

    //scene.lights.push_back(Light(origin - dx - dy, 2 * dx, 2 * dy, emission));
    //scene.lights.push_back(Light(origin + dx + dy, -2 * dx, -2 * dy, emission));

    scene.lights = model.lights;


    scene.pCamera = &camera;
    scene.init();

    //路径跟踪
    PathTracer pathTracer(&scene);

    //显示
    Display display(&pathTracer);
    display.run();

    return 0;


}


int main()
{
    //scene01.obj绘制
    render_scene01();

    //scene02.obj绘制
    //不设置直接光照时，收敛比较快；设置直接光照后，收敛比较慢。
    //render_scene02();

    //sportsCar.obj绘制
    //render_sportsCar();

    //CornellBox-Glossy.obj绘制
    //render_CornellBox();

    return 0;
}