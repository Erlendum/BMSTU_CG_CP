#include "scene.h"
#include <cmath>
#include <float.h>

#include <QVector3D>

#define EPS 1e-6

Scene::Scene()
{
}

bool Scene::intersect(const Ray& ray, Intersection& intersect)
{

    double dist = std::numeric_limits<float>::max();
    ;
    Intersection closest;

    for (auto iter = _objects.begin(); iter != _objects.end(); iter++) {

        Intersection inter = (*iter)->intersection(ray);

        if (inter.dist > 0.0 && inter.dist <= dist) {
            dist = inter.dist;
            closest = inter;
        }
    }

    if (fabs(dist - std::numeric_limits<float>::max()) < EPS)
        return false;

    intersect = closest;

    return true;
}

void Scene::add_light(const QVector3D& position, const Color& color, const double& attenuation)
{
    auto light = std::make_shared<Light>(Light(position, color, attenuation));

    _lights.push_back(light);
}

void Scene::add_object(const std::shared_ptr<Object> object)
{
    _objects.push_back(object);
}
