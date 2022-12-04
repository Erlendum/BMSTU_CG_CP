/**
 * @file test_color.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса TestColor
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "test_color.h"
#include <QtTest/QtTest>
#include <cmath>

#define EPS 1e-2

TestColor::TestColor(QObject* parent)
    : QObject { parent }
{
}

void TestColor::test_01_mul_operator()
{
    auto color_01 = Color();
    auto color_02 = Color(1.0, 1.0, 1.0);
    auto res = color_01 * color_02;
    auto check_01 = fabs(res.r) < EPS;
    auto check_02 = fabs(res.g) < EPS;
    auto check_03 = fabs(res.b) < EPS;
    QVERIFY(check_01);
    QVERIFY(check_02);
    QVERIFY(check_03);
}

void TestColor::test_02_mul_operator()
{
    auto color = Color(0.5, 0.5, 0.5);
    auto res = color * 2.0;
    auto check_01 = fabs(res.r - 1.0) < EPS;
    auto check_02 = fabs(res.g - 1.0) < EPS;
    auto check_03 = fabs(res.b - 1.0) < EPS;
    QVERIFY(check_01);
    QVERIFY(check_02);
    QVERIFY(check_03);
}

void TestColor::test_01_sum_operator()
{
    auto color_01 = Color();
    auto color_02 = Color();
    color_02.r = 1.0;
    color_02.g = 1.0;
    color_02.b = 1.0;
    auto res = color_01 + color_02;
    auto check_01 = fabs(res.r - 1.0) < EPS;
    auto check_02 = fabs(res.g - 1.0) < EPS;
    auto check_03 = fabs(res.b - 1.0) < EPS;
    QVERIFY(check_01);
    QVERIFY(check_02);
    QVERIFY(check_03);
}

void TestColor::test_01_mul_assign_operator()
{
    auto color = Color(0.5, 0.5, 0.5);
    color *= Color();
    auto check_01 = fabs(color.r) < EPS;
    auto check_02 = fabs(color.g) < EPS;
    auto check_03 = fabs(color.b) < EPS;
    QVERIFY(check_01);
    QVERIFY(check_02);
    QVERIFY(check_03);
}

void TestColor::test_01_sum_assign_operator()
{
    auto color = Color(0.5, 0.5, 0.5);
    color += Color();
    auto check_01 = fabs(color.r - 0.5) < EPS;
    auto check_02 = fabs(color.g - 0.5) < EPS;
    auto check_03 = fabs(color.b - 0.5) < EPS;
    QVERIFY(check_01);
    QVERIFY(check_02);
    QVERIFY(check_03);
}

void TestColor::test_01_set_color()
{
    auto color = Color(0.5, 0.5, 0.5);
    color.set_color(0.2, 0.2, 0.2);
    auto check_01 = fabs(color.r - 0.2) < EPS;
    auto check_02 = fabs(color.g - 0.2) < EPS;
    auto check_03 = fabs(color.b - 0.2) < EPS;
    QVERIFY(check_01);
    QVERIFY(check_02);
    QVERIFY(check_03);
}

void TestColor::test_01_normalize()
{
    auto color = Color(2.0, 1.9, 3.56);
    color.normalize();
    auto check_01 = fabs(color.r - 1.0) < EPS;
    auto check_02 = fabs(color.g - 1.0) < EPS;
    auto check_03 = fabs(color.b - 1.0) < EPS;
    QVERIFY(check_01);
    QVERIFY(check_02);
    QVERIFY(check_03);
}

void TestColor::test_01_eq_operator()
{
    auto color_01 = Color();
    auto color_02 = Color(1.0, 1.0, 1.0);
    QVERIFY(!(color_01 == color_02));
}

void TestColor::test_02_eq_operator()
{
    auto color_01 = Color(1.0, 1.0, 1.0);
    auto color_02 = Color(1.0, 1.0, 1.0);
    QVERIFY(color_01 == color_02);
}
