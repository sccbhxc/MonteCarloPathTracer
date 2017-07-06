#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <string>
#include "Vec.h"

class Reflectance {
public:
    Vec3f ka;//环境光系数
    Vec3f kd;//漫反射系数
    Vec3f ks;//镜面反射系数
};

class Material
{
public:

    Material() :shiness(60), refractiveIndex(1.0), bUseFresnel(false){};

    std::string name;//材料名称
    Color3f emission;//发光

    double shiness;//光泽度Ns
    double refractiveIndex;//折射系数Ni
    Vec3f tf;//transmission filter

    bool bUseFresnel;//默认为不用Fresnel
    Reflectance ref;//反射系数
};

#endif