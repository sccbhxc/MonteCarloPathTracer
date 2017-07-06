#include "Light.h"
#include <algorithm>

using namespace std;

static const Color3f BLACK = Color3f(0.0f, 0.0f, 0.0f);

Light::Light(Point3f _origin, Vec3f _dx, Vec3f _dy, Color3f _emission)
{
    lightSamples = 3;
    origin = _origin;
    dx = _dx;
    dy = _dy;
    emission = _emission;

    normal = cross(dx, dy);
    area = length(normal);
    normal = normalize(normal);

}



Color3f Light::render(Intersection& intersection, Ray& ray, Scene* scene)
{
    //srand(0);
    if (emission == BLACK) return BLACK;
    
    Color3f rgb;
    Material& intersectAttr = intersection.pGeometry->material;
    //Reflectance& ref = intersection.pGeometry->getReflectance(intersection.point);
    Reflectance& ref = intersection.pGeometry->material.ref;
    float rate = 1.0f / lightSamples;

    for (int i = 0; i < lightSamples; i++) 
    {
        float sx = (float)rand() / RAND_MAX;
        float sy = (float)rand() / RAND_MAX * (1.0f - sx);

        Vec3f lightOrigin = origin + dx * sx + dy * sy;
        Vec3f&r = lightOrigin - intersection.point;
        float rr = length(r);
        Ray& shadowRay = Ray(intersection.point, r);
        shadowRay.tmax = rr;

        if (!scene->isInShadow(shadowRay))
        {
            Vec3f s = normalize(r);

            float cosThetaIn = max(dot(intersection.normal, s), 0.0f);
            float cosThetaOut = max(dot(-s, normal), 0.0f);
            float geoFactor = cosThetaIn*cosThetaOut / (rr*rr);
            // Probability: 1/area.
            Vec3f intensity = geoFactor * area * emission * rate;

            if (ref.kd != BLACK)
            {
                //calculate the diffuse color
                float mDots = dot(s, intersection.normal);
                if (mDots > 0.0) rgb += mDots*ref.kd
                    *intensity / PI;
            }

            if (ref.ks != BLACK)
            {
                //calculate the specular color
                Vec3f v = ray.direction.flip();
                Vec3f h = normalize(s + v);
                float mDotH = dot(h, intersection.normal);
                if (mDotH > 0.0) rgb += pow(mDotH, intersectAttr.shiness)*ref.ks
                    *intensity
                    *(intersectAttr.shiness + 1) / (2 * PI);
            }
        }
    }
    //cout << endl;
    return rgb;
}


