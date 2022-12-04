/**
 * @file ray.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса Ray
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ray.h"

Ray::Ray(const QVector3D& p, const QVector3D& v)
    : _src(p)
    , _dir(v)
{
    _inv_dir = QVector3D { 1.0f / _dir.x(), 1.0f / _dir.y(), 1.0f / _dir.z() };

    _sign = std::vector<int> { (_inv_dir.x() < 0), (_inv_dir.y() < 0), (_inv_dir.z() < 0) };
}

QVector3D Ray::operator()(double t) const
{
    return _src + _dir * t;
}

QVector3D Ray::get_vector() const
{
    QVector3D ray = _src - _dir;
    ray.normalize();
    return ray;
}
