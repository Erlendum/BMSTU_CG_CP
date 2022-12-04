/**
 * @file test_camera.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса TestCamera
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include "model.h"
#include <QObject>

#include "camera.h"

/*!
    @brief Класс, представляющий тестирование класса Camera
    @details
    Конструктор:\n
    Тест №1 - конструктор по умолчанию\n
    Создание луча:\n
    Тест №1 - луч, направленный в центр картинной плоскости\n

*/
class TestCamera : public QObject {
    Q_OBJECT
public:
    /*!
        @brief Конструктор
        @param [IN] parent - родительский класс QWidget
        @return Объект класса
    */
    explicit TestCamera(QObject* parent = nullptr);

private slots:
    void test_01_constructor();

    void test_01_create_ray();
};

#endif // TESTCAMERA_H
