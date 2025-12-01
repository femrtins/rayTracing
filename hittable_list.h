#pragma once

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

/**
 * @class hittable_list
 * @brief Implementa uma coleção de objetos atingíveis por raios
 *
 * Essa classe armazena múltiplos objetos que implementam a interface `hittable`
 * e permite testar colisão entre um raio e todos os objetos da cena
 *
 * O método `hit()` percorre todos os objetos e retorna o registro do
 * objeto mais próximo atingido pelo raio, se houver colisão.
 */
class hittable_list : public hittable {
    
    public:
        /// Construtor padrão
        hittable_list();

        /// Construtor que inicia com um objeto
        hittable_list(shared_ptr<hittable> object);

        /// Remove todos os objetos da lista
        void clear();

        /// Adiciona um objeto à lista
        void add(shared_ptr<hittable> object);

        /**
        * @brief Testa colisão entre o raio e todos os objetos da lista.
        * @param r Raio a testar
        * @param t_min Menor valor aceito para t
        * @param t_max Maior valor aceito para t
        * @param rec Registro onde será armazenada a colisão mais próxima
        * @return true se algum objeto foi atingido, false caso contrário
        */
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        std::vector<shared_ptr<hittable>> objects;
};