#ifndef SPHERE_H
#define SPHERE_H

#include "intersection.h"
#include "object.h"
#include "ray.h"
#include <QVector3D>

class Sphere : public Object {
public:
    Sphere();
    Sphere(const QVector3D& center, double radius);
    explicit Sphere(const std::string& file_name);

    QVector3D get_normal(const QVector3D p) const { return (p - _center) / _radius; }

    virtual Intersection intersection(const Ray& ray) const override;

    double get_radius() const { return _radius; };

    void set_radius(const double& radius) { _radius = radius; };

    virtual void move(const QVector3D& coeffs) override;

    virtual void scale(const QVector3D& coeffs) override;

    virtual void rotate(const QVector3D& coeffs) override;

    virtual void save(const std::string& file_name) override;

    virtual bool is_sphere() override { return true; }

private:
    double _radius;
};

#endif // SPHERE_H
