/**
 * @file mainwindow.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса MainWindow
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

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

/*!
    @brief Класс, представляющий графический интерфейс пользователя
*/
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /*!
        @brief Конструктор
        @param [IN] parent - родительский класс QWidget
        @return Объект класса
    */
    MainWindow(QWidget* parent = nullptr);
    /*!
        @brief Деструктор по умолчанию
    */
    ~MainWindow();

    /*!
        @brief Создание сцены
        @details Устанавливается камера и источники света по умолчанию
    */
    void create_scene();

    /*!
        @brief Рендеринг изображения
    */
    void render();

    /*!
        @brief Параллельный рендеринг изображения
        @param [IN] nth - количество потоков (int)
    */
    void render_parallel(int nth);

    /*!
        @brief Установка выходного файла
        @param [IN] file_name - имя выходного файла (std::string)
    */
    void set_output_file(const std::string& file_name);

    /*!
        @brief Установка глубины рекурсивных погружений
        @param [IN] n - глубина рекурсивных погружений (int)
    */
    void set_N(const int& n);

    /*!
        @brief Установка количества пикселей в горизонтальном измерении
        @param [IN] size_x - количество пикселей в горизонтальной измерении (int)
    */
    void set_size_x(const int& size_x);

    /*!
        @brief Установка количества пикселей в вертикальном измерении
        @param [IN] size_y - количество пикселей в вертикальном измерении (int)
    */
    void set_size_y(const int& size_y);

    /*!
        @brief Загрузка сцены
        @param [IN] dir_name - имя директории, содержащей сцену (QString)
    */
    void load_scene(const QString& dir_name);

    /*!
        @brief Перемещение объектов сцены
        @param [IN] mx - расстояние перемещения по оси X (double)
        @param [IN] my - расстояние перемещения по оси Y (double)
        @param [IN] mz - расстояние перемещения по оси Z (double)
        @warning Предполагается, что нулевой объект сцены - поверхность, задающая землю, которую не надо перемещать
    */
    void move_objects(const double& mx, const double& my, const double& mz);

    /*!
        @brief Поворот объектов сцены
        @param [IN] rx - угол поворота в градусах по оси X (double)
        @param [IN] ry - угол поворота в градусах по оси Y (double)
        @param [IN] rz - угол поворота в градусах по оси Z (double)
        @warning Предполагается, что нулевой объект сцены - поверхность, задающая землю, которую не надо поворачивать
    */
    void rotate_objects(const double& rx, const double& ry, const double& rz);

private slots:
    void exit_messagebox();

    void on_render_button_clicked();

    void on_moveButton_clicked();

    void on_scaleButton_clicked();

    void on_rotateButton_clicked();

    void menu_loadButton_clicked();

    void menu_saveButton_clicked();

    void menu_loadSceneButton_clicked();

    void menu_saveSceneButton_clicked();

    void on_removeObjectButton_clicked();

    void on_geometry_triggered();

    void on_lights_triggered();

    void on_removeLightButton_clicked();

    void on_lightsBox_currentIndexChanged(int index);

    void on_setLightButton_clicked();

    void on_addLightButton_clicked();

    void on_material_triggered();

    void on_modelsBox_2_currentIndexChanged(int index);

    void on_setMaterialButton_clicked();

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
