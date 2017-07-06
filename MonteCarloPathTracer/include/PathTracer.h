#ifndef __RAYTRACER_H
#define __RAYTRACER_H

#include "Vec.h"
#include "Ray.h"
#include "Scene.h"
#include "Intersection.h"

class PathTracer
{
private:
    Scene* pScene;
    int iterations;
    int px_sample_num;//每个像素的采样数目
    int mc_sample_num;//蒙特卡洛采样数目
    int max_rescursive_depth;//光线最大递归深度
    bool use_direct_light;//是否使用直接光照
    Color3f ambient; //环境光照

    //路径跟踪，计算ray产生的color
    Color3f trace(Ray& ray, int cur_depth = 0);

    // Monte Carlo Sampling，产生下一条Ray
    Ray monteCarloSample(Ray& ray, Intersection& intersection);

    // 俄罗斯赌盘
    bool russianRoulette(float probability, float& survivor);

    // cosine-weighted importance sampling，使得Monte Carlo Integral比均匀采样收敛更快一些
    // 产生上半球面的ray方向
    Vec3f importanceSample(Vec3f up, float n = -1);


public:

    PathTracer(Scene* _scene);
    float* render();
    Scene* getScene();
};

#endif