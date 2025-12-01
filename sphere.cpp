#include "sphere.h"

// Construtor vazio
sphere::sphere() {}

// Construtor com argumentos
sphere::sphere(point3 cen, double r, shared_ptr<material> m)
    : center(cen), radius(r), mat_ptr(m) {};

// A lógica de colisão
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Acha a raiz mais próxima no intervalo aceitável
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    
    bool front_face = dot(r.direction(), outward_normal) < 0;
    rec.normal = front_face ? outward_normal : -outward_normal;
    rec.mat_ptr = mat_ptr;

    return true;
}