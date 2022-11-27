/**
 * @file intersection.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл с записью Intersection
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "material.h"
#include <QVector3D>

/*!
    @brief Запись, представляющая найденное пересечение
*/
struct Intersection {
    /*!
        @brief Расстояние от начала луча до точки пересечения
    */
    double dist;
    /*!
        @brief Точка пересечения
    */
    QVector3D point;
    /*!
        @brief Нормаль в точки пересечения
    */
    QVector3D norm;
    /*!
        @brief Материал в точки пересечения
    */
    Material material;
};

#endif // INTERSECTION_H
