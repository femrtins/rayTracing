/**
 * @file vec3.h
 * @brief Implementação de um vetor 3D utilizado para representar 
 * posições, direções, cores e deslocamentos
 *
 * A classe suporta várias operações vetoriais, incluindo soma, 
 * subtração, produto escalar, produto vetorial e normalização.
 */

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

/**
 * @class vec3
 * @brief Classe que representa um vetor tridimensional.
 *
 * Esta classe é usada para representar vetores em 3D para geometrias, 
 * direções, cores e pontos.
 */
class vec3 {
    
  public:
    double e[3];

    /**
     * @brief Construtor padrão. Inicializa o vetor como (0, 0, 0).
     */
    vec3() : e{0,0,0} {}

    /**
     * @brief Construtor com valores iniciais.
     * @param e0 Componente X.
     * @param e1 Componente Y.
     * @param e2 Componente Z.
     */
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    /**
     * @brief Retorna a componente X do vetor.
     */
    double x() const { return e[0]; }

    /**
     * @brief Retorna a componente X do vetor.
     */
    double y() const { return e[1]; }

    /**
     * @brief Retorna a componente Z do vetor.
     */
    double z() const { return e[2]; }

    /**
     * @brief Retorna o vetor oposto
     * @return Novo vetor com todas as componentes multiplicadas por -1.
     */
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    /**
     * @brief Acessa uma componente do vetor.
     * @param i Índice (0=x, 1=y, 2=z)
     * @return Valor da componente.
     */
    double operator[](int i) const { return e[i]; }

    /**
     * @brief Acessa e permite modificar uma componente do vetor.
     * @param i Índice (0=x, 1=y, 2=z)
     * @return Referência para a componente.
     */
    double& operator[](int i) { return e[i]; }

    /**
     * @brief Soma outro vetor ao vetor atual.
     * @param v Vetor a ser somado.
     * @return Referência ao vetor atual após modificação.
     */
    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    /**
     * @brief Multiplica o vetor por um escalar.
     * @param t Escalar.
     * @return Referência ao vetor atual após modificação.
     */
    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    /**
     * @brief Divide o vetor por um escalar.
     * @param t Escalar.
     * @return Referência ao vetor atual após modificação.
     */
    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    /**
     * @brief Retorna o comprimento do vetor.
     */
    double length() const {
        return std::sqrt(length_squared());
    }

    /**
     * @brief Retorna o comprimento ao quadrado do vetor.
     */
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    bool near_zero() const {
    // Retorna true se o vetor for muito pequeno (quase zero)
    const auto s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

};

/// Alias para representar pontos no espaço 3D.
using point3 = vec3;


// Vector Utility Functions

/**
 * @brief Operador para imprimir o vetor em um stream de saída.
 */
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

/**
 * @brief Soma dois vetores.
 */
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

/**
 * @brief Subtrai dois vetores.
 */
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

/**
 * @brief Produto Hadamard entre dois vetores.
 */
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

/**
 * @brief Multiplica um vetor por um escalar.
 */
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

/**
 * @brief Multiplica um vetor por um escalar.
 */
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

/**
 * @brief Divide um vetor por um escalar.
 */
inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

/**
 * @brief Calcula o produto escalar entre dois vetores.
 */
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

/**
 * @brief Calcula o produto vetorial entre dois vetores.
 */
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

/**
 * @brief Retorna o vetor normalizado (unitário).
 */
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_vec3() {
    return vec3(random_double(), random_double(), random_double());
}

inline vec3 random_vec3(double min, double max) {
    return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

// Método de rejeição: gera vetores aleatórios até achar um dentro de uma esfera unitária
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = random_vec3(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

// Normaliza para garantir que está na superfície da esfera
inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}


#endif