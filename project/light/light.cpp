#include "light.h"

Light::Light(const QVector3D& position, const Color& color, const double& intensity)

    : _position(position)
    , _color(color)
    , _intensity(intensity)
{
}

QVector3D Light::get_position() const
{
    return _position;
}

Color Light::get_color() const
{
    return _color;
}

double Light::get_intensity() const
{
    return _intensity;
}

void Light::set_position(const QVector3D& position)
{
    _position = position;
}

void Light::set_color(const Color& color)
{
    _color = color;
}

void Light::set_intensity(const double& intensity)
{
    _intensity = intensity;
}
