#pragma once
#include "ray.h"
#include "hittable.h"
#include "color.h"
#include "material.h"

// Interface abstrata (Strategy)
class Integrator {
public:
    virtual ~Integrator() = default;
    
    // O método principal que calcula a cor de um raio
    virtual color Li(const ray& r, const hittable& scene, int depth) const = 0;
};

// Implementação concreta: O algoritmo recursivo clássico
class RecursiveIntegrator : public Integrator {
public:
    RecursiveIntegrator(int max_depth) : max_depth(max_depth) {}

    color Li(const ray& r, const hittable& scene, int depth) const override {
        hit_record rec;

        // Se exceder o limite de rebatidas, não retorna luz
        if (depth <= 0) return color(0,0,0);

        // Se atingir algo na cena
        if (scene.hit(r, 0.001, infinity, rec)) {
            ray scattered;
            color attenuation;
            
            // Polimorfismo do material (já existente no seu código)
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
                // Chama recursivamente Li em vez de ray_color
                return attenuation * Li(scattered, scene, depth - 1);
            }
            return color(0,0,0);
        }

        // Fundo (Skybox)
        vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }

private:
    int max_depth;
};