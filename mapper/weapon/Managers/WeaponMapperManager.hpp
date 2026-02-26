/**
 * @file WeaponMapperManager.hpp
 * @brief Заголовочный файл, содержащий определение класса WeaponMapperManager
 */

#pragma once

#include "../FromDTO/IWeaponMapper.hpp"
#include "../../../template/LookupTable.hpp"

/**
 * @class WeaponMapperManager
 * @brief Менеджер мапперов для преобразования WeaponDTO в IWeapon
 */
class WeaponMapperManager {
    private:
        LookupTable<std::string, std::unique_ptr<IWeaponMapper>> mappers_; ///< Карта зарегистрированных мапперов
    public:
        /**
         * @brief Конструктор
         */
        WeaponMapperManager();

        /**
         * @brief Регистрирует маппер для определенного типа оружия
         * @param type Тип оружия
         * @param mapper Указатель на маппер
         */
        void register_mapper(const std::string& type, std::unique_ptr<IWeaponMapper> mapper);
        
        /**
         * @brief Создает IWeapon из WeaponDTO
         * @param weapon_dto Объект DTO оружия
         * @return std::unique_ptr<IWeapon> Указатель на созданное оружие
         */
        std::unique_ptr<IWeapon> create_weapon(const WeaponDTO& weapon_dto) const;
};