#pragma once

#include "ray.h"
#include <memory> // Para shared_ptr

class material;

/**
 * @struct hit_record
 * @brief Armazena todas as informações necessárias quando um raio atinge um objeto
 *
 * Este registro guarda:
 * - o ponto da colisão (`p`)
 * - a normal da superfície no ponto (`normal`)
 * - a distância ao longo do raio (`t`)
 * - um ponteiro para o material do objeto atingido (`mat_ptr`)
 */
struct hit_record {
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
    double t;
};

/**
 * @class hittable
 * @brief Interface base para qualquer objeto que possa ser atingido por um raio
 *
 * O método hit determina se um raio colide com o objeto dentro de um intervalo
 * de parâmetros (`t_min` até `t_max`) e, em caso positivo, preenche o hit_record
 */
class hittable {
public:

    /**
     * @brief Verifica se um raio atinge o objeto
     *
     * @param r Raio lançado
     * @param t_min Valor mínimo de t a considerar
     * @param t_max Valor máximo de t a considerar
     * @param rec Estrutura onde será armazenado o resultado da colisão
     *
     * @return true se o objeto for atingido; false caso contrário
     */
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
