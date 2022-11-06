#include "model.h"
#include "file_utils.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>

#define EPS 1e-6

Model::Model(const std::vector<QVector3D>& points, const std::vector<Triangle>& faces)
    : _points(points)
    , _faces(faces)
{
    this->_create_box();
    this->_update_corners();

    _center = _calculate_center();
}

Model::Model(const std::string& file_name)
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

            if (iterator->compare("v") == 0) {
                ++iterator;

                QVector3D v1;
                double x = stod(*iterator++);
                double y = stod(*iterator++);
                double z = stod(*iterator++);
                v1.setX(x);
                v1.setY(y);
                v1.setZ(z);

                if (current_line_tokens.size() == 5) {
                    ++iterator;
                }

                else if (current_line_tokens.size() == 7) {
                    ++iterator;
                    ++iterator;
                    ++iterator;
                } else if (current_line_tokens.size() == 8) {
                    ++iterator;
                }

                _points.emplace_back(v1);
            }

            else if (iterator->compare("vn") == 0) {
                ++iterator;

                ++iterator;
                ++iterator;
                ++iterator;
            }

            else if (iterator->compare("vt") == 0) {
                ++iterator;

            }

            else if (iterator->compare("f") == 0) {
                ++iterator;

                Triangle face;

                while (iterator != current_line_tokens.end()) {

                    QVector3D v1;

                    int index = stoi(*iterator++);
                    v1 = _points[index];
                    if (iterator != current_line_tokens.end() && iterator->compare("/") == 0) {
                        ++iterator;

                        if (iterator != current_line_tokens.end() && iterator->compare("/") != 0) {
                            ++iterator;

                            if (iterator != current_line_tokens.end() && iterator->compare("/") == 0) {
                                ++iterator;
                            }
                        } else {
                            ++iterator;
                        }
                        face.verts.push_back(index - 1);
                    }
                }

                if (face.verts.size() > 3) {
                    std::vector<Triangle>* triangulated_faces = face.get_triangulated_faces();
                    for (unsigned int i = 0; i < triangulated_faces->size(); i++) {
                        _faces.emplace_back(triangulated_faces->at(i));
                    }
                    delete triangulated_faces;

                } else
                    _faces.emplace_back(face);

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

    this->_create_box();
    this->_update_corners();
    this->set_material(*material);
    _center = _calculate_center();
}

size_t Model::num_of_points() const
{
    return this->_faces.size();
}

size_t Model::num_of_faces() const
{
    return this->_points.size();
}

const QVector3D& Model::get_point(size_t i) const
{
    return this->_points[i];
}

QVector3D& Model::get_point(size_t i)
{
    return this->_points[i];
}

const Triangle& Model::get_face(size_t i) const
{
    return this->_faces[i];
}

QVector3D Model::get_normal(const Triangle& face, const Ray& ray) const
{
    QVector3D edge1 = get_point(face.verts[1]) - get_point(face.verts[0]);
    QVector3D edge2 = get_point(face.verts[2]) - get_point(face.verts[0]);

    QVector3D n = QVector3D::crossProduct(edge1, edge2);

    n.normalize();

    if (QVector3D::dotProduct(n, ray.get_dst()) > 0) {
        n *= -1;
    }

    return n;
}

Intersection Model::intersection(const Ray& ray) const
{
    Intersection intersectPoint;
    intersectPoint.dist = 0.0;

    if (!this->_ray_box_intersect(ray))
        return intersectPoint;

    float faceDist = std::numeric_limits<float>::max();
    float currDist;
    Triangle face;

    std::vector<Triangle>::const_iterator face_it;

    for (auto it = _faces.begin(); it != _faces.end(); ++it) {
        if (this->_ray_face_intersect(ray, *it, currDist) && fabs(currDist) < faceDist) {
            faceDist = currDist;
            face = *it;
            face_it = it;
        }
    }

    if (faceDist == std::numeric_limits<float>::max())
        return intersectPoint;

    intersectPoint.norm = this->get_normal(face, ray);
    intersectPoint.dist = faceDist;
    intersectPoint.point = ray.get_src() + ray.get_dst() * faceDist;
    intersectPoint.material = this->get_material();

    return intersectPoint;
}

void Model::move(const QVector3D& coeffs)
{
    for (size_t i = 0; i < _points.size(); i++)
        _points[i] += coeffs;

    this->_create_box();
    this->_update_corners();
    _center = this->_calculate_center();
}

void Model::scale(const QVector3D& coeffs)
{
    auto center = this->get_center();

    for (size_t i = 0; i < _points.size(); i++) {
        _points[i] -= center;

        _points[i].setX(coeffs[0] * _points[i].x());
        _points[i].setY(coeffs[1] * _points[i].y());
        _points[i].setZ(coeffs[2] * _points[i].z());

        _points[i] += center;
    }

    this->_create_box();
    this->_update_corners();
    _center = this->_calculate_center();
}

void Model::rotate(const QVector3D& coeffs)
{
    auto center = this->get_center();

    for (size_t i = 0; i < _points.size(); i++) {
        _points[i] -= center;

        _points[i] = this->_rotate_x(_points[i], coeffs[0]);
        _points[i] = this->_rotate_y(_points[i], coeffs[1]);
        _points[i] = this->_rotate_z(_points[i], coeffs[2]);

        _points[i] += center;
    }

    this->_create_box();
    this->_update_corners();
    _center = this->_calculate_center();
}

void Model::save(const std::string& file_name)
{
    std::shared_ptr<std::ofstream> output = std::make_shared<std::ofstream>();
    output->open(file_name, std::ifstream::out);
    if (!output->is_open()) {
        std::cout << "ERROR. File" << file_name << "not found" << std::endl;
        return;
    }
    for (size_t i = 0; i < _points.size(); i++)
        *output << "v " << _points[i].x() << " " << _points[i].y() << " " << _points[i].z() << std::endl;

    for (size_t i = 0; i < _faces.size(); i++)
        *output << "f " << _faces[i].verts[0] + 1 << "// " << _faces[i].verts[1] + 1 << "// " << _faces[i].verts[2] + 1 << "//" << std::endl;

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

bool Model::_ray_face_intersect(const Ray& ray, const Triangle& face, float& ray_tvalue) const
{
    //  find vectors for two edges sharing vertex[0]
    QVector3D edge1 = get_point(face.verts[1]) - get_point(face.verts[0]);
    QVector3D edge2 = get_point(face.verts[2]) - get_point(face.verts[0]);

    //   begin calc determinant - also used to calc U parameter
    QVector3D pvec = QVector3D::crossProduct(ray.get_dst(), edge2);
    float det = QVector3D::dotProduct(edge1, pvec);

    //   ray lies in plane of triangle
    if (fabs(det) < EPS)
        return false;

    auto inv_det = 1. / det;

    //   calc dist from vertex[0] to ray source
    QVector3D tvec = ray.get_src() - get_point(face.verts[0]);

    //  calculate bary_u parameter and test bounds
    float bary_u = QVector3D::dotProduct(tvec, pvec) * inv_det;
    if (bary_u < 0.0 || bary_u > 1.0)
        return false;

    //  bary_v (barycenter)
    QVector3D qvec = QVector3D::crossProduct(tvec, edge1);
    float bary_v = QVector3D::dotProduct(ray.get_dst(), qvec) * inv_det;

    // test bounds
    if (bary_v < 0.0 || bary_u + bary_v > 1.0)
        return false;

    ray_tvalue = static_cast<float>(QVector3D::dotProduct(edge2, qvec) * inv_det);

    return ray_tvalue > EPS;
}

void Model::_update_corners()
{
    auto pmin = this->_box_bounds[0];
    auto pmax = this->_box_bounds[1];

    _corners[0] = pmin;
    _corners[1] = QVector3D { pmin.x(), pmin.y(), pmax.z() };
    _corners[2] = QVector3D { pmin.x(), pmax.y(), pmin.z() };
    _corners[3] = QVector3D { pmax.x(), pmin.y(), pmin.z() };
    _corners[4] = QVector3D { pmin.x(), pmax.y(), pmax.z() };
    _corners[5] = QVector3D { pmax.x(), pmin.y(), pmax.z() };
    _corners[6] = QVector3D { pmax.x(), pmax.y(), pmin.z() };
    _corners[7] = pmax;
}

void Model::_create_box()
{
    auto p_min = QVector3D { 1.0, 1.0, 1.0 } * std::numeric_limits<float>::max();
    auto p_max = QVector3D { 1.0, 1.0, 1.0 } * std::numeric_limits<float>::min();

    for (const auto& p : this->_points) {
        for (int i = 0; i < 3; ++i) {
            p_min[i] = std::min(p_min[i], p[i]);
            p_max[i] = std::max(p_max[i], p[i]);
        }
    }

    this->_box_bounds[0] = p_min;
    this->_box_bounds[1] = p_max;
}

bool Model::_ray_box_intersect(const Ray& ray) const
{
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (this->_box_bounds[ray.get_sign()[0]].x() - ray.get_src().x()) * ray.get_inv_dst().x();
    tmax = (this->_box_bounds[1 - ray.get_sign()[0]].x() - ray.get_src().x()) * ray.get_inv_dst().x();
    tymin = (this->_box_bounds[ray.get_sign()[1]].y() - ray.get_src().y()) * ray.get_inv_dst().y();
    tymax = (this->_box_bounds[1 - ray.get_sign()[1]].y() - ray.get_src().y()) * ray.get_inv_dst().y();

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (this->_box_bounds[ray.get_sign()[2]].z() - ray.get_src().z()) * ray.get_inv_dst().z();
    tzmax = (this->_box_bounds[1 - ray.get_sign()[2]].z() - ray.get_src().z()) * ray.get_inv_dst().z();

    return ((tmin <= tzmax) && (tzmin <= tmax));
}

QVector3D Model::_calculate_center()
{
    QVector3D sum = { 0, 0, 0 };
    for (size_t i = 0; i < _points.size(); i++)
        sum += _points[i];
    return sum / _points.size();
}

inline float degrees_to_radians(const float& angle)
{
    return M_PI / 180.0 * angle;
}

QVector3D Model::_rotate_x(QVector3D point, const float& angle)
{
    auto _cos = (float)cos(degrees_to_radians(angle));
    auto _sin = (float)sin(degrees_to_radians(angle));
    auto _y = point.y();

    point.setY(point.y() * _cos - point.z() * _sin);
    point.setZ(point.z() * _cos + _y * _sin);

    return point;
}

QVector3D Model::_rotate_y(QVector3D point, const float& angle)
{
    auto _cos = (float)cos(degrees_to_radians(angle));
    auto _sin = (float)sin(degrees_to_radians(angle));
    auto _x = point.x();

    point.setX(point.x() * _cos - point.z() * _sin);
    point.setZ(point.z() * _cos + _x * _sin);

    return point;
}

QVector3D Model::_rotate_z(QVector3D point, const float& angle)
{
    auto _cos = (float)cos(degrees_to_radians(angle));
    auto _sin = (float)sin(degrees_to_radians(angle));
    auto _x = point.x();

    point.setX(point.x() * _cos - point.y() * _sin);
    point.setY(point.y() * _cos + _x * _sin);

    return point;
}

std::vector<Triangle>* Triangle::get_triangulated_faces()
{
    std::vector<Triangle>* result = new std::vector<Triangle>();

    if (verts.size() < 4) {
        result->emplace_back(*this);
        return result;
    }

    int v1_index = verts[0];

    int index = 1;
    int last_index = verts.size() - 1;
    while (index < last_index) {
        Triangle face(*this);
        face.verts.clear();

        face.verts.push_back(v1_index);

        face.verts.push_back(verts[index]);
        face.verts.push_back(verts[index + 1]);
        index++;

        result->emplace_back(face);
    }

    return result;
}
