#ifndef RAY_H
#define RAY_H

#include <QVector3D>

class Ray {
public:
    Ray();
    Ray(const QVector3D& p, const QVector3D& v);

    QVector3D operator()(double t) const;

    QVector3D get_vector() const;

    QVector3D get_src() const;
    QVector3D get_dst() const;

    QVector3D get_inv_dst() const;

    std::vector<int> get_sign() const;

private:
    QVector3D _src;
    QVector3D _dst;

    QVector3D _inv_dst;
    std::vector<int> _sign;
};

#endif // RAY_H
