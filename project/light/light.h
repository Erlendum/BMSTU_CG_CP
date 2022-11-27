/**
 * @file light.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса Light
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include <QVector3D>

/*!
    @brief Класс, представляющий точечный источник света
*/
class Light {
public:
    /*!
        @brief Конструктор
        @param [IN] position - положение источника света в пространстве (QVector3D)
        @param [IN] color - цвет излучения источника света (Color)
        @param [IN] intensity - интенсивность излучения источника света (double)
        @return Объект класса
    */
    Light(const QVector3D& position, const Color& color, const double& intensity);

    /*!
        @brief Получить положение источника света в пространстве
        @return QVector3D
    */
    QVector3D get_position() const;
    /*!
        @brief Получить цвет излучения источника света
        @return Color
    */
    Color get_color() const;
    /*!
        @brief Получить интенсивность излучения источника света
        @return double
    */
    double get_intensity() const;

    /*!
        @brief Установить положение источника света в пространстве
        @param [IN] position - положение источника света в пространстве
    */
    void set_position(const QVector3D& position);
    /*!
        @brief Установить цвет излучения источника света
        @param [IN] color - цвет излучения источника света
    */
    void set_color(const Color& color);
    /*!
        @brief Установить интенсивность излучения источника света
        @param [IN] intensity - интенсивность излучения источника света
    */
    void set_intensity(const double& intensity);

private:
    QVector3D _position;
    Color _color;
    double _intensity;
};

#endif // LIGHT_H
