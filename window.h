#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "color.h" // Sua classe color existente

class Window {
public:
    Window(int width, int height) : width(width), height(height) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
            exit(1);
        }

        window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
        
        // Buffer de pixels (ARGB)
        pixels.resize(width * height);
    }

    ~Window() {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void set_pixel(int x, int y, const color& pixel_color, int samples_per_pixel) {
        // Converte sua classe color para 0-255 (lógica adaptada do seu color.h)
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        // Correção Gama (que você usava no write_color)
        auto scale = 1.0 / samples_per_pixel;
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);

        uint8_t ir = static_cast<uint8_t>(256 * clamp(r, 0.0, 0.999));
        uint8_t ig = static_cast<uint8_t>(256 * clamp(g, 0.0, 0.999));
        uint8_t ib = static_cast<uint8_t>(256 * clamp(b, 0.0, 0.999));

        // SDL usa pixels empacotados (ARGB ou RGBA dependendo da endianness, mas ARGB8888 costuma ser seguro)
        // Y invertido pois SDL desenha de cima para baixo, e seu Raytracer de baixo para cima
        int inverted_y = height - 1 - y; 
        pixels[inverted_y * width + x] = (255 << 24) | (ir << 16) | (ig << 8) | ib;
    }

    void refresh() {
        SDL_UpdateTexture(texture, NULL, pixels.data(), width * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    bool should_close() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) return true;
        }
        return false;
    }

    void wait_for_exit() {
        while (!should_close()) {
            SDL_Delay(100);
        }
    }

private:
    int width, height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    std::vector<uint32_t> pixels;

    double clamp(double x, double min, double max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
};