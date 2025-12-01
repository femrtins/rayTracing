#pragma once

#include "hittable.h"
#include "vec3.h"
#include <memory>

// Adicione isto para não precisar escrever std:: toda vez
using std::shared_ptr; 

class sphere : public hittable {
    public:
        sphere();
        // Agora o compilador vai reconhecer o shared_ptr
        sphere(point3 cen, double r, shared_ptr<material> m);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};