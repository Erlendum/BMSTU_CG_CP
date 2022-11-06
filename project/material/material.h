#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

class Material {
public:
    Material();
    Material(const Color& amb, const Color& diff, const Color& spec, int k);
    Material(const Color& amb, const Color& diff, const Color& spec, int k, double ka, double kd, double ks, double k_refl, double k_refr, double refraction_index);

    void set_ambient(const Color& c) { _ambient = c; }
    void set_diffuse(const Color& c) { _diffuse = c; }
    void set_specular(const Color& c) { _specular = c; }
    void set_ka(const double& ka) { _ka = ka; };
    void set_kd(const double& kd) { _kd = kd; };
    void set_ks(const double& ks) { _ks = ks; };
    void set_k_refl(const double& k_refl) { _k_refl = k_refl; };
    void set_k_refr(const double& k_refr) { _k_refr = k_refr; };
    void set_refraction_index(const double& refraction_index) { _refraction_index = refraction_index; };
    void set_k(const double& k) { _k = k; };

    Color get_ambient() const { return _ambient; };
    Color get_diffuse() const { return _diffuse; };
    Color get_specular() const { return _specular; };
    double get_ka() const { return _ka; };
    double get_kd() const { return _kd; };
    double get_ks() const { return _ks; };
    double get_k_refl() const { return _k_refl; };
    double get_k_refr() const { return _k_refr; };
    double get_refraction_index() const { return _refraction_index; };
    double get_k() const { return _k; };

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
