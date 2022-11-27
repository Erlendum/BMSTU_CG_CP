/**
 * @file scene.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса Scene
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SCENE_H
#define SCENE_H

#include "sphere.h"
#include <memory>
#include <vector>

#include "color.h"
#include "light.h"
#include "model.h"
#include <QVector3D>

/*!
    @brief Класс, представляющий сцену
*/
class Scene {
public:
    /*!
        @brief Конструктор по умолчанию
        @return Объект класса
    */
    Scene();

    /*!
        @brief Поиск пересечения луча со всеми объектами сцены
        @param [OUT] запись Intersection
        @param [IN] ray - луч (Ray)
        @return bool
    */
    bool intersect(const Ray& ray, Intersection& intersect);

    /*!
        @brief Добавление источника света на сцену
        @param [IN] position - расположение источника света в пространстве (QVector3D)
        @param [IN] color - цвет излучения источника света (Color)
        @param [IN] intensity - интенсивность излучения источника света (double)
    */
    void add_light(const QVector3D& position, const Color& color, const double& intensity);

    /*!
        @brief Удаление источника света со сцены
        @param [IN] i - индекс источника света в массиве источников света (size_t)
    */
    void remove_light(const size_t& i);

    /*!
        @brief Добавление объекта на сцену
        @param [IN] object - объект (Object)
    */
    void add_object(const std::shared_ptr<Object> object);

    /*!
        @brief Удаление объекта со сцены
        @param [IN] i - индекс объекта в массиве объектов (size_t)
    */
    void remove_object(const size_t& i);

    /*!
        @brief Получение всех объектов на сцене
        @return Массив объектов сцены
    */
    std::vector<std::shared_ptr<Object>> get_objects() const
    {
        return _objects;
    };

    /*!
        @brief Получение всех источников света на сцене
        @return Массив источников света на сцене
    */
    std::vector<std::shared_ptr<Light>> get_lights() const { return _lights; };

private:
    std::vector<std::shared_ptr<Object>> _objects;

    std::vector<std::shared_ptr<Light>> _lights;
};

#endif // SCENE_H
