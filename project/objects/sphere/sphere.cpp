/**
 * @file sphere.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса Sphere
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "sphere.h"
#include <QVector3D>
#include <cmath>
#include <file_utils.h>
#include <fstream>
#include <iostream>
#include <memory>

Sphere::Sphere()
    : _radius(0)
{
}

Sphere::Sphere(const QVector3D& center, double radius)
    : Object(center)
    , _radius(radius)
{
}

Sphere::Sphere(const std::string& file_name)
{
    std::shared_ptr<std::ifstream> input = std::make_shared<std::ifstream>();
    input->open(file_name);
    if (!input->is_open()) {
        std::cout << "ERROR. File" << file_name << "not found" << std::endl;
        return;
    }

    auto material = std::make_shared<Material>(Material());
    while (!input->eof()) {
        std::string current_line;
        getline(*input, current_line);
        std::list<std::string> current_line_tokens = interpret_line(current_line);

        std::list<std::string>::iterator iterator = current_line_tokens.begin();
        while (iterator != current_line_tokens.end()) {

            if (iterator->compare("c") == 0) {
                ++iterator;
                _center.setX(stod(*iterator++));
                _center.setY(stod(*iterator++));
                _center.setZ(stod(*iterator++));
            }

            else if (iterator->compare("r") == 0) {
                ++iterator;
                _radius = stod(*iterator++);
            } else if (iterator->compare("ambient_color") == 0) {
                ++iterator;
                Color c;
                c.r = stod(*iterator++);
                c.g = stod(*iterator++);
                c.b = stod(*iterator++);
                material->set_ambient(c);
            } else if (iterator->compare("diffuse_color") == 0) {
                ++iterator;
                Color c;
                c.r = stod(*iterator++);
                c.g = stod(*iterator++);
                c.b = stod(*iterator++);
                material->set_diffuse(c);
            } else if (iterator->compare("specular_color") == 0) {
                ++iterator;
                Color c;
                c.r = stod(*iterator++);
                c.g = stod(*iterator++);
                c.b = stod(*iterator++);
                material->set_specular(c);
            } else if (iterator->compare("ka") == 0) {
                ++iterator;
                material->set_ka(stoi(*iterator++));
            } else if (iterator->compare("kd") == 0) {
                ++iterator;
                material->set_kd(stoi(*iterator++));
            } else if (iterator->compare("ks") == 0) {
                ++iterator;
                material->set_ks(stoi(*iterator++));
            } else if (iterator->compare("k") == 0) {
                ++iterator;
                material->set_k(stoi(*iterator++));
            } else if (iterator->compare("k_refl") == 0) {
                ++iterator;
                material->set_k_refl(stoi(*iterator++));
            } else if (iterator->compare("k_refr") == 0) {
                ++iterator;
                material->set_k_refr(stoi(*iterator++));
            } else if (iterator->compare("refraction_index") == 0) {
                ++iterator;
                material->set_refraction_index(stoi(*iterator++));
            } else {
                ++iterator;
            }
        }
    }

    input->close();

    this->set_material(*material);
}

Intersection Sphere::intersection(const Ray& ray) const
{
    QVector3D c = QVector3D(_center.x(), _center.y(), _center.z());
    QVector3D src = ray.get_src();
    QVector3D dst = ray.get_dir();

    double eqa = QVector3D::dotProduct(dst, dst);

    double eqb = 2 * (QVector3D::dotProduct(src, dst) - QVector3D::dotProduct(dst, c));
    double eqc = QVector3D::dotProduct(c, c) - QVector3D::dotProduct(c, src) * 2 + QVector3D::dotProduct(src, src) - _radius * _radius;

    double delta = eqb * eqb - 4 * eqa * eqc;

    Intersection intersectPoint;
    intersectPoint.dist = 0.0;

    if (delta < 0) {
        return intersectPoint;
    } else if (delta == 0) {
        Intersection intersectPoint;
        intersectPoint.dist = -eqb / (2 * eqa);
        intersectPoint.point = src + dst * intersectPoint.dist;
        intersectPoint.material = this->_material;
        intersectPoint.norm = this->get_normal(intersectPoint.point);
    } else {

        double sqrtDelta = sqrtf(delta);
        double t0 = (-eqb - sqrtDelta) / (2 * eqa);
        double t1 = (-eqb + sqrtDelta) / (2 * eqa);

        double smallest = (t0 < t1) ? t0 : t1;

        intersectPoint.dist = smallest;
        intersectPoint.point = src + dst * intersectPoint.dist;
        intersectPoint.norm = this->get_normal(intersectPoint.point);
        intersectPoint.material = this->_material;
    }

    return intersectPoint;
}

void Sphere::move(const QVector3D& coeffs)
{
    _center += coeffs;
}

void Sphere::scale(const QVector3D& coeffs)
{
    _radius *= coeffs[0];
}

void Sphere::rotate(const QVector3D& coeffs)
{
}

void Sphere::save(const std::string& file_name)
{
    std::shared_ptr<std::ofstream> output = std::make_shared<std::ofstream>();
    output->open(file_name, std::ifstream::out);
    if (!output->is_open()) {
        std::cout << "ERROR. File" << file_name << "not found" << std::endl;
        return;
    }

    *output << "c " << _center.x() << " " << _center.y() << " " << _center.z() << std::endl;

    *output << "r " << _radius << std::endl;

    *output << "ambient_color " << this->get_material().get_ambient().r << " " << this->get_material().get_ambient().g << " " << this->get_material().get_ambient().b << std::endl;
    *output << "diffuse_color " << this->get_material().get_diffuse().r << " " << this->get_material().get_diffuse().g << " " << this->get_material().get_diffuse().b << std::endl;
    *output << "specular_color " << this->get_material().get_specular().r << " " << this->get_material().get_specular().g << " " << this->get_material().get_specular().b << std::endl;
    *output << "ka " << this->get_material().get_ka() << std::endl;
    *output << "kd " << this->get_material().get_kd() << std::endl;
    *output << "ks " << this->get_material().get_ks() << std::endl;
    *output << "k " << this->get_material().get_k() << std::endl;
    *output << "k_refl " << this->get_material().get_k_refl() << std::endl;
    *output << "k_refr " << this->get_material().get_k_refr() << std::endl;
    *output << "refraction_index " << this->get_material().get_refraction_index() << std::endl;

    output->close();
}
