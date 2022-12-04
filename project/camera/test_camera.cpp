/**
 * @file test_camera.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса TestCamera
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "test_camera.h"
#include <QtTest/QtTest>

#define EPS 1E-2

TestCamera::TestCamera(QObject* parent)
    : QObject { parent }
{
}

void TestCamera::test_01_constructor()
{
    auto camera = Camera();
    QCOMPARE(camera.get_pos(), QVector3D(0.0, 0.0, 17.0));
    QCOMPARE(camera.get_look_at(), QVector3D(0.0, 0.0, 1.0));
}

void TestCamera::test_01_create_ray()
{
    auto camera = Camera(100, 100);
    camera.set_pos(QVector3D(0, 0, 11));
    camera.set_look_at(QVector3D(0, 0, 0));
    auto ray = camera.create_ray(50, 50);
    QCOMPARE(ray.get_src().x(), 0.0);
    QCOMPARE(ray.get_src().y(), 0.0);
    QCOMPARE(ray.get_src().z(), 11.0);

    auto check_01 = fabs(ray.get_dir().x() - 0.01) < EPS;
    auto check_02 = fabs(ray.get_dir().y() + 0.01) < EPS;
    auto check_03 = fabs(ray.get_dir().z() + 1.00) < EPS;
    QVERIFY(check_01);
    QVERIFY(check_02);
    QVERIFY(check_03);
}
