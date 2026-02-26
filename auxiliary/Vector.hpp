/**
 * @file Vector.hpp
 * @brief Заголовочный файл, содержащий определение структуры Vector
 */

#pragma once

/**
 * @struct Vector
 * @brief Структура, представляющая двумерный вектор
 */
struct Vector {
    double x; ///< Координата по оси X
    double y; ///< Координата по оси Y

    /**
     * @brief Конструктор по умолчанию
     */
    Vector() : x(0.0), y(0.0) {}
    
    /**
     * @brief Конструктор с параметрами
     * @param x Координата по оси X
     * @param y Координата по оси Y
     */
    Vector(double x, double y) : x(x), y(y) {}

    /**
     * @brief Оператор сложения векторов
     * @param other Другой вектор для сложения
     * @return Vector Результат сложения векторов
     */
    Vector operator+(const Vector& other) const {
        Vector result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }
    
    /**
     * @brief Оператор сравнения на равенство (с учетом погрешности)
     * @param other Другой вектор для сравнения
     * @return true Если векторы равны с заданной точностью, false в противном случае
     */
    bool operator==(const Vector& other) const {
        return ((x - other.x) < 1e-9) && ((y - other.y) < 1e-9);
    }
};