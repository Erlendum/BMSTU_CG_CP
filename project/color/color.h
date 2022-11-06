#ifndef COLOR_H
#define COLOR_H

#include "property.hpp"

class Color {
public:
    Color(double red = 0, double green = 0, double blue = 0)
        : r(this, &Color::get_r, &Color::set_r)
        , g(this, &Color::get_g, &Color::set_g)
        , b(this, &Color::get_b, &Color::set_b)
        , _r(red)
        , _g(green)
        , _b(blue)
    {
    }

    Color(const Color& c)
        : r(this, &Color::get_r, &Color::set_r)
        , g(this, &Color::get_g, &Color::set_g)
        , b(this, &Color::get_b, &Color::set_b)
        , _r(c.r)
        , _g(c.g)
        , _b(c.b)
    {
    }

    Color operator*(const double& d) const;
    Color operator*(const Color& c) const;
    Color& operator*=(const Color& c);
    Color operator+(const Color& c) const;
    Color& operator+=(const Color& c);
    Color& operator=(const Color& c);

    const Property<double, Color> r, g, b;

    void set_color(double red, double green, double blue);

    void normalize();

    void normalize_samples(int samples_per_pixel);

private:
    double get_r() { return _r; }
    double get_g() { return _g; }
    double get_b() { return _b; }

    void set_r(double value) { _r = value; }
    void set_g(double value) { _g = value; }
    void set_b(double value) { _b = value; }

    double _r, _g, _b;
};

bool operator==(Color c1, Color c2);

#endif // COLOR_H
