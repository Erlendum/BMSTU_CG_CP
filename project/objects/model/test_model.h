/**
 * @file test_model.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса TestModel
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TESTMODEL_H
#define TESTMODEL_H

#include "model.h"
#include <QObject>

/*!
    @brief Класс, представляющий тестирование класса Model
    @details Тест №1 - проверяется пересечение луча с одним полигоном, центр котрого расположен в начале координат, а луч также проходит через начало координат
    перпендикулярно плоскости полигона\n
    Тест №2 - проверяется пересечение луча с одним полигоном, центр котрого расположен в начале координат, а луч
    проходит через точку полиона с наибольшим значением x\n
    Тест №3 - проверяется пересечение луча с одним полигоном, центр котрого расположен в начале координат, а луч
    проходит через точку полиона с наименьшим значением x\n
    Тест №4 - проверяется пересечение луча с одним полигоном, центр котрого расположен в начале координат, а луч
    проходит через точку полиона с наибольшим значением y\n
    Тест №5 - проверяется пересечение луча с одним полигоном, центр котрого расположен в начале координат, а луч
    проходит через точку полиона с наименьшим значением y\n
*/
class TestModel : public QObject {
    Q_OBJECT
public:
    /*!
        @brief Конструктор
        @param [IN] parent - родительский класс QWidget
        @return Объект класса
    */
    explicit TestModel(QObject* parent = nullptr);

private slots:
    void test_01_intersection();
    void test_02_intersection();
    void test_03_intersection();
    void test_04_intersection();
    void test_05_intersection();
};

#endif // TESTMODEL_H
