/**
 * @file ray.h
 * @brief Representação de raios utilizados no ray tracing.
 *
 * A classe ray modela um raio no espaço tridimensional, definido por uma
 * origem e uma direção. Também fornece a função `at(t)` que permite calcular
 * pontos ao longo do raio.
 */
#ifndef RAY_H
#define RAY_H

#include "vec3.h"


/**
 * @class ray
 * @brief Classe que representa um raio no espaço 3D
 *
 * Um raio é definido por:
 * - um ponto de origem (`orig`)
 * - um vetor de direção (`dir`)
 */
class ray {
  public:
    /**
     * @brief Construtor padrão. Cria um raio sem valores definidos
     */
    ray() {}

    /**
     * @brief Construtor que define origem e direção do raio
     * @param origin Ponto inicial do raio
     * @param direction Vetor de direção do raio
     */
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    /**
     * @brief Retorna a origem do raio.
     */
    const point3& origin() const  { return orig; }

    /**
     * @brief Retorna a direção do raio.
     */
    const vec3& direction() const { return dir; }

    /**
     * @brief Retorna o ponto ao longo do raio no parâmetro t.
     *
     * Calcula:
     * \f[
     *    P(t) = \text{orig} + t \cdot \text{dir}
     * \f]
     *
     * @param t Parâmetro escalar.
     * @return Ponto no espaço tridimensional correspondente ao parâmetro t.
     */
    point3 at(double t) const {
        return orig + t*dir;
    }

  private:
    point3 orig;
    vec3 dir;
};

#endif

