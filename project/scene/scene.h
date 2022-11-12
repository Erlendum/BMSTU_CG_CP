#ifndef SCENE_H
#define SCENE_H

#include "sphere.h"
#include <memory>
#include <vector>

#include "color.h"
#include "light.h"
#include "model.h"
#include <QVector3D>

class Scene {
public:
    Scene();

    bool intersect(const Ray& ray, Intersection& intersect);

    void add_light(const QVector3D& position, const Color& color, const double& attenuation);

    void remove_light(const size_t& i);

    void add_object(const std::shared_ptr<Object> object);

    void remove_object(const size_t& i);

    std::vector<std::shared_ptr<Object>> get_objects() const
    {
        return _objects;
    };

    std::vector<std::shared_ptr<Light>> get_lights() const { return _lights; };

private:
    std::vector<std::shared_ptr<Object>> _objects;

    std::vector<std::shared_ptr<Light>> _lights;
};

#endif // SCENE_H
