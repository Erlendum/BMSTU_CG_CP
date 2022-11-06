#include "camera.h"
#include <QVector3D>

Camera::Camera()
    : _img_width(0)
    , _img_height(0)
    , _ic(QVector3D(1.0, 0.0, 0.0))
    , _jc(QVector3D(0.0, 1.0, 0.0))
    , _kc(QVector3D(0.0, 0.0, 1.0))
    , _pos(QVector3D(0.0, 0.0, 17.0))
{
}

Camera::Camera(int width, int height)
{
    _img_width = width;
    _img_height = height;

    _ic = QVector3D(1.0, 0.0, 0.0);
    _jc = QVector3D(0.0, -1.0, 0.0);
    _kc = QVector3D(0.0, 0.0, 1.0);
}

Camera::~Camera()
{
}

Ray Camera::create_ray(int x, int y)
{
    double xw = (-1.0 / 2.0) + ((1.0 / _img_width) + (x * (1.0 / _img_width)));
    double yw = (1.0 / 2.0) - ((1.0 / _img_height) + (y * (1.0 / _img_height)));

    QVector3D p = _pos + _ic * xw + _jc * yw + _kc * (-1.0);
    QVector3D dir = p - _pos;
    dir.normalize();

    return Ray(_pos, dir);
}

QVector3D Camera::get_pos() const
{
    return this->_pos;
}

void Camera::set_pos(const QVector3D& pos)
{
    this->_pos = pos;
}

QVector3D Camera::get_look_at() const
{
    return this->_kc;
}

void Camera::set_look_at(const QVector3D& point)
{
    this->_kc = this->_pos - point;
    this->_kc.normalize();

    this->_ic = QVector3D::crossProduct(((point + QVector3D(0, 1.0, 0)) - this->_pos), this->_kc);
    this->_ic.normalize();

    this->_jc = QVector3D::crossProduct(this->_kc, this->_ic);
}
