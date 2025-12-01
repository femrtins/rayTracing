#pragma once

#include "hittable.h"
#include "vec3.h"
#include <memory>

using std::shared_ptr; 

/**
 * @class sphere
 * @brief Representa uma esfera no cenário 3D
 *
 * A classe `sphere` implementa o método `hit`, que determina se um raio colide 
 * com a esfera e, caso haja interseção, calcula informações úteis como o ponto 
 * de impacto, normal da superfície.
 *
 * A equação de interseção é baseada no teste geométrico padrão entre um raio
 * parametrizado pela equação:
 *
 *   `P(t) = A + tB`
 *
 * e a esfera definida por centro `C` e raio `R`.
 */
class sphere : public hittable {

    public:

        /**
         * @brief Construtor padrão. Cria uma esfera com raio 0 e centro na origem.
         */
        sphere();

        /**
         * @brief Constrói uma esfera com centro, raio e material.
         * 
         * @param cen Centro da esfera.
         * @param r   Raio da esfera.
         * @param m   Ponteiro compartilhado para o material da esfera.
         */
        sphere(point3 cen, double r, shared_ptr<material> m);

        /**
         * @brief Verifica se o raio atinge esta esfera.
         *
         * Implementa o cálculo da interseção entre um raio e a esfera.
         * Se houver impacto no intervalo `[t_min, t_max]`, o método registra
         * informações como:
         * - ponto de impacto (`rec.p`)
         * - valor de `t` (parâmetro do raio)
         * - normal da superfície no ponto
         * - referência ao material
         *
         * @param r       Raio de entrada.
         * @param t_min   Valor mínimo permitido para t (para evitar hits indesejados)
         * @param t_max   Valor máximo permitido para t
         * @param rec     Estrutura onde serão salvos os dados da colisão
         * @return true se o raio colidir com a esfera, false caso contrário
         */
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};
