#include "light.h"

Light::Light(const QVector3D& position, const Color& color, const double& attenuation)

    : _position(position)
    , _color(color)
    , _attenuation(attenuation)
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

double Light::get_attenuation() const
{
    return _attenuation;
}

void Light::set_position(const QVector3D& position)
{
    _position = position;
}

void Light::set_color(const Color& color)
{
    _color = color;
}

void Light::set_attenuation(const double& attenuation)
{
    _attenuation = attenuation;
}
