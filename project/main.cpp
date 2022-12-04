#include "mainwindow.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>

#include "test_camera.h"
#include "test_color.h"
#include "test_model.h"
#include "test_ray.h"
#include "test_scene.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    setlocale(LC_NUMERIC, "C");
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-o") == 0) {
            w.set_output_file(argv[i + 1]);
            w.render_parallel(4);
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-mx") == 0) {
            w.move_objects(std::stod(argv[i + 1]), 0, 0);
        } else if (strcmp(argv[i], "-mz") == 0) {
            w.move_objects(0, 0, std::stod(argv[i + 1]));
        } else if (strcmp(argv[i], "-ry") == 0) {
            w.rotate_objects(0, std::stod(argv[i + 1]), 0);
        } else if (strcmp(argv[i], "-s") == 0) {
            w.load_scene(argv[i + 1]);
        } else if (strcmp(argv[i], "-size") == 0) {
            w.set_size_x(std::stoi(argv[i + 1]));
            w.set_size_y(std::stoi(argv[i + 1]));
        } else if (strcmp(argv[i], "-r") == 0) {
            w.set_N(std::stoi(argv[i + 1]));

            using std::chrono::duration_cast;
            using std::chrono::microseconds;

            auto end = std::chrono::system_clock::now();
            auto start = std::chrono::system_clock::now();

            start = std::chrono::system_clock::now();
            w.render();
            end = std::chrono::system_clock::now();
            std::cout << (double)duration_cast<microseconds>(end - start).count() << std::endl;
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-t") == 0) {
            using std::chrono::duration_cast;
            using std::chrono::microseconds;

            auto end = std::chrono::system_clock::now();
            auto start = std::chrono::system_clock::now();

            int t = std::stoi(argv[i + 1]);
            start = std::chrono::system_clock::now();
            if (t > 0)
                w.render_parallel(std::stoi(argv[i + 1]));
            else
                w.render();
            end = std::chrono::system_clock::now();
            std::cout << (double)duration_cast<microseconds>(end - start).count() << std::endl;
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-test") == 0) {
            if (strcmp(argv[i + 1], "model") == 0) {
                QTest::qExec(new TestModel);
            } else if (strcmp(argv[i + 1], "camera") == 0) {
                QTest::qExec(new TestCamera);
            } else if (strcmp(argv[i + 1], "color") == 0) {
                QTest::qExec(new TestColor);
            } else if (strcmp(argv[i + 1], "ray") == 0) {
                QTest::qExec(new TestRay);
            } else if (strcmp(argv[i + 1], "scene") == 0) {
                QTest::qExec(new TestScene);
            } else if (strcmp(argv[i + 1], "all") == 0) {
                QTest::qExec(new TestModel);
                QTest::qExec(new TestCamera);
                QTest::qExec(new TestColor);
                QTest::qExec(new TestRay);
                QTest::qExec(new TestScene);
            }
            return EXIT_SUCCESS;
        }

    w.show();
    return a.exec();
}
