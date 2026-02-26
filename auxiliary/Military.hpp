/**
 * @file Military.hpp
 * @brief Заголовочный файл, содержащий определение структуры Military
 */

#pragma once

#include <string>

/**
 * @struct Military
 * @brief Структура, представляющая военнослужащего
 */
struct Military {
    std::string FIO; ///< Фамилия Имя Отчество военнослужащего
    std::string rank; ///< Звание военнослужащего

    /**
     * @brief Конструктор по умолчанию
     */
    Military() : FIO(), rank() {}
    
    /**
     * @brief Конструктор с параметрами
     * @param fio Фамилия Имя Отчество военнослужащего
     * @param rank Звание военнослужащего
     */
    Military(std::string fio, std::string rank) : FIO(fio), rank(rank) {}

    /**
     * @brief Оператор сравнения на равенство
     * @param other Другой объект Military для сравнения
     * @return true Если ФИО и звание совпадают, false в противном случае
     */
    bool operator==(const Military& other) const {
        return FIO == other.FIO && rank == other.rank;
    }
};