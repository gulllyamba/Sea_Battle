/**
 * @file WeaponDTOMapperManager.hpp
 * @brief Заголовочный файл, содержащий определение класса WeaponDTOMapperManager
 */

#pragma once

#include "../ToDTO/IWeaponDTOMapper.hpp"
#include "../../../template/LookupTable.hpp"

/**
 * @class WeaponDTOMapperManager
 * @brief Менеджер мапперов для преобразования IWeapon в WeaponDTO
 */
class WeaponDTOMapperManager {
    private:
        LookupTable<std::string, std::unique_ptr<IWeaponDTOMapper>> mappers_; ///< Карта зарегистрированных мапперов
    public:
        /**
         * @brief Конструктор
         */
        WeaponDTOMapperManager();

        /**
         * @brief Регистрирует маппер для определенного типа оружия
         * @param type Тип оружия
         * @param mapper Указатель на маппер
         */
        void register_mapper(const std::string& type, std::unique_ptr<IWeaponDTOMapper> mapper);
        
        /**
         * @brief Создает WeaponDTO из IWeapon
         * @param weapon Указатель на объект оружия
         * @return WeaponDTO Объект DTO оружия
         */
        WeaponDTO create_weapon_dto(const IWeapon* weapon) const;
};