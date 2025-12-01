/**
 * @file vec3.h
 * @brief Implementação de um vetor tridimensional (3D) utilizado em operações
 *        de computação gráfica e ray tracing.
 *
 * Esta classe fornece uma representação simples e eficiente de vetores no
 * espaço 3D, incluindo operações fundamentais como soma, subtração, produto
 * escalar, produto vetorial, normalização e geração de vetores aleatórios.
 *
 * O código segue o estilo do livro *Ray Tracing in One Weekend*,
 * porém adaptado para evitar dependências externas conflitantes.
 */

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <cstdlib>

using std::sqrt;
using namespace std;

/**
 * @class vec3
 * @brief Representa um vetor ou ponto no espaço tridimensional.
 */
class vec3 {
  public:
    double e[3];  

    /**
     * @brief Constrói um vetor `(0,0,0)`
     */
    vec3() : e{0,0,0} {}

    /**
     * @brief Constrói um vetor com valores fornecidos
     * @param e0 Componente x
     * @param e1 Componente y
     * @param e2 Componente z
     */
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    /// @return componente x
    double x() const { return e[0]; }

    /// @return componente y
    double y() const { return e[1]; }

    /// @return componente z
    double z() const { return e[2]; }

    /**
     * @brief Retorna o vetor negado
     * @return `(-x, -y, -z)`
     */
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    /**
     * @brief Acesso somente-leitura a um índice do vetor
     * @param i Índice (0 = x, 1 = y, 2 = z)
     */
    double operator[](int i) const { return e[i]; }

    /**
     * @brief Acesso modificável a um índice do vetor
     * @param i Índice (0 = x, 1 = y, 2 = z)
     */
    double& operator[](int i) { return e[i]; }

    /**
     * @brief Soma o vetor atual com outro vetor
     * @param v Vetor a ser somado.
     * @return Referência para o próprio vetor
     */
    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2];
        return *this;
    }

    /**
     * @brief Multiplica o vetor por um escalar
     */
    vec3& operator*=(double t) {
        e[0] *= t; e[1] *= t; e[2] *= t;
        return *this;
    }

    /**
     * @brief Divide o vetor por um escalar
     */
    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    /**
     * @brief Calcula o comprimento do vetor
     */
    double length() const { return sqrt(length_squared()); }

    /**
     * @brief Calcula o quadrado do comprimento do vetor
     */
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    /**
     * @brief Verifica se o vetor é muito próximo de zero
     */
    bool near_zero() const {
        const auto s = 1e-8;
        return (abs(e[0]) < s) && (abs(e[1]) < s) && (abs(e[2]) < s);
    }
};

using point3 = vec3;

// -----------------------------------------------------------------------------
// Funções utilitárias de vetores
// -----------------------------------------------------------------------------

/**
 * @brief Imprime um vetor no formato "x y z"
 */
inline ostream& operator<<(ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

/**
 * @brief Soma dois vetores
 */
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

/**
 * @brief Subtrai dois vetores
 */
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

/**
 * @brief Multiplicação de dois vetores
 */
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

/**
 * @brief Multiplica vetor por escalar
 */
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

/**
 * @brief Multiplica vetor por escalar
 */
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

/**
 * @brief Divide vetor por escalar
 */
inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

/**
 * @brief Produto escalar de dois vetores
 */
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

/**
 * @brief Produto vetorial entre dois vetores
 */
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

/**
 * @brief Retorna a versão normalizada de um vetor
 */
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

/**
 * @brief Gera um vetor aleatório dentro do intervalo [0,1)
 */
inline vec3 random_vec3() {
    return vec3(rand() / (RAND_MAX + 1.0), 
                rand() / (RAND_MAX + 1.0), 
                rand() / (RAND_MAX + 1.0));
}

/**
 * @brief Gera um vetor aleatório dentro de um intervalo específico
 * @param min Valor mínimo
 * @param max Valor máximo
 */
inline vec3 random_vec3(double min, double max) {
    auto r = [=]() { return min + (max-min)*(rand() / (RAND_MAX + 1.0)); };
    return vec3(r(), r(), r());
}

/**
 * @brief Gera um vetor aleatório dentro de uma esfera unitar
 */
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = random_vec3(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

/**
 * @brief Gera um vetor unitário aleatório
 */
inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

/**
 * @brief Calcula a reflexão de um vetor em relação a uma normal
 * @param v Vetor incidente
 * @param n Normal da superfície 
 */
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*  dot(v,n) * n;
}

#endif