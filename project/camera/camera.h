#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include <QVector2D>
#include <QVector3D>

class Camera {
public:
    Camera();
    Camera(int width, int height);
    ~Camera();

    Ray create_ray(int x, int y);

    QVector3D get_look_at() const;
    void set_look_at(const QVector3D& point);

    QVector3D get_pos() const;
    void set_pos(const QVector3D& pos);

private:
    int _img_width;
    int _img_height;

    QVector3D _ic;
    QVector3D _jc;
    QVector3D _kc;

    QVector3D _pos;
};

#endif // CAMERA_H
