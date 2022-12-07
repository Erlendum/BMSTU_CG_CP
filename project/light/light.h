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
    @brief Тип источника света (DIRECTIONAL - источник света не бесконечности, POINT - точечный источник света)
 */
enum LightType {
    DIRECTIONAL,
    POINT
};

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
        @param [IN] light_type - тип источника света (LightType)
        @return Объект класса
    */
    Light(const QVector3D& position, const Color& color, const double& intensity, const LightType& light_type);

    /*!
        @brief Получить положение источника света в пространстве
        @return QVector3D
    */
    QVector3D get_position() const { return _position; }
    /*!
        @brief Получить цвет излучения источника света
        @return Color
    */
    Color get_color() const { return _color; }

    /*!
        @brief Получить интенсивность излучения источника света
        @return double
    */
    double get_intensity() const { return _intensity; }

    /*!
        @brief Установить положение источника света в пространстве
        @param [IN] position - положение источника света в пространстве
    */
    void set_position(const QVector3D& position) { _position = position; };
    /*!
        @brief Установить цвет излучения источника света
        @param [IN] color - цвет излучения источника света
    */
    void set_color(const Color& color) { _color = color; };
    /*!
        @brief Установить интенсивность излучения источника света
        @param [IN] intensity - интенсивность излучения источника света
    */
    void set_intensity(const double& intensity) { _intensity = intensity; }

    /*!
        @brief Получить тип источника света
        @return LightType
    */
    LightType get_light_type() const { return _light_type; }

    /*!
        @brief Установить тип источника света
        @param [IN] light_type - тип источника света (LightType)
    */
    void set_light_type(const LightType& light_type) { _light_type = light_type; }

private:
    QVector3D _position;
    Color _color;
    double _intensity;
    LightType _light_type;
};

#endif // LIGHT_H
