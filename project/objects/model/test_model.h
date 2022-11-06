#ifndef TESTMODEL_H
#define TESTMODEL_H

#include "model.h"
#include <QObject>

class TestModel : public QObject {
    Q_OBJECT
public:
    explicit TestModel(QObject* parent = nullptr);

private slots:
    void test_01_intersection();
};

#endif // TESTMODEL_H
