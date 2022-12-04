/**
 * @file material.cpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации класса Material
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "material.h"

Material::Material()
{
}

Material::Material(const Color& amb, const Color& diff, const Color& spec, int k, double ka, double kd, double ks, double k_refl, double k_refr, double refraction_index)
    : _ambient(amb)
    , _diffuse(diff)
    , _specular(spec)
    , _ka(ka)
    , _kd(kd)
    , _ks(ks)
    , _k_refl(k_refl)
    , _k_refr(k_refr)
    , _refraction_index(refraction_index)
    , _k(k)
{
}
