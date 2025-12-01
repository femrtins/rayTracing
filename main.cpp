#include "rtweekend.h"
#include "renderer.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h" // Importante: inclui lambertian, metal, etc.
#include "camera.h"   // Sua classe camera extraída

int main() {
    // 1. Configurações
    RenderSettings settings;
    settings.image_width = 800;
    settings.samples_per_pixel = 20;
    settings.max_depth = 50;
    
    // 2. Cena
    hittable_list world;

    // Instanciação direta (sem Factory)
    auto mat_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto mat_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto mat_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto mat_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, mat_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, mat_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, mat_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, mat_right));

    // 3. Câmera e Integrador
    camera cam; 
    RecursiveIntegrator integrator(settings.max_depth);

    // 4. Execução (Janela Gráfica)
    Renderer engine(settings);
    engine.render(world, cam, integrator);

    return 0;
}