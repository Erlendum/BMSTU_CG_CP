/**
 * @file test_scene.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса TestScene
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "test_scene.h"
#include "model.h"
#include <QtTest/QtTest>

TestScene::TestScene(QObject* parent)
    : QObject { parent }
{
}

void TestScene::test_01_add_object()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto scene = Scene();
    scene.add_object(model);
    QCOMPARE(scene.get_objects().size(), 1);
}

void TestScene::test_01_remove_object()
{
    auto model = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto scene = Scene();
    scene.add_object(model);
    QCOMPARE(scene.get_objects().size(), 1);
    scene.remove_object(0);
    QCOMPARE(scene.get_objects().size(), 0);
}

void TestScene::test_01_add_light()
{
    auto scene = Scene();
    scene.add_light(QVector3D(0.0, 0.0, 0.0), Color(), 1.0);
    QCOMPARE(scene.get_lights().size(), 1);
}

void TestScene::test_01_remove_light()
{
    auto scene = Scene();
    scene.add_light(QVector3D(0.0, 0.0, 0.0), Color(), 1.0);
    QCOMPARE(scene.get_lights().size(), 1);
    scene.remove_light(0);
    QCOMPARE(scene.get_lights().size(), 0);
}

void TestScene::test_01_intersect()
{
    auto model_01 = std::make_shared<Model>(Model({ { -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto model_02 = std::make_shared<Model>(Model({ { -1.0, 0.0, -1.0 }, { 0.0, -1.0, -1.0 }, { 1.0, 0.0, -1.0 }, { -1.0, 1.0, 0.0 } },
        { Triangle(std::vector<int> { 0, 1, 2 }), { Triangle(std::vector<int> { 0, 3, 2 }) } }));
    auto ray = Ray({ 0.0, 0.0, 11.0 }, { 0.0, 0.0, -11.0 });
    auto scene = Scene();
    scene.add_object(model_01);
    scene.add_object(model_02);
    Intersection intersection;
    scene.intersect(ray, intersection);
    auto expected = QVector3D(0.0, 0.0, 0.0);
    QCOMPARE(intersection.point, expected);
}
