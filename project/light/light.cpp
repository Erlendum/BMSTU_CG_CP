/**
 * @file light.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса Light
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "light.h"

Light::Light(const QVector3D& position, const Color& color, const double& intensity, const LightType& light_type)

    : _position(position)
    , _color(color)
    , _intensity(intensity)
    , _light_type(light_type)
{
}
