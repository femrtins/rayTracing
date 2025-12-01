#include "camera.h"

// Construtor
camera::camera() {
    reset_view();
}

void camera::move_forward(double speed) {
    // Z negativo é para dentro da tela (frente)
    origin.e[2] -= speed;
    recalculate();
}

void camera::move_backward(double speed) {
    origin.e[2] += speed;
    recalculate();
}

void camera::move_left(double speed) {
    origin.e[0] -= speed;
    recalculate();
}

void camera::move_right(double speed) {
    origin.e[0] += speed;
    recalculate();
}

ray camera::get_ray(double u, double v) const {
    return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}

void camera::reset_view() {
    origin = point3(0, 0, 0);
    recalculate();
}

void camera::recalculate() {
    auto aspect_ratio = 16.0 / 9.0;
    auto viewport_width = aspect_ratio * viewport_height;

    horizontal = vec3(viewport_width, 0.0, 0.0);
    vertical = vec3(0.0, viewport_height, 0.0);
    
    // Recalcula o canto inferior esquerdo com base na nova origem
    lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
}