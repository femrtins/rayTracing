#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <cstdint> 
#include "color.h"
#include "camera.h"

/**
 * @class Window
 * @brief Gerencia a janela, renderizador e buffer de pixels usando SDL2
 */
class Window {

public:
    /**
     * @brief Constrói uma janela SDL com o tamanho especificado
     */
    Window(int width, int height);

    /**
     * @brief Destrutor
     */
    ~Window();

    /**
     * @brief Define a cor de um pixel no framebuffer interno
     */
    void set_pixel(int x, int y, const color& pixel_color, int samples_per_pixel);

    /**
     * @brief Atualiza a janela com o conteúdo atual do framebuffer
     */
    void refresh();

    /**
     * @brief Processa eventos do teclado e movimenta a câmera
     * @return `true` se a câmera se moveu, `false` caso contrário
     */
    bool process_input(camera& cam);

    /**
     * @brief Indica se a janela deve ser fechada
     */
    bool should_close();

private:
    int width, height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    std::vector<uint32_t> pixels;
    bool should_close_flag = false;

    /**
     * @brief Clampa valores numéricos.
     */
    double clamp(double x, double min, double max);
};