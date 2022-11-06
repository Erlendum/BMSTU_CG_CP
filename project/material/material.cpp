#include "material.h"

Material::Material()
{
}

Material::Material(const Color& amb, const Color& diff, const Color& spec, int k)
    : _ambient(amb)
    , _diffuse(diff)
    , _specular(spec)
    , _k(k)
{
    this->_ka = 1.0;
    this->_kd = 1.0;
    this->_ks = 1.0;
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
