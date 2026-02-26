/**
 * @file WeaponInstallationVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса WeaponInstallationVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"
#include "../../auxiliary/PlaceForWeapon.hpp"
#include "../../entity/weapon/Interfaces/IWeapon.hpp"

/**
 * @class WeaponInstallationVisitor
 * @brief Посетитель для установки оружия на корабль
 */
class WeaponInstallationVisitor : public IShipVisitor {
    private:
        PlaceForWeapon place_; ///< Место для установки оружия
        std::unique_ptr<IWeapon> weapon_; ///< Оружие для установки
        bool can_install_ = false; ///< Флаг возможности установки
        bool installed_ = false; ///< Флаг успешной установки
    public:
        /**
         * @brief Конструктор
         * @param place Место для установки оружия
         * @param weapon Оружие для установки
         */
        WeaponInstallationVisitor(PlaceForWeapon place, std::unique_ptr<IWeapon> weapon) : place_(place), weapon_(std::move(weapon)) {}
        
        /**
         * @brief Деструктор
         */
        ~WeaponInstallationVisitor() override;

        void visit(TransportShip* ship) override;
        void visit(GuardShip* ship) override;
        void visit(WarShip* ship) override;

        /**
         * @brief Проверяет возможность установки оружия
         * @return bool true если оружие можно установить, false в противном случае
         */
        bool can_install() const;
        
        /**
         * @brief Проверяет, было ли оружие успешно установлено
         * @return bool true если оружие установлено, false в противном случае
         */
        bool is_installed() const;
};