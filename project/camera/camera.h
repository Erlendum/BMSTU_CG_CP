/**
 * @file camera.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса Camera
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include <QVector2D>
#include <QVector3D>

/*!
    @brief Класс, представляющий наблюдателя (камеру)
*/
class Camera {
public:
    /*!
        @brief Конструктор по умолчанию
        @return Объект класса
    */
    Camera();
    /*!
        @brief Конструктор
        @param [IN] width - ширина пирамиды видимости
        @param [IN] height - высота пирамиды видимости
        @return Объект класса
    */
    Camera(int width, int height);
    /*!
        @brief Деструктор по умолчанию
    */
    ~Camera();

    /*!
        @brief Создание луча
        @param [IN] x - координата x точки на экранной плоскости
        @param [IN] y - координата y точки на экранной плоскости
    */
    Ray create_ray(int x, int y);

    /*!
        @brief Получить точку наблюдения
        @return QVector3D
    */
    QVector3D get_look_at() const;
    /*!
        @brief Установить точку наблюдения
        @param [IN] point - точка наблюдения (QVector3D)
    */
    void set_look_at(const QVector3D& point);

    /*!
        @brief Получить расположение камеры
        @return QVector3D
    */
    QVector3D get_pos() const;
    /*!
        @brief Установить расположение камеры
        @param [IN] pos - положение камеры в пространстве (QVector3D)
    */
    void set_pos(const QVector3D& pos);

private:
    int _img_width;
    int _img_height;

    QVector3D _ic;
    QVector3D _jc;
    QVector3D _kc;

    QVector3D _pos;
};

#endif // CAMERA_H
