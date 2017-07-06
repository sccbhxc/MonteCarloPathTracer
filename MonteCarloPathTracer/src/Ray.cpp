#include "Ray.h"

Point3f Ray::getPoint(float t)
{ 
    return origin + direction*t;
}

Vec3f Ray::getInverseDirection()
{ 
    return inverse_direction; 
}

//可以加快是否有交点的判断
float Ray::getLowerBound()
{ 
    return tmin; 
}

float Ray::getUpperBound()
{
    return tmax; 
}

bool Ray::isWithinBounds(float tVal)
{ 
    return tVal <= tmax && tVal >= tmin; 
}

void Ray::setBounds(float min, float max)
{ 
    tmin = min; tmax = max; 
}

Vec3f Ray::reflect(const Vec3f& normal)
{ 
    return direction - 2.0f * dot(normal, direction) * normal; 
}

bool Ray::refract(const Vec3f& normal, float nit, Vec3f& refract_direction)
{
    float ndoti = dot(normal, direction), 
        k = 1.0f - nit * nit * (1.0f - ndoti * ndoti);
    if (k >= 0.0f) {
        refract_direction = nit * direction - normal * (nit * ndoti + sqrt(k));
        return true;
    }
    // total internal reflection. There is no refraction in this case
    else return false;
}
