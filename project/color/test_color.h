/**
 * @file test_color.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса TestColor
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TESTCOLOR_H
#define TESTCOLOR_H

#include "color.h"
#include <QObject>

/*!
    @brief Класс, представляющий тестирование класса Color
    @details
    Оператор умножения:\n
    Тест №1 - оператор умножения с другим объектом класса Color\n
    Тест №1 - оператор умножения с вещественным числом\n
    Оператор сложения:\n
    Тест №1 - оператор сложения с другим объектом класса Color\n
    Оператор умножения, совмещённый с оператором присваивания:\n
    Тест №1 - оператор умножения с другим объектом класса Color, совмещённый с оператором присваивания\n
    Оператор сложения, совмещённый с оператором присваивания:\n
    Тест №1 - оператор сложения с другим объектом класса Color, совмещённый с оператором присваивания\n
    Установка цвета:\n
    Тест №1 - установка цвета (0.2, 0.2, 0.2)\n
    Нормализация цвета:\n
    Тест №1 - нормализация цвета (2.0, 1.9, 3.56)\n
    Оператор проверки на равенство:\n
    Тест №1 - Оператор проверки на равенство разных цветов\n
    Тест №2 - Оператор проверки на равенство одинаковых цветов\n
*/
class TestColor : public QObject {
    Q_OBJECT
public:
    explicit TestColor(QObject* parent = nullptr);

private slots:
    void test_01_mul_operator();
    void test_02_mul_operator();

    void test_01_sum_operator();

    void test_01_mul_assign_operator();

    void test_01_sum_assign_operator();

    void test_01_set_color();

    void test_01_normalize();

    void test_01_eq_operator();
    void test_02_eq_operator();
};

#endif // TESTCOLOR_H
