/**
 * @file test_scene.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса TestScene
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "scene.h"
#include <QObject>

/*!
    @brief Класс, представляющий тестирование класса Scene
    @details
    Добавление объекта на сцену:\n
    Тест №1 - добавление одного объекта на пустую сцену\n
    Удаление объекта со сцены:\n
    Тест №1 - удаление единственного объекта со сцены\n
    Добавление источника света на сцену:\n
    Тест №1 - добавление одного источника света на пустую сцену\n
    Удаление источника света со сцены:\n
    Тест №1 - удаление единственного источника света со сцены\n
    Поиск пересечения луча со сценой:\n
    Тест №1 - поиск пересечения луча со сценой, состоящей из двух квадратов, расположенных друг за другом\n
*/
class TestScene : public QObject {
    Q_OBJECT
public:
    explicit TestScene(QObject* parent = nullptr);

private slots:
    void test_01_add_object();

    void test_01_remove_object();

    void test_01_add_light();

    void test_01_remove_light();

    void test_01_intersect();
};

#endif // TESTSCENE_H
