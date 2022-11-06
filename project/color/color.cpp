#include "color.h"
#include <cmath>

Color Color::operator*(const double& d) const
{
    return Color(d * this->r, d * this->g, d * this->b);
}

Color Color::operator*(const Color& c) const
{
    return Color(r * c.r, g * c.g, b * c.b);
}

Color Color::operator+(const Color& c) const
{
    return Color(r + c.r, g + c.g, b + c.b);
}

Color& Color::operator*=(const Color& c)
{
    _r *= c.r;
    _g *= c.g;
    _b *= c.b;
    return *this;
}

Color& Color::operator+=(const Color& c)
{
    _r += c.r;
    _g += c.g;
    _b += c.b;
    return *this;
}

Color& Color::operator=(const Color& c)
{
    _r = c.r;
    _g = c.g;
    _b = c.b;

    return *this;
}

void Color::set_color(double red, double green, double blue)
{
    _r = red;
    _g = green;
    _b = blue;

    normalize();
}

void Color::normalize()
{
    if (_r > 1)
        _r = 1;
    if (_g > 1)
        _g = 1;
    if (_b > 1)
        _b = 1;
}

void Color::normalize_samples(int samples_per_pixel)
{
    auto scale = 1.0 / samples_per_pixel;
    _r = sqrt(_r * scale);
    _g = sqrt(_g * scale);
    _b = sqrt(_b * scale);
}

bool operator==(Color c1, Color c2)
{
    if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b)
        return true;
    return false;
}
