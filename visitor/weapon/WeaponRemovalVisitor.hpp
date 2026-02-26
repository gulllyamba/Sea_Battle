/**
 * @file WeaponRemovalVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса WeaponRemovalVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"
#include "../../auxiliary/PlaceForWeapon.hpp"
#include "../../entity/weapon/Interfaces/IWeapon.hpp"

/**
 * @class WeaponRemovalVisitor
 * @brief Посетитель для удаления оружия с корабля
 */
class WeaponRemovalVisitor : public IShipVisitor {
    private:
        PlaceForWeapon place_; ///< Место для удаления оружия
        double removed_weapon_cost_ = 0.0; ///< Стоимость удаленного оружия
        bool can_remove_ = false; ///< Флаг возможности удаления
        bool removed_ = false; ///< Флаг успешного удаления
    public:
        /**
         * @brief Конструктор
         * @param place Место для удаления оружия
         */
        WeaponRemovalVisitor(PlaceForWeapon place) : place_(place) {}
        
        /**
         * @brief Деструктор
         */
        ~WeaponRemovalVisitor();
        
        void visit(TransportShip* ship) override;
        void visit(GuardShip* ship) override;
        void visit(WarShip* ship) override;
        
        /**
         * @brief Получает стоимость удаленного оружия
         * @return double Стоимость удаленного оружия
         */
        double get_weapon_cost() const;

        /**
         * @brief Проверяет возможность удаления оружия
         * @return bool true если оружие можно удалить, false в противном случае
         */
        bool can_remove() const;
        
        /**
         * @brief Проверяет, было ли оружие успешно удалено
         * @return bool true если оружие удалено, false в противном случае
         */
        bool is_removed() const;
};