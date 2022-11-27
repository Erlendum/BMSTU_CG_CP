/**
 * @file sphere.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса Sphere
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "intersection.h"
#include "object.h"
#include "ray.h"
#include <QVector3D>

/*!
    @brief Класс, представляющий сферу
*/
class Sphere : public Object {
public:
    /*!
        @brief Конструктор по умолчанию
        @return Объект класса
    */
    Sphere();
    /*!
        @brief Конструктор
        @param [IN] center - центр сферы (double)
        @param [IN] radius - радиус сферы (double)
        @return Объект класса
    */
    Sphere(const QVector3D& center, double radius);
    /*!
        @brief Конструктор, создающий сферу, загружая её из файла
        @param [IN] file_name - имя входного файла (std::string)
        @return Объект класса
    */
    explicit Sphere(const std::string& file_name);

    /*!
        @brief Получение нормали к полигону
        @param [IN] p - точка на сфере (QVector3D)
        @return QVector3D
    */
    QVector3D get_normal(const QVector3D p) const { return (p - _center) / _radius; }

    /*!
        @brief Поиск пересечения луча со сферой
        @param [IN] ray - луч (Ray)
        @return запись Intersection
    */
    virtual Intersection intersection(const Ray& ray) const override;

    /*!
        @brief Получение радиуса сферы
        @return double
    */
    double get_radius() const { return _radius; };

    /*!
        @brief Установка радиуса сферы
        @param [IN] radius - радиус сферы (double)
    */
    void set_radius(const double& radius) { _radius = radius; };

    /*!
        @brief Перемещение сферы
        @param [IN] coeffs - коэффициенты переноса (QVector3D)
    */
    virtual void move(const QVector3D& coeffs) override;

    /*!
        @brief Масштабирование сферы
        @param [IN] coeffs - коэффициенты масштабирования (QVector3D)
    */
    virtual void scale(const QVector3D& coeffs) override;

    /*!
        @brief Поворот сферы
        @param [IN] coeffs - коэффициенты поворота (QVector3D)
    */
    virtual void rotate(const QVector3D& coeffs) override;

    /*!
        @brief Сохранение сферы в файл
        @param [IN] file_name - имя файла (std::string)
    */
    virtual void save(const std::string& file_name) override;

    /*!
        @brief Проверка, является ли объект сферой
        @return bool
    */
    virtual bool is_sphere() override { return true; }

private:
    double _radius;
};

#endif // SPHERE_H
