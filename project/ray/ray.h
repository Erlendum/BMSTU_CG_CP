/**
 * @file ray.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса Ray
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef RAY_H
#define RAY_H

#include <QVector3D>

/*!
    @brief Класс, представляющий луч
*/
class Ray {
public:
    /*!
        @brief Конструктор по умолчанию
        @return Объект класса
    */
    Ray();
    /*!
        @brief Конструктор
        @param [IN] p - точка испускания луча (QVector3D)
        @param [IN] v - вектор направления луча (QVector3D)
        @return Объект класса
    */
    Ray(const QVector3D& p, const QVector3D& v);

    /*!
        @brief Перегруженный оператор приведения типа
        @param [IN] t - параметр (double)
        @return QVector3D
    */
    QVector3D operator()(double t) const;

    /*!
        @brief Получение вектора
        @return QVector3D
    */
    QVector3D get_vector() const;

    /*!
        @brief Получение точки испускания луча
        @return QVector3D
    */
    QVector3D get_src() const;
    /*!
        @brief Получение вектора направления луча
        @return QVector3D
    */
    QVector3D get_dir() const;

    /*!
        @brief Получение инвертированного вектора направления луча
        @return QVector3D
    */
    QVector3D get_inv_dir() const;

    /*!
        @brief Получение знака луча
        @return std::vector<int>
    */
    std::vector<int> get_sign() const;

private:
    QVector3D _src;
    QVector3D _dir;

    QVector3D _inv_dir;
    std::vector<int> _sign;
};

#endif // RAY_H
