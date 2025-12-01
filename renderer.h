#pragma once
#include "window.h"
#include "integrator.h"
#include "camera.h"
#include "hittable.h"
#include <iostream>

// 1. A struct TEM que vir antes da classe
struct RenderSettings {
    int image_width = 800;
    double aspect_ratio = 16.0 / 9.0;
    int samples_per_pixel = 50;
    int max_depth = 50;
};

// 2. A classe Renderer vem depois
class Renderer {
public:
    Renderer(const RenderSettings& settings) 
        : settings(settings), 
          window(settings.image_width, static_cast<int>(settings.image_width / settings.aspect_ratio)) 
    {
        image_height = static_cast<int>(settings.image_width / settings.aspect_ratio);
    }

    void render(const hittable& scene, camera& cam, const Integrator& integrator) {
        while (!window.should_close()) {
            for (int j = image_height - 1; j >= 0; --j) {
                
                // Processa input e verifica se precisa reiniciar
                bool camera_moved = window.process_input(cam);
                if (window.should_close()) return;

                if (camera_moved) {
                    j = image_height - 1; // Reinicia o render
                    continue; 
                }

                // Renderiza a linha
                for (int i = 0; i < settings.image_width; ++i) {
                    color pixel_color(0, 0, 0);
                    for (int s = 0; s < settings.samples_per_pixel; ++s) {
                        auto u = (double(i) + random_double()) / (settings.image_width - 1);
                        auto v = (double(j) + random_double()) / (image_height - 1);
                        ray r = cam.get_ray(u, v);
                        pixel_color += integrator.Li(r, scene, settings.max_depth);
                    }
                    window.set_pixel(i, j, pixel_color, settings.samples_per_pixel);
                }
                window.refresh();
            }
            
            // Espera ociosa se terminou a imagem
            while (!window.process_input(cam) && !window.should_close()) {
                SDL_Delay(50);
            }
        }
    }

private:
    RenderSettings settings; // Agora o compilador sabe o que é isso
    int image_height;
    Window window;
};