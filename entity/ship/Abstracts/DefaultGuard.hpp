/**
 * @file DefaultGuard.hpp
 * @brief Заголовочный файл, содержащий определение класса DefaultGuard
 */

#pragma once

#include "../Interfaces/IGuard.hpp"
#include "../../../auxiliary/PlaceForWeapon.hpp"
#include "../../../template/LookupTable.hpp"

/**
 * @class DefaultGuard
 * @brief Реализация базовой функциональности вооружения корабля
 */
class DefaultGuard : public IGuard {
    protected:
        LookupTable<PlaceForWeapon, std::unique_ptr<IWeapon>> weapons_; ///< Карта оружия по местам установки
    public:
        /**
         * @brief Конструктор по умолчанию
         */
        DefaultGuard() = default;
        
        /**
         * @brief Деструктор
         */
        ~DefaultGuard() override = default;

        IWeapon* get_weapon_in_place(PlaceForWeapon place) const override;
        void set_weapon_in_place(PlaceForWeapon place, std::unique_ptr<IWeapon> weapon) override;
        void remove_weapon_from_place(PlaceForWeapon place) override;
        size_t get_weapon_count() const override;
        bool has_weapon_in_place(PlaceForWeapon place) const override;
        
        /**
         * @brief Получает максимальную дальность среди всего оружия
         * @return double Максимальная дальность или 0.0 если оружия нет
         */
        double get_max_range() const;
};