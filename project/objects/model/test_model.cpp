/**
 * @file test_model.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса TestModel
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "test_model.h"
#include <QtTest/QtTest>
#include <iostream>

TestModel::TestModel(QObject* parent)
    : QObject { parent }
{
}

void TestModel::test_01_intersection()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto ray = Ray({ 0.0, 0.0, 11.0 }, { 0.0, 0.0, -11.0 });
    auto intersection = model->intersection(ray);
    auto expected = QVector3D(0.0, 0.0, 0.0);
    QCOMPARE(intersection.point, expected);
}

void TestModel::test_02_intersection()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto ray = Ray({ 0.0, 0.0, 11.0 }, { 1.0, 0.0, -11.0 });
    auto intersection = model->intersection(ray);
    auto expected = QVector3D(1.0, 0.0, 0.0);
    QCOMPARE(intersection.point, expected);
}

void TestModel::test_03_intersection()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto ray = Ray({ 0.0, 0.0, 11.0 }, { -1.0, 0.0, -11.0 });
    auto intersection = model->intersection(ray);
    auto expected = QVector3D(-1.0, 0.0, 0.0);
    QCOMPARE(intersection.point, expected);
}

void TestModel::test_04_intersection()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto ray = Ray({ 0.0, 0.0, 11.0 }, { 0.0, 1.0, -11.0 });
    auto intersection = model->intersection(ray);
    auto expected = QVector3D(0.0, 1.0, 0.0);
    QCOMPARE(intersection.point, expected);
}

void TestModel::test_05_intersection()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto ray = Ray({ 0.0, 0.0, 11.0 }, { 0.0, -1.0, -11.0 });
    auto intersection = model->intersection(ray);
    auto expected = QVector3D(0.0, -1.0, 0.0);
    QCOMPARE(intersection.point, expected);
}

void TestModel::test_01_load()
{
    std::cout.setstate(std::ios::failbit);
    auto model = Model("not_existing.txt");
    std::cout.clear();
    QCOMPARE(model.num_of_points(), 0);
    QCOMPARE(model.num_of_faces(), 0);
}

void TestModel::test_02_load()
{
    auto model = Model("../objects/floor.obj");
    QCOMPARE(model.num_of_points(), 4);
    QCOMPARE(model.num_of_faces(), 2);
}

void TestModel::test_03_load()
{
    auto model = Model("../objects/floor_one_poly.obj");
    QCOMPARE(model.num_of_points(), 4);
    QCOMPARE(model.num_of_faces(), 2);
}

void TestModel::test_01_move()
{
    auto model = std::make_shared<Model>(Model({ { 0.0, 0.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 0, 0 }) }));
    auto move_coeffs = QVector3D(1.0, 1.0, 1.0);
    model->move(move_coeffs);
    auto expected = QVector3D(1.0, 1.0, 1.0);
    QCOMPARE(model->get_point(0), expected);
}

void TestModel::test_01_scale()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto scale_coeffs = QVector3D(2.0, 2.0, 2.0);
    model->scale(scale_coeffs);
    auto expected_01 = QVector3D(-2.0, 0.0, 0.0);
    auto expected_02 = QVector3D(0.0, -2.0, 0.0);
    auto expected_03 = QVector3D(2.0, 0.0, 0.0);
    auto expected_04 = QVector3D(0.0, 2.0, 0.0);
    QCOMPARE(model->get_point(0), expected_01);
    QCOMPARE(model->get_point(1), expected_02);
    QCOMPARE(model->get_point(2), expected_03);
    QCOMPARE(model->get_point(3), expected_04);
}

void TestModel::test_02_scale()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto scale_coeffs = QVector3D(2.0, 2.0, 2.0);
    model->scale(scale_coeffs, model->get_center());
    auto expected_01 = QVector3D(-2.0, 0.0, 0.0);
    auto expected_02 = QVector3D(0.0, -2.0, 0.0);
    auto expected_03 = QVector3D(2.0, 0.0, 0.0);
    auto expected_04 = QVector3D(0.0, 2.0, 0.0);
    QCOMPARE(model->get_point(0), expected_01);
    QCOMPARE(model->get_point(1), expected_02);
    QCOMPARE(model->get_point(2), expected_03);
    QCOMPARE(model->get_point(3), expected_04);
}

void TestModel::test_01_rotate()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto rotate_coeffs = QVector3D(90, 90, 90);
    model->rotate(rotate_coeffs);
    auto expected_01 = QVector3D(0.0, 0.0, -1.0);
    auto expected_02 = QVector3D(0.0, 1.0, 0.0);
    auto expected_03 = QVector3D(0.0, 0.0, 1.0);
    auto expected_04 = QVector3D(0.0, -1.0, 0.0);

    QCOMPARE(model->get_point(0).x(), expected_01.x());
    QCOMPARE(model->get_point(0).y(), expected_01.y());
    QCOMPARE(model->get_point(0).z(), expected_01.z());

    QCOMPARE(model->get_point(1).x(), expected_02.x());
    QCOMPARE(model->get_point(1).y(), expected_02.y());
    QCOMPARE(model->get_point(1).z(), expected_02.z());

    QCOMPARE(model->get_point(2).x(), expected_03.x());
    QCOMPARE(model->get_point(2).y(), expected_03.y());
    QCOMPARE(model->get_point(2).z(), expected_03.z());

    QCOMPARE(model->get_point(3).x(), expected_04.x());
    QCOMPARE(model->get_point(3).y(), expected_04.y());
    QCOMPARE(model->get_point(3).z(), expected_04.z());
}

void TestModel::test_02_rotate()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto rotate_coeffs = QVector3D(90, 90, 90);
    model->rotate(rotate_coeffs, model->get_center());
    auto expected_01 = QVector3D(0.0, 0.0, -1.0);
    auto expected_02 = QVector3D(0.0, 1.0, 0.0);
    auto expected_03 = QVector3D(0.0, 0.0, 1.0);
    auto expected_04 = QVector3D(0.0, -1.0, 0.0);

    QCOMPARE(model->get_point(0).x(), expected_01.x());
    QCOMPARE(model->get_point(0).y(), expected_01.y());
    QCOMPARE(model->get_point(0).z(), expected_01.z());

    QCOMPARE(model->get_point(1).x(), expected_02.x());
    QCOMPARE(model->get_point(1).y(), expected_02.y());
    QCOMPARE(model->get_point(1).z(), expected_02.z());

    QCOMPARE(model->get_point(2).x(), expected_03.x());
    QCOMPARE(model->get_point(2).y(), expected_03.y());
    QCOMPARE(model->get_point(2).z(), expected_03.z());

    QCOMPARE(model->get_point(3).x(), expected_04.x());
    QCOMPARE(model->get_point(3).y(), expected_04.y());
    QCOMPARE(model->get_point(3).z(), expected_04.z());
}

void TestModel::test_01_save()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    model->save("/tmp/model.obj");
    auto new_model = Model("/tmp/model.obj");
    QCOMPARE(new_model.num_of_points(), 4);
    QCOMPARE(new_model.num_of_faces(), 2);
}
