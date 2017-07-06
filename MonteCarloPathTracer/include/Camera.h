#ifndef __CAMERA_H
#define __CAMERA_H

#include "Vec.h"
#include "Ray.h"

class Camera
{
public:
    int width, height;//视口的大小/窗口大小

    Point3f origin;
    Vec3f direction;

    float fov;//垂直方向的filed of view
    Vec3f front, up, right;//摄像机放置方向
    Vec3f view_x, view_y, view_z;//视线的极限方向

    Camera();

    //确定Camera摆放位置和方向
    void lookAt(float eye_x, float eye_y, float eye_z,
        float center_x, float center_y, float center_z,
        float up_x, float up_y, float up_z);

    //计算视线极限位置
    void calcViewPort(float _fov, int _width, int _height);

    //在视景体内根据像素所在位置，产生对应的ray
    Ray getRay(float x, float y); 

    


};

#endif