/**
 * @file material.h
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл интерфейса класса Material
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

/*!
    @brief Класс, представляющий материал некоторой поверхности
*/
class Material {
public:
    /*!
        @brief Конструктор по умолчанию
        @return Объект класса
    */
    Material();
    /*!
        @brief Конструктор
        @param [IN] amb - цвет фонового освещения(Color)
        @param [IN] diff - цвет диффузного освещения (Color)
        @param [IN] spec - цвет зеркального освещения (Color)
        @param [IN] k -  степень, аппроксимирующая пространственное распределение зеркально отражённого света (int)
        @param [IN] ka -  коэффициент фонового освещения (double)
        @param [IN] kd -  коэффициент диффузного освещения (double)
        @param [IN] ks -  коэффициент зеркального освещения (double)
        @param [IN] k_refl - коэффициент отражения (double)
        @param [IN] k_refr -  коэффициент преломления (double)
        @param [IN] refraction_index -  коэффициент преломления света в среде (double)
        @return Объект класса
    */
    Material(const Color& amb, const Color& diff, const Color& spec, int k, double ka, double kd, double ks, double k_refl, double k_refr, double refraction_index);

    /*!
        @brief Установить цвет фонового освещения
        @param [IN] c - цвет фонового освещения
    */
    void set_ambient(const Color& c) { _ambient = c; }
    /*!
        @brief Установить цвет диффузного освещения
        @param [IN] c - цвет диффузного освещения
    */
    void set_diffuse(const Color& c) { _diffuse = c; }
    /*!
        @brief Установить цвет зеркального освещения
        @param [IN] c - цвет зеркального освещения
    */
    void set_specular(const Color& c) { _specular = c; }
    /*!
        @brief Установить коэффициент фонового освещения
        @param [IN] ka - коэффициент фонового освещения
    */
    void set_ka(const double& ka) { _ka = ka; };
    /*!
        @brief Установить коэффициент диффузного освещения
        @param [IN] kd - коэффициент диффузного освещения
    */
    void set_kd(const double& kd) { _kd = kd; };
    /*!
        @brief Установить коэффициент зеркального освещения
        @param [IN] ks - коэффициент зеркального освещения
    */
    void set_ks(const double& ks) { _ks = ks; };
    /*!
        @brief Установить коэффициент отражения
        @param [IN] k_refl - коэффициент отражения
    */
    void set_k_refl(const double& k_refl) { _k_refl = k_refl; };
    /*!
        @brief Установить коэффициент преломления
        @param [IN] k_refr - коэффициент преломления
    */
    void set_k_refr(const double& k_refr) { _k_refr = k_refr; };
    /*!
        @brief Установить коэффициент преломления света в среде
        @param [IN] refraction_index - коэффициент преломления света в среде
    */
    void set_refraction_index(const double& refraction_index) { _refraction_index = refraction_index; };
    /*!
        @brief Установить степень, аппроксимирующую пространственное распределение зеркально отражённого света
        @param [IN] k - степень, аппроксимирующая пространственное распределение зеркально отражённого света
    */
    void set_k(const double& k) { _k = k; };

    /*!
        @brief Получить цвет фонового освещения
        @return Color
    */
    Color get_ambient() const { return _ambient; };
    /*!
        @brief Получить цвет диффузного освещения
        @return Color
    */
    Color get_diffuse() const { return _diffuse; };
    /*!
        @brief Получить цвет зеркального освещения
        @return Color
    */
    Color get_specular() const { return _specular; };
    /*!
        @brief Получить коэффициент фонового освещения
        @return double
    */
    double get_ka() const { return _ka; };
    /*!
        @brief Получить коэффициент диффузного освещения
        @return double
    */
    double get_kd() const { return _kd; };
    /*!
        @brief Получить коэффициент зеркального освещения
        @return double
    */
    double get_ks() const { return _ks; };
    /*!
        @brief Получить коэффициент отражения
        @return double
    */
    double get_k_refl() const { return _k_refl; };
    /*!
        @brief Получить коэффициент преломления
        @return double
    */
    double get_k_refr() const { return _k_refr; };
    /*!
        @brief Получить коэффициент преломления света в среде
        @return double
    */
    double get_refraction_index() const { return _refraction_index; };
    /*!
        @brief Получить степень, аппроксимирующую пространственное распределение зеркально отражённого света
        @return int
    */
    int get_k() const { return _k; };

private:
    Color _ambient;
    Color _diffuse;
    Color _specular;

    double _ka, _kd, _ks;

    double _k_refl, _k_refr;

    double _refraction_index;

    int _k;
};

#endif // MATERIAL_H
