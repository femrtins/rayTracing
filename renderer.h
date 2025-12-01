#pragma once
#include "window.h"       // Sua classe Window (definida anteriormente)
#include "integrator.h"   // Sua classe Integrator (definida anteriormente)
#include "camera.h"       // Sua classe Camera
#include "hittable.h"
#include <iostream>

struct RenderSettings {
    int image_width = 800;
    double aspect_ratio = 16.0 / 9.0;
    int samples_per_pixel = 50;
    int max_depth = 50;
};

class Renderer {
public:
    Renderer(const RenderSettings& settings) 
        : settings(settings), 
          // O Renderer inicializa a janela automaticamente
          window(settings.image_width, static_cast<int>(settings.image_width / settings.aspect_ratio)) 
    {
        image_height = static_cast<int>(settings.image_width / settings.aspect_ratio);
    }

    void render(const hittable& scene, const camera& cam, const Integrator& integrator) {
        bool quit = false;

        for (int j = image_height - 1; j >= 0 && !quit; --j) {
            
            // Verifica se o usuário fechou a janela no meio do render
            if (window.should_close()) {
                std::cout << "\nRenderização cancelada pelo usuário.\n";
                quit = true;
                break;
            }

            std::cerr << "\rLinhas restantes: " << j << ' ' << std::flush;
            
            for (int i = 0; i < settings.image_width; ++i) {
                color pixel_color(0, 0, 0);
                
                for (int s = 0; s < settings.samples_per_pixel; ++s) {
                    auto u = (double(i) + random_double()) / (settings.image_width - 1);
                    auto v = (double(j) + random_double()) / (image_height - 1);
                    
                    ray r = cam.get_ray(u, v);
                    pixel_color += integrator.Li(r, scene, settings.max_depth);
                }
                
                // O Renderer desenha direto na janela interna
                window.set_pixel(i, j, pixel_color, settings.samples_per_pixel);
            }
            
            // Atualiza a tela a cada linha
            window.refresh();
        }

        if (!quit) {
            std::cerr << "\nRenderização concluída. Feche a janela para sair.\n";
            // Mantém a janela aberta para apreciar a arte
            window.wait_for_exit();
        }
    }

private:
    RenderSettings settings;
    int image_height;
    Window window; // A janela agora é propriedade privada do Renderer
};