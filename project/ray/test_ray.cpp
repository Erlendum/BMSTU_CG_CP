/**
 * @file test_ray.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса TestRay
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "test_ray.h"
#include <QtTest/QtTest>

TestRay::TestRay(QObject* parent)
    : QObject { parent }
{
}

void TestRay::test_01_operator_call_func()
{
    auto ray = Ray(QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0));
    auto res = ray(5.0);
    QCOMPARE(res.x(), 0.0);
    QCOMPARE(res.y(), 0.0);
    QCOMPARE(res.z(), 5.0);
}

void TestRay::test_01_get_vector()
{
    auto ray = Ray(QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0));
    auto res = ray.get_vector();
    QCOMPARE(res.x(), 0.0);
    QCOMPARE(res.y(), 0.0);
    QCOMPARE(res.z(), -1.0);
}
