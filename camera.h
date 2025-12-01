#pragma once

#include "utils.h"
#include "ray.h"

class camera {
    public:
        /**
         * @brief Construtor padrão da câmera.
         */
        camera();

        void move_forward(double speed);
        void move_backward(double speed);
        void move_left(double speed);
        void move_right(double speed);

        /**
         * @brief Gera um raio a partir da câmera para as coordenadas (u, v).
         */
        ray get_ray(double u, double v) const;

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        
        // Parâmetros fixos (podem virar variáveis no futuro)
        const double viewport_height = 2.0;
        const double focal_length = 1.0;

        void reset_view();
        void recalculate();
};