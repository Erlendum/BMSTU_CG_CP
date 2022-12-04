/**
 * @file mainwindow.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса MainWindow
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "mainwindow.h"
#include "color.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageAuthenticationCode>
#include <QMessageBox>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <thread>

#define EPS 1e-6
#define BUFLEN 10

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _size_x = 620;
    _size_y = 620;

    N = 7;

    _output_file = "";

    connect(_ui->loadFromFileButton, SIGNAL(triggered()), this, SLOT(menu_loadButton_clicked()));
    connect(_ui->saveToFileButton, SIGNAL(triggered()), this, SLOT(menu_saveButton_clicked()));
    connect(_ui->loadSceneButton, SIGNAL(triggered()), this, SLOT(menu_loadSceneButton_clicked()));
    connect(_ui->saveSceneButton, SIGNAL(triggered()), this, SLOT(menu_saveSceneButton_clicked()));

    connect(_ui->exit, SIGNAL(triggered()), this, SLOT(exit_messagebox()));

    _ui->geometry->setChecked(true);
    _ui->stackedWidget->setCurrentIndex(0);

    create_scene();

    for (size_t i = 0; i < _scene.get_lights().size(); i++) {
        char buf[BUFLEN];
        snprintf(buf, sizeof(buf), "light_%02zu", i);
        _ui->lightsBox->addItem(buf);
    }
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::exit_messagebox()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход", "Вы уверены, что хотите выйти?",
        QMessageBox::Ok | QMessageBox::Cancel);
    if (reply == QMessageBox::Ok) {
        QApplication::quit();
    }
}

void MainWindow::create_scene()
{

    //    _scene.add_light(QVector3D { 0, 0.11, 1 }, Color(1.0, 1.0, 1.0), 0.85);
    _scene.add_light(QVector3D { 0.209923, 5.14763, -0.267231 }, Color(1.0, 1.0, 1.0), 0.85);

    //    _scene.add_light(QVector3D { 0, 2, 11 }, Color(1.0, 1.0, 1.0), 1.0);
    _camera = std::make_shared<Camera>(Camera(_size_x, _size_y));
    _camera->set_pos(QVector3D(0, 2, 11));
    _camera->set_look_at(QVector3D { 0, 0, 0 });
}

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

void MainWindow::render()
{
    QImage image = QImage(_size_x, _size_y, QImage::Format_RGB32);

    for (int i = 0; i < _size_x; i++) {
        for (int j = 0; j < _size_y; j++) {
            Color color;
            Ray ray = _camera->create_ray(i, j);
            color = _cast_ray(color, ray);
            image.setPixel(i, j, qRgb(color.r * 255, color.g * 255, color.b * 255));
        }
    }
    QGraphicsScene* scene = new QGraphicsScene(this);

    scene->addPixmap(QPixmap::fromImage(image));

    _ui->canvas->setScene(scene);

    if (_output_file != "")
        image.save(_output_file.c_str(), "PNG");
}

void MainWindow::render_parallel(int nth)
{
    QImage image = QImage(_size_x, _size_y, QImage::Format_RGB32);

    std::vector<std::thread> threads(nth);
    std::vector<Color> colors(nth);
    std::vector<std::pair<int, int>> coords(nth);
    int k = 0;
    for (int l = 0; l < _size_x; l++) {
        for (int c = 0; c < _size_y; c++) {
            if (k == nth) {
                for (int i = 0; i < nth; i++)
                    threads[i].join();
                for (int i = 0; i < nth; i++)
                    image.setPixel(coords[i].first, coords[i].second, qRgb(colors[i].r * 255, colors[i].g * 255, colors[i].b * 255));
                k = 0;
            }
            Ray ray = _camera->create_ray(l, c);
            threads[k] = std::thread(&MainWindow::_cast_ray, this, std::ref(colors[k]), ray, 0);
            coords[k] = std::pair<int, int>(l, c);
            k++;
        }
    }
    for (int i = 0; i < nth; i++)
        threads[i].join();
    for (int i = 0; i < nth; i++)
        image.setPixel(coords[i].first, coords[i].second, qRgb(colors[i].r * 255, colors[i].g * 255, colors[i].b * 255));

    QGraphicsScene* scene = new QGraphicsScene(this);

    scene->addPixmap(QPixmap::fromImage(image));

    _ui->canvas->setScene(scene);

    if (_output_file != "")
        image.save(_output_file.c_str(), "PNG");
}

void MainWindow::set_output_file(const std::string& file_name)
{
    _output_file = file_name;
}

void MainWindow::set_N(const int& n)
{
    N = n;
}

void MainWindow::set_size_x(const int& size_x)
{
    _size_x = size_x;
}

void MainWindow::set_size_y(const int& size_y)
{
    _size_y = size_y;
}

QVector3D MainWindow::_reflects(QVector3D raio, QVector3D norm)
{
    raio = -raio;
    QVector3D reflect = raio - (norm * (2.0 * QVector3D::dotProduct(raio, norm)));
    reflect.normalize();
    return reflect;
}

QVector3D MainWindow::_refract(QVector3D raio, QVector3D norm, double refractive_index)
{
    double cosi = -std::max(-1.f, std::min(1.f, QVector3D::dotProduct(raio, norm)));
    double etai = 1, etat = refractive_index;
    QVector3D n = norm;
    if (cosi < 0) {
        return _refract(raio, -norm, refractive_index);
    }
    double eta = etai / etat;
    double k = 1 - eta * eta * (1 - cosi * cosi);

    return k < 0 ? QVector3D(1, 0, 0) : raio * eta + n * (eta * cosi - sqrtf(k));
}

void MainWindow::on_render_button_clicked()
{
    render_parallel(4);
}

Color MainWindow::_cast_ray(Color& buf_color, const Ray ray, const int depth)
{
    Intersection intersect;

    Color color;

    if (_scene.intersect(ray, intersect) && depth <= N) {

        QVector3D reflect_dir = _reflects(-ray.get_dir(), intersect.norm);
        reflect_dir.normalize();
        QVector3D reflect_orig = QVector3D::dotProduct(reflect_dir, intersect.norm) < 0 ? intersect.point - intersect.norm * 1e-3 : intersect.point + intersect.norm * 1e-3;

        Color reflect_color;
        if (intersect.material.get_k_refl() > 0)
            reflect_color = _cast_ray(buf_color, Ray(reflect_orig, reflect_dir), depth + 1);

        QVector3D refract_dir = _refract(ray.get_dir(), intersect.norm, intersect.material.get_refraction_index());
        refract_dir.normalize();
        QVector3D refract_orig = QVector3D::dotProduct(refract_dir, intersect.norm) < 0 ? intersect.point - intersect.norm * 1e-3 : intersect.point + intersect.norm * 1e-3;
        Color refract_color;
        if (intersect.material.get_k_refr() > 0)
            refract_color = _cast_ray(buf_color, Ray(refract_orig, refract_dir), depth + 1);

        for (size_t k = 0; k < _scene.get_lights().size(); k++) {
            QVector3D L = _scene.get_lights()[k]->get_position() - intersect.point;
            L.normalize();

            double fator_dif = QVector3D::dotProduct(L, intersect.norm);

            double light_dist = (_scene.get_lights()[k]->get_position() - intersect.point).length();

            QVector3D shadow_orig = fator_dif <= EPS ? intersect.point - intersect.norm * 1e-3 : intersect.point + intersect.norm * 1e-3;

            Intersection tmp_intersect;

            Ray tmp_ray = Ray(shadow_orig, L);

            if (_scene.intersect(tmp_ray, tmp_intersect) && (tmp_intersect.point - shadow_orig).length() < light_dist && fabs(tmp_intersect.material.get_k_refr()) < EPS) {
                continue;
            }

            if (fator_dif <= EPS)
                fator_dif = 0.0;

            // AMBIENT COEFFICIENT
            color.r = (intersect.material.get_ambient().r * intersect.material.get_ka());
            color.g = (intersect.material.get_ambient().g * intersect.material.get_ka());
            color.b = (intersect.material.get_ambient().b * intersect.material.get_ka());

            // DIFFUSE COEFFICIENT
            color.r = color.r + _scene.get_lights()[k]->get_color().r * _scene.get_lights()[k]->get_intensity() * fator_dif * intersect.material.get_diffuse().r * intersect.material.get_kd();
            color.g = color.g + _scene.get_lights()[k]->get_color().g * _scene.get_lights()[k]->get_intensity() * fator_dif * intersect.material.get_diffuse().g * intersect.material.get_kd();
            color.b = color.b + _scene.get_lights()[k]->get_color().b * _scene.get_lights()[k]->get_intensity() * fator_dif * intersect.material.get_diffuse().b * intersect.material.get_kd();

            QVector3D reflexao = _reflects(L, intersect.norm);
            double fator_esp = QVector3D::dotProduct(ray.get_vector(), reflexao);
            if (fator_esp <= EPS)
                fator_esp = 0.0;

            // SPECULAR COEFFICIENT
            color.r = color.r + _scene.get_lights()[k]->get_color().r * _scene.get_lights()[k]->get_intensity() * pow(fator_esp, intersect.material.get_k()) * intersect.material.get_specular().r * intersect.material.get_ks();
            color.g = color.g + _scene.get_lights()[k]->get_color().g * _scene.get_lights()[k]->get_intensity() * pow(fator_esp, intersect.material.get_k()) * intersect.material.get_specular().g * intersect.material.get_ks();
            color.b = color.b + _scene.get_lights()[k]->get_color().b * _scene.get_lights()[k]->get_intensity() * pow(fator_esp, intersect.material.get_k()) * intersect.material.get_specular().b * intersect.material.get_ks();

            // REFLECTION
            color.r = color.r + reflect_color.r * intersect.material.get_k_refl();
            color.g = color.g + reflect_color.g * intersect.material.get_k_refl();
            color.b = color.b + reflect_color.b * intersect.material.get_k_refl();

            // REFRACTION
            color.r = color.r + refract_color.r * intersect.material.get_k_refr();
            color.g = color.g + refract_color.g * intersect.material.get_k_refr();
            color.b = color.b + refract_color.b * intersect.material.get_k_refr();
        }
        color.normalize();
    } else {
        color = Color(0.07, 0.07, 0.07);
    }
    buf_color = color;
    return color;
}

void MainWindow::on_moveButton_clicked()
{
    auto i = _ui->modelsBox->currentIndex();

    if (i != -1) {

        _scene.get_objects()[i]->move(QVector3D(_ui->moveXSpinBox->value(), _ui->moveYSpinBox->value(), _ui->moveZSpinBox->value()));

        render();
    }
}

void MainWindow::on_scaleButton_clicked()
{
    auto i = _ui->modelsBox->currentIndex();

    if (i != -1) {

        _scene.get_objects()[i]->scale(QVector3D(_ui->scaleXSpinBox->value(), _ui->scaleYSpinBox->value(), _ui->scaleZSpinBox->value()));

        render();
    }
}

void MainWindow::on_rotateButton_clicked()
{
    auto i = _ui->modelsBox->currentIndex();

    if (i != -1) {
        _scene.get_objects()[i]->rotate(QVector3D(_ui->rotateXSpinBox->value(), _ui->rotateYSpinBox->value(), _ui->rotateZSpinBox->value()));

        render();
    }
}

void MainWindow::_load_object(std::string& file_name)
{
    if (file_name.find("sphere") != std::string::npos) {
        auto sphere = std::make_shared<Sphere>(Sphere(file_name));
        _scene.add_object(sphere);
    } else {
        auto model = std::make_shared<Model>(Model(file_name));
        _scene.add_object(model);
    }

    _ui->modelsBox->addItem(QString::fromUtf8(file_name.c_str()));
    _ui->modelsBox_2->addItem(QString::fromUtf8(file_name.c_str()));
    _ui->modelsBox->setCurrentIndex(_ui->modelsBox->count() - 1);
}

void MainWindow::_save_object(std::string& file_name, const size_t& i)
{
    _scene.get_objects()[i]->save(file_name);
}

void MainWindow::menu_loadButton_clicked()
{
    QString fname_tmp1 = QFileDialog::getOpenFileName();

    if (fname_tmp1.isNull())
        return;

    QByteArray fname_tmp2 = fname_tmp1.toUtf8();
    std::string fname = fname_tmp2.data();

    _load_object(fname);

    render();
}

void MainWindow::menu_saveButton_clicked()
{
    QString fname_tmp1 = QFileDialog::getSaveFileName();

    if (fname_tmp1.isNull())
        return;

    QByteArray fname_tmp2 = fname_tmp1.toUtf8();
    std::string fname = fname_tmp2.data();

    auto i = _ui->modelsBox->currentIndex();

    _save_object(fname, i);
}

void MainWindow::load_scene(const QString& dir_name)
{
    QDir dir;
    dir.setCurrent(dir_name);
    QStringList allFiles = dir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

    for (const auto& i : allFiles) {
        QByteArray fname_tmp = i.toUtf8();
        std::string fname = fname_tmp.data();

        _load_object(fname);
    }
}

void MainWindow::move_objects(const double& mx, const double& my, const double& mz)
{
    for (size_t i = 1; i < _scene.get_objects().size(); i++)
        _scene.get_objects()[i]->move(QVector3D(mx, my, mz));
}

void MainWindow::rotate_objects(const double& rx, const double& ry, const double& rz)
{
    for (size_t i = 1; i < _scene.get_objects().size(); i++)
        _scene.get_objects()[i]->rotate(QVector3D(rx, ry, rz), _scene.get_objects()[1]->get_center());
}

void MainWindow::menu_loadSceneButton_clicked()
{

    QString dir_name = QFileDialog::getExistingDirectory();

    load_scene(dir_name);

    render();
}

void MainWindow::menu_saveSceneButton_clicked()
{
    QString dir_name = QFileDialog::getExistingDirectory();

    QDir dir;
    dir.setCurrent(dir_name);

    for (size_t i = 0; i < _scene.get_objects().size(); i++) {
        std::string path = dir.dirName().toStdString() + "/";
        if (_scene.get_objects()[i]->is_sphere()) {
            path += "sphere";
        } else {
            path += "model";
        }
        char s_num[3] = "";
        std::sprintf(s_num, "%02zu", i);
        path += "_" + std::string(s_num) + ".obj";
        _save_object(path, i);
    }
}

void MainWindow::on_removeObjectButton_clicked()
{
    auto i = _ui->modelsBox->currentIndex();

    if (i != -1) {
        _scene.remove_object(i);

        _ui->modelsBox->removeItem(i);

        _ui->modelsBox_2->removeItem(i);
    }
}

void MainWindow::on_geometry_triggered()
{
    _ui->geometry->setChecked(true);
    _ui->lights->setChecked(false);
    _ui->material->setChecked(false);
    _ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_lights_triggered()
{
    _ui->geometry->setChecked(false);
    _ui->lights->setChecked(true);
    _ui->material->setChecked(false);
    _ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_material_triggered()
{
    _ui->geometry->setChecked(false);
    _ui->lights->setChecked(false);
    _ui->material->setChecked(true);
    _ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_removeLightButton_clicked()
{
    auto i = _ui->lightsBox->currentIndex();

    if (i != -1) {
        _scene.remove_light(i);

        _ui->lightsBox->removeItem(i);
    }
}

void MainWindow::on_lightsBox_currentIndexChanged(int index)
{
    if (index != -1) {
        _ui->posXSpinBox->setValue(_scene.get_lights().at(index)->get_position().x());
        _ui->posYSpinBox->setValue(_scene.get_lights().at(index)->get_position().y());
        _ui->posZSpinBox->setValue(_scene.get_lights().at(index)->get_position().z());
        _ui->intensitySpinBox->setValue(_scene.get_lights().at(index)->get_intensity());
    }
}

void MainWindow::on_setLightButton_clicked()
{
    auto i = _ui->lightsBox->currentIndex();
    if (i != -1) {
        auto light = _scene.get_lights().at(i);
        light->set_position(QVector3D(_ui->posXSpinBox->value(), _ui->posYSpinBox->value(), _ui->posZSpinBox->value()));
        light->set_intensity(_ui->intensitySpinBox->value());
    }
}

void MainWindow::on_addLightButton_clicked()
{
    _scene.add_light(QVector3D { 0, 0, 0 }, Color(1.0, 1.0, 1.0), 1.0);
    char buf[BUFLEN];
    snprintf(buf, sizeof(buf), "light_%02zu", _scene.get_lights().size() - 1);
    _ui->lightsBox->addItem(buf);
}

void MainWindow::on_modelsBox_2_currentIndexChanged(int index)
{
    if (index != -1) {
        _ui->ARedSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_ambient().r);
        _ui->AGreenSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_ambient().g);
        _ui->ABlueSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_ambient().b);
        _ui->DRedSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_diffuse().r);
        _ui->DGreenSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_diffuse().g);
        _ui->DBlueSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_diffuse().b);
        _ui->SRedSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_specular().r);
        _ui->SGreenSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_specular().g);
        _ui->SBlueSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_specular().b);

        _ui->kaSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_ka());
        _ui->kdSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_kd());
        _ui->ksSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_ks());
        _ui->kSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_k());

        _ui->k_reflSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_k_refl());
        _ui->k_refrSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_k_refr());
        _ui->refr_indexSpinBox->setValue(_scene.get_objects().at(index)->get_material().get_refraction_index());
    }
}

void MainWindow::on_setMaterialButton_clicked()
{
    auto i = _ui->modelsBox_2->currentIndex();
    auto object = _scene.get_objects().at(i);

    auto material = Material();

    material.set_ambient(Color(_ui->ARedSpinBox->value(), _ui->AGreenSpinBox->value(), _ui->ABlueSpinBox->value()));
    material.set_diffuse(Color(_ui->DRedSpinBox->value(), _ui->DGreenSpinBox->value(), _ui->DBlueSpinBox->value()));
    material.set_specular(Color(_ui->SRedSpinBox->value(), _ui->SGreenSpinBox->value(), _ui->SBlueSpinBox->value()));

    material.set_ka(_ui->kaSpinBox->value());
    material.set_kd(_ui->kdSpinBox->value());
    material.set_ks(_ui->ksSpinBox->value());
    material.set_k(_ui->kSpinBox->value());

    material.set_k_refl(_ui->k_reflSpinBox->value());
    material.set_k_refr(_ui->k_refrSpinBox->value());
    material.set_refraction_index(_ui->refr_indexSpinBox->value());

    object->set_material(material);
}
