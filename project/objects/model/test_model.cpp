#include "test_model.h"
#include <QtTest/QtTest>

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
