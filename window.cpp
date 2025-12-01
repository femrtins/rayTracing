#include "window.h"
#include <cmath>     
#include <iostream>  
#include <algorithm>

Window::Window(int width, int height) : width(width), height(height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(
        "Ray Tracer", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        width, height, 
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    pixels.resize(width * height);
}

Window::~Window() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::set_pixel(int x, int y, const color& pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Média das amostras + Gamma correction
    auto scale = 1.0 / samples_per_pixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    uint8_t ir = static_cast<uint8_t>(256 * clamp(r, 0.0, 0.999));
    uint8_t ig = static_cast<uint8_t>(256 * clamp(g, 0.0, 0.999));
    uint8_t ib = static_cast<uint8_t>(256 * clamp(b, 0.0, 0.999));

    // Inverte Y para alinhar com coordenadas matemáticas
    int inverted_y = height - 1 - y;

    if (inverted_y >= 0 && inverted_y < height && x >= 0 && x < width) {
        pixels[inverted_y * width + x] =
            (255 << 24) | (ir << 16) | (ig << 8) | ib;
    }
}

void Window::refresh() {
    SDL_UpdateTexture(texture, NULL, pixels.data(), width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool Window::process_input(camera& cam) {
    SDL_Event e;
    bool moved = false;
    double speed = 0.5;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            should_close_flag = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    should_close_flag = true;
                    break;
                case SDLK_w:
                    cam.move_forward(speed);
                    moved = true;
                    break;
                case SDLK_s:
                    cam.move_backward(speed);
                    moved = true;
                    break;
                case SDLK_a:
                    cam.move_left(speed);
                    moved = true;
                    break;
                case SDLK_d:
                    cam.move_right(speed);
                    moved = true;
                    break;
            }
        }
    }
    return moved;
}

bool Window::should_close() { 
    return should_close_flag; 
}

double Window::clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}