#ifndef OBJECT_H
#define OBJECT_H

#include "intersection.h"
#include "material.h"
#include "ray.h"
#include <QVector3D>

class Object {
public:
    Object() = default;

    virtual ~Object() = default;

    virtual Intersection intersection(const Ray& ray) const = 0;

    virtual void set_material(const Material& mat) { this->_material = mat; }

    virtual Material get_material() const { return this->_material; }

    virtual void set_center(const QVector3D& center) { _center = center; };

    virtual QVector3D get_center() const { return this->_center; }

    virtual void move(const QVector3D& coeffs) = 0;

    virtual void scale(const QVector3D& coeffs) = 0;

    virtual void rotate(const QVector3D& coeffs) = 0;

    virtual void save(const std::string& file_name) = 0;

    virtual bool is_sphere() { return false; }

protected:
    Object(const Material& m, const QVector3D& c)
        : _material(m)
        , _center(c)
    {
    }
    Object(const QVector3D& c)
        : _center(c)
    {
    }
    Material _material;
    QVector3D _center;
};

#endif // OBJECT_H
