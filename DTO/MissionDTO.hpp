/**
 * @file MissionDTO.hpp
 * @brief Заголовочный файл, содержащий определение структуры MissionDTO
 */

#pragma once

#include <string>
#include "PirateBaseDTO.hpp"
#include "../auxiliary/Military.hpp"
#include "../auxiliary/Vector.hpp"

/**
 * @struct MissionDTO
 * @brief Структура DTO (Data Transfer Object) для передачи данных о миссии
 */
struct MissionDTO {
    std::string id = ""; ///< Идентификатор миссии
    Military commander = {"", ""}; ///< Командир миссии

    double total_budget; ///< Общий бюджет миссии
    double current_budget; ///< Текущий бюджет миссии
    
    double total_cargo; ///< Общий груз миссии
    double current_cargo; ///< Текущий груз миссии
    double required_cargo_percentage; ///< Процент необходимого груза
    
    size_t max_convoy_ships; ///< Максимальное количество кораблей конвоя
    size_t max_pirate_ships; ///< Максимальное количество пиратских кораблей
    
    Vector base_a; ///< Координаты базы А
    Vector base_b; ///< Координаты базы Б
    double base_size; ///< Размер базы

    std::vector<PirateBaseDTO> pirate_bases; ///< Вектор пиратских баз в формате DTO

    bool is_completed; ///< Флаг завершения миссии
    bool is_successful; ///< Флаг успешности миссии
};