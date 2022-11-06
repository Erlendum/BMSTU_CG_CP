#include "ray.h"

Ray::Ray()
{
}

Ray::Ray(const QVector3D& p, const QVector3D& v)
    : _src(p)
    , _dst(v)
{
    _inv_dst = QVector3D { 1.0f / _dst.x(), 1.0f / _dst.y(), 1.0f / _dst.z() };

    _sign = std::vector<int> { (_inv_dst.x() < 0), (_inv_dst.y() < 0), (_inv_dst.z() < 0) };
}

QVector3D Ray::operator()(double t) const
{
    return _src + _dst * t;
}

QVector3D Ray::get_vector() const
{
    QVector3D ray = _src - _dst;
    ray.normalize();
    return ray;
}

QVector3D Ray::get_src() const
{
    return _src;
}

QVector3D Ray::get_dst() const
{
    return _dst;
}

QVector3D Ray::get_inv_dst() const
{
    return _inv_dst;
}

std::vector<int> Ray::get_sign() const
{
    return _sign;
}
