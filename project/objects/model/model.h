/**
 * @file model.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса Model
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include "intersection.h"
#include "object.h"
#include "ray.h"
#include <QVector3D>

/*!
    @brief Запись, представляющая полигон-треугольник
*/
struct Triangle {
    /*!
        @brief Конструктор по умолчанию
        @return Объект класса
    */
    Triangle() = default;

    /*!
        @brief Конструктор
        @param [IN] verts - массив номеров вершин
        @return Объект класса
    */
    explicit Triangle(const std::vector<int>& verts)
        : verts(verts)
    {
    }

    /*!
        @brief Разбиение полигонона на полигоны-треугольники (Triangle)
        @return Массив полигонов-треугольников (Triangle)
    */
    std::vector<Triangle>* get_triangulated_faces();

    /*!
        @brief Массив номеров вершин
    */
    std::vector<int> verts {};
};

/*!
    @brief Класс, представляющий полигональную модель
*/
class Model : public Object {
public:
    /*!
        @brief Конструктор по умолчанию
        @return Объект класса
    */
    Model() = default;

    /*!
        @brief Конструктор
        @param [IN] points - массив точек некоторого геометрического объекта
        @param [IN] faces - массив полигонов-треугольников (Triangle) некоторого геометрического объекта
        @return Объект класса
    */
    Model(const std::vector<QVector3D>& points, const std::vector<Triangle>& faces);

    /*!
        @brief Конструктор, создающий модель, загружая её из файла формата OBJ
        @param [IN] file_name - имя входного файла (std::string)
        @return Объект класса
    */
    explicit Model(const std::string& file_name);

    /*!
        @brief Получение количества точек в модели
        @return size_t
    */
    size_t num_of_points() const;

    /*!
        @brief Получение количества полигонов в модели
        @return size_t
    */
    size_t num_of_faces() const;

    /*!
        @brief Получение точки по её индексу в массиве точек
        @param [IN] i - индекс точки в массиве точек (size_t)
        @return QVector3D&
    */
    const QVector3D& get_point(size_t i) const;
    /*!
        @brief Получение точки по её индексу в массиве точек для константной модели
        @param [IN] i - индекс точки в массиве точек (size_t)
        @return QVector3D&
    */
    QVector3D& get_point(size_t i);

    /*!
        @brief Получение полигона по его индексу в массиве полигонов для константной модели
        @param [IN] i - индекс полигона в массиве полигонов (size_t)
        @return QVector3D&
    */
    const Triangle& get_face(size_t i) const;

    /*!
        @brief Получение нормали к полигону
        @param [IN] face - полигон (Triangle)
        @param [IN] ray - луч (Ray)
        @return QVector3D
    */
    QVector3D get_normal(const Triangle& face, const Ray& ray) const;

    /*!
        @brief Поиск пересечения луча с моделью
        @param [IN] ray - луч (Ray)
        @return запись Intersection
    */
    virtual Intersection intersection(const Ray& ray) const override;

    /*!
        @brief Перемещение модели
        @param [IN] coeffs - коэффициенты переноса (QVector3D)
    */
    virtual void move(const QVector3D& coeffs) override;

    /*!
        @brief Масштабирование модели
        @param [IN] coeffs - коэффициенты масштабирования (QVector3D)
        @param [IN] center - центр масштабирования (QVector3D)
    */
    virtual void scale(const QVector3D& coeffs, const QVector3D& center) override;

    /*!
        @brief Масштабирование модели
        @param [IN] coeffs - коэффициенты масштабирования (QVector3D)
    */
    virtual void scale(const QVector3D& coeffs) override;

    /*!
        @brief Поворот модели
        @param [IN] coeffs - коэффициенты поворота (QVector3D)
        @param [IN] center - центр поворота (QVector3D)
    */
    virtual void rotate(const QVector3D& coeffs, const QVector3D& center) override;

    /*!
        @brief Поворот модели
        @param [IN] coeffs - коэффициенты поворота (QVector3D)
    */
    virtual void rotate(const QVector3D& coeffs) override;

    /*!
        @brief Сохранение модели в файл
        @param [IN] file_name - имя файла (std::string)
    */
    virtual void save(const std::string& file_name) override;

private:
    std::vector<QVector3D> _points;
    std::vector<Triangle> _faces;
    QVector3D _box_bounds[2] = {};
    QVector3D _corners[8] = {};

    bool _ray_face_intersect(const Ray& ray, const Triangle& face, float& ray_tvalue) const;

    void _update_corners();

    void _create_box();

    bool _ray_box_intersect(const Ray& ray) const;

    QVector3D _calculate_center();

    QVector3D _rotate_x(QVector3D point, const float& angle);

    QVector3D _rotate_y(QVector3D point, const float& angle);

    QVector3D _rotate_z(QVector3D point, const float& angle);

    virtual bool is_sphere() override { return false; }
};

#endif // MODEL_H
