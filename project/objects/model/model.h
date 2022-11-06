#ifndef MODEL_H
#define MODEL_H

#include "intersection.h"
#include "object.h"
#include "ray.h"
#include <QVector3D>

struct Triangle {
    Triangle() = default;

    explicit Triangle(const std::vector<int>& verts)
        : verts(verts)
    {
    }

    std::vector<Triangle>* get_triangulated_faces();

    std::vector<int> verts {};
};

class Model : public Object {
public:
    Model() = default;

    Model(const std::vector<QVector3D>& points, const std::vector<Triangle>& faces);

    explicit Model(const std::string& file_name);

    size_t num_of_points() const;

    size_t num_of_faces() const;

    const QVector3D& get_point(size_t i) const;
    QVector3D& get_point(size_t i);

    const Triangle& get_face(size_t i) const;

    QVector3D get_normal(const Triangle& face, const Ray& ray) const;

    virtual Intersection intersection(const Ray& ray) const override;

    virtual void move(const QVector3D& coeffs) override;

    virtual void scale(const QVector3D& coeffs) override;

    virtual void rotate(const QVector3D& coeffs) override;

    virtual void save(const std::string& file_name) override;

private:
    std::vector<QVector3D> _points;
    std::vector<Triangle> _faces;
    QVector3D _box_bounds[2] = {};
    QVector3D _corners[8] = {};

    bool _ray_face_intersect(const Ray& ray, const Triangle& face, float& ray_tvalue) const;

    void _update_corners();

    void _create_box();

    bool _ray_box_intersect(const Ray& ray) const;

    QVector3D _calculate_center();

    QVector3D _rotate_x(QVector3D point, const float& angle);

    QVector3D _rotate_y(QVector3D point, const float& angle);

    QVector3D _rotate_z(QVector3D point, const float& angle);

    virtual bool is_sphere() override { return false; }
};

#endif // MODEL_H
