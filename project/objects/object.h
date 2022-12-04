/**
 * @file object.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса абстрактного класса Object
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "intersection.h"
#include "material.h"
#include "ray.h"
#include <QVector3D>

/*!
    @brief Абстрактный класс, представляющий объект
*/
class Object {
public:
    /*!
        @brief Конструктор по умолчанию
        @return Объект класса
    */
    Object() = default;

    /*!
        @brief Виртуальный деструктор
    */
    virtual ~Object() = default;

    /*!
        @brief Поиск пересечения луча с объектом
        @param [IN] ray - луч (Ray)
        @return запись Intersection
    */
    virtual Intersection intersection(const Ray& ray) const = 0;

    /*!
        @brief Установка материала
        @param [IN] mat - материал (mat)
    */
    virtual void set_material(const Material& mat) { this->_material = mat; }

    /*!
        @brief Установка материала
        @return объект класса Material
    */
    virtual Material get_material() const { return this->_material; }

    /*!
        @brief Установка центра объекта
        @param [IN] center - центр (QVector3D)
    */
    virtual void set_center(const QVector3D& center) { _center = center; };

    /*!
        @brief Получение центра
        @return QVector3D
    */
    virtual QVector3D get_center() const { return this->_center; }

    /*!
        @brief Перемещение объекта
        @param [IN] coeffs - коэффициенты переноса (QVector3D)
    */
    virtual void move(const QVector3D& coeffs) = 0;

    /*!
        @brief Масштабирование объекта
        @param [IN] coeffs - коэффициенты масштабирования (QVector3D)
        @param [IN] center - центр масштабирования (QVector3D)
    */
    virtual void scale(const QVector3D& coeffs, const QVector3D& center) = 0;

    /*!
        @brief Масштабирование объекта
        @param [IN] coeffs - коэффициенты масштабирования (QVector3D)
    */
    virtual void scale(const QVector3D& coeffs) = 0;

    /*!
        @brief Поворот объекта
        @param [IN] coeffs - коэффициенты поворота (QVector3D)
        @param [IN] center - центр поворота (QVector3D)
    */
    virtual void rotate(const QVector3D& coeffs, const QVector3D& center) = 0;

    /*!
        @brief Поворот объекта
        @param [IN] coeffs - коэффициенты поворота (QVector3D)
    */
    virtual void rotate(const QVector3D& coeffs) = 0;

    /*!
        @brief Сохранение объекта в файл
        @param [IN] file_name - имя файла (std::string)
    */
    virtual void save(const std::string& file_name) = 0;

    /*!
        @brief Проверка, является ли объект сферой
        @return bool
    */
    virtual bool is_sphere() { return false; }

protected:
    /*!
        @brief Конструктор
        @param [IN] m - материал объекта (Material)
        @param [IN] c - центр объекта (QVector3D)
        @return Объект класса
    */
    Object(const Material& m, const QVector3D& c)
        : _material(m)
        , _center(c)
    {
    }
    /*!
        @brief Конструктор
        @param [IN] c - центр объекта (QVector3D)
        @return Объект класса
    */
    Object(const QVector3D& c)
        : _center(c)
    {
    }
    /*!
        @brief Материал объекта
    */
    Material _material;
    /*!
        @brief Центр объекта
    */
    QVector3D _center;
};

#endif // OBJECT_H
