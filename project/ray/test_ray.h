/**
 * @file test_ray.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса TestRay
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TESTRAY_H
#define TESTRAY_H

#include "ray.h"
#include <QObject>

/*!
    @brief Класс, представляющий тестирование класса Ray
    @details
    Оператор вызова функции:\n
    Тест №1 - оператор вызова функции (точка на луче на расстоянии 5.0)\n
    Получение вектора:\n
    Тест №1 - получение вектора луча с началом в точке (0, 0, 0), направление которого совпадает с Oz\n
*/
class TestRay : public QObject {
    Q_OBJECT
public:
    explicit TestRay(QObject* parent = nullptr);

private slots:
    void test_01_operator_call_func();

    void test_01_get_vector();
};

#endif // TESTRAY_H
