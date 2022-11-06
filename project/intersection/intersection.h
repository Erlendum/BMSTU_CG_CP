#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "material.h"
#include <QVector3D>

struct Intersection {
    double dist;
    QVector3D point;
    QVector3D norm;
    Material material;
};

#endif // INTERSECTION_H
