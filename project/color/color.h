/**
 * @file color.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса Color
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef COLOR_H
#define COLOR_H

#include "property.hpp"

/*!
    @brief Класс, представляющий цвет в цветовой модели RGB
*/
class Color {
public:
    /*!
        @brief Конструктор
        @param [IN] red - коэффициент красного цвета (от 0 до 255)
        @param [IN] green - коэффициент зелёного цвета (от 0 до 255)
        @param [IN] blue - коэффициент синего цвета (от 0 до 255)
        @return Объект класса
    */
    Color(double red = 0, double green = 0, double blue = 0)
        : r(this, &Color::get_r, &Color::set_r)
        , g(this, &Color::get_g, &Color::set_g)
        , b(this, &Color::get_b, &Color::set_b)
        , _r(red)
        , _g(green)
        , _b(blue)
    {
    }

    /*!
        @brief Конструктор копирования
        @param [IN] Color - копируемый цвет
        @return Объект класса
    */
    Color(const Color& c)
        : r(this, &Color::get_r, &Color::set_r)
        , g(this, &Color::get_g, &Color::set_g)
        , b(this, &Color::get_b, &Color::set_b)
        , _r(c.r)
        , _g(c.g)
        , _b(c.b)
    {
    }

    /*!
        @brief Перегруженный оператор умножения
        @param [IN] d - множитель (double)
        @return Объект класса
    */
    Color operator*(const double& d) const;
    /*!
        @brief Перегруженный оператор умножения
        @param [IN] c - множитель (Color)
        @return Объект класса
    */
    Color operator*(const Color& c) const;
    /*!
        @brief Перегруженный оператор умножения, совмещённого с присваиванием
        @param [IN] c - множитель (Color)
        @return Объект класса
    */
    Color& operator*=(const Color& c);
    /*!
        @brief Перегруженный оператор сложения
        @param [IN] c - множитель (Color)
        @return Объект класса
    */
    Color operator+(const Color& c) const;
    /*!
        @brief Перегруженный оператор сложения, совмещённого с присваиванием
        @param [IN] c - слагаемое (Color)
        @return Объект класса
    */
    Color& operator+=(const Color& c);
    /*!
        @brief Перегруженный оператор присваивания
        @param [IN] c - rvalue (Color)
        @return Объект класса
    */
    Color& operator=(const Color& c);

    /*!
        @brief Использование паттерна Property для красного компонента цвета
    */
    const Property<double, Color> r;
    /*!
        @brief Использование паттерна Property для зелёного компонента цвета
    */
    const Property<double, Color> g;
    /*!
        @brief Использование паттерна Property для синего компонента цвета
    */
    const Property<double, Color> b;

    /*!
        @brief Установка цвета
        @param [IN] red - коэффициент красного цвета (от 0 до 255)
        @param [IN] green - коэффициент зелёного цвета (от 0 до 255)
        @param [IN] blue - коэффициент синего цвета (от 0 до 255)
    */
    void set_color(double red, double green, double blue);

    /*!
        @brief Нормализация цвета
        @details Если коэффициент одного из компонентов цвета превысил значение 255, этот коэффициент становится равным 255
    */
    void normalize();

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
