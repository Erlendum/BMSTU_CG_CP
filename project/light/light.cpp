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

Light::Light(const QVector3D& position, const Color& color, const double& intensity)

    : _position(position)
    , _color(color)
    , _intensity(intensity)
{
}
