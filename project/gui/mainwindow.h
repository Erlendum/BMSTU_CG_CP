#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "camera.h"
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void create_scene();

    void render();

    void render_parallel(int nth);

    void set_output_file(const std::string& file_name);

    void set_N(const int& n);

    void set_size_x(const int& size_x);

    void set_size_y(const int& size_y);

    void load_scene(const QString& dir_name);

private slots:
    void on_render_button_clicked();

    void on_moveButton_clicked();

    void on_scaleButton_clicked();

    void on_rotateButton_clicked();

    void menu_loadButton_clicked();

    void menu_saveButton_clicked();

    void menu_loadSceneButton_clicked();

    void menu_saveSceneButton_clicked();

private:
    Ui::MainWindow* _ui;

    Scene _scene;
    std::shared_ptr<Camera> _camera;

    int _size_x;
    int _size_y;

    std::string _output_file;

    Color _cast_ray(Color& buf_color, const Ray ray, const int depth = 0);

    QVector3D _reflects(QVector3D raio, QVector3D norm);
    QVector3D _refract(QVector3D raio, QVector3D norm, double refractive_index);

    void _load_object(std::string& file_name);
    void _save_object(std::string& file_name, const size_t& i);

    int N;

    Material material_gold = Material(Color(0.09, 0.07, 0.02), Color(0.8549, 0.6470, 0.1254), Color(1.0, 1.0, 1.0), 200, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0);
    Material material_red = Material(Color(0.2, 0.0, 0.0), Color(1.0, 0, 0), Color(1, 1, 0.2), 200, 0.0, 1.0, 10.0, 1.0, 0.0, 0.0);
    Material material_blue = Material(Color(0.0, 0.0, 0.2), Color(0.0, 0, 1.0), Color(1.0, 1.0, 1.0), 70, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0);
    Material material_wood = Material(Color(0.0, 0.0, 0.0), Color(0.9922, 0.9804, 0.8941), Color(0.63, 0.63, 0.63), 70, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0);
};
#endif // MAINWINDOW_H
