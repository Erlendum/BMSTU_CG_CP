#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include <QVector3D>

class Light {
public:
    Light(const QVector3D& position, const Color& color, const double& attenuation);

    QVector3D get_position() const;
    Color get_color() const;
    double get_intensity() const;

    void set_position(const QVector3D& position);
    void set_color(const Color& color);
    void set_intensity(const double& intensity);

private:
    QVector3D _position;
    Color _color;
    double _intensity;
};

#endif // LIGHT_H
