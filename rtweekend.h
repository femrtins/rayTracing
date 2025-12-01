#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib> // Para rand()

// Usings comuns
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constantes
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Funções Utilitárias

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Retorna um número real aleatório entre [0, 1)
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// Retorna um número real aleatório entre [min, max)
inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

// Clampa o valor x entre min e max (útil para cores)
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}