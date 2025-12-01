/**
 * @file color.h
 * @brief Utilidades para manipulação e escrita de cores no formato RGB.
 *
 * Este arquivo define o alias `color` baseado em `vec3` para representar cores 
 * e fornece funções para converter cores normalizadas (0–1) para o formato 
 * de saída PPM (0–255).
 */

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "utils.h"
#include <iostream>

using color = vec3;

/**
 * @brief Escreve um pixel de cor no formato PPM.
 *
 * Esta função converte uma cor representada por valores no intervalo 
 * [0, 1] para o intervalo de bytes [0, 255].
 *
 * @param out Stream de saída onde a cor será escrita.
 * @param pixel_color Vetor contendo as componentes de cor normalizadas.
 */
inline void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide a cor pelo número de amostras
    auto scale = 1.0 / samples_per_pixel;
    
    // --- CORREÇÃO GAMA (Raiz Quadrada) ---
    // Substituímos a multiplicação direta pela raiz quadrada (sqrt)
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Escreve os valores [0,255]
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}
#endif