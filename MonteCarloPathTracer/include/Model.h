#ifndef __MODEL_H
#define __MODEL_H

#include <vector>
#include <string>

#include "Vec.h"
#include "Material.h"
#include "AABB.h"
#include "Geometry.h"
#include "KdTree.h"
#include "Light.h"

/*
class Vertex
{
public:
    Point3f point;
    Vec3f normal;//顶点法向量,从Model类normals中进行检索得到
};*/
class Model;
class Light;

//将多边形分解成三角面片
class Triangle:public Geometry
{
public:
/*
    std::vector<int> vertex_idx;//组成顶点的索引
    std::vector<int> vertex_normal_idx;//顶点法向量index
*/
    //不要使用vector，当triangle以指针表示时有问题，可能是被提前释放了
    int vertex_idx[3];
    int vertex_normal_idx[3];

    Model* pmodel;//面所对应的model

    Point3f origin;//三角面片的一个点
    Vec3f edge1, edge2;//三角面片的2条边
    //Mat4 barycentric;//质心

    Vec3f normal;//3个顶点计算得到的面片法向量

    Mat4 barycentric;

    Triangle(Model* _pmodel, int _vertex_idx[3], int _vertex_normal_idx[3]);

    void init();

    //继承Geometry
    AABB getAABB();
    bool intersect(Ray& ray, Intersection& intersection);

    //std::vector<int> vertex_texture_idx;
    Vec3f Triangle::getNormal(const Vec3f& point);
};

//用于表示obj文件的模型，没有记录vt信息，不考虑texture
class Model:public Geometry
{
public:
    //std::vector<Vertex> vertices;
    std::vector<Point3f> vertices;
    std::vector<Geometry*> pTriangles;
    std::vector<Light> lights;

    std::vector<Vec3f> normals;//顶点/面法向量

    //Point3f center;//Model所有vertex的最大最小坐标的平均
    AABB bbox;//Model的包围盒，用于计算Camera视点、所在坐标、朝向等参数
    KdTree kdTree;

    Model(){};
    ~Model();
    Model(const std::string obj_path);

    bool load(const std::string obj_path);
    void init();//将Triangle组织成kdTree

    //继承Geometry
    AABB getAABB();
    bool intersect(Ray& ray, Intersection& intersection);
    bool shadowRayIntersect(Ray& ray, Intersection& intersection);
};

#endif