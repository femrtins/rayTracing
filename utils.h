#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib> 

using std::shared_ptr;
using std::make_shared;
using std::sqrt;


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// -----------------------------------------------------------------------------
// Funções utilitárias
// -----------------------------------------------------------------------------

/**
 * @brief Converte graus em radianos
 *
 * @param degrees Valor em graus
 * @return Valor correspondente em radianos
 */
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

/**
 * @brief Gera um número real aleatório no intervalo [0, 1)
 *
 * @return Número aleatório entre 0 (inclusive) e 1 (exclusive).
 */
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

/**
 * @brief Gera um número real aleatório no intervalo [min, max)
 *
 * @param min Limite inferior
 * @param max Limite superior
 * @return Número aleatório entre `min` (inclusive) e `max` (exclusive)
 */
inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

/**
 * @brief Limita o valor de `x` ao intervalo [min, max].
 *
 * @param x Valor a ser limitado
 * @param min Limite mínimo
 * @param max Limite máximo
 * @return `x` limitado dentro do intervalo [min, max]
 */
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
