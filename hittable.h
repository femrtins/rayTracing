#pragma once

#include "ray.h"
#include <memory> // Para shared_ptr

// AVISO AO COMPILADOR: "Existe uma classe chamada material, confia em mim"
class material;

struct hit_record {
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr; // <--- NOVO: Ponteiro para o material
    double t;
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};