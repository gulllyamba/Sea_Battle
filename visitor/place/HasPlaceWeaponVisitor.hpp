/**
 * @file HasPlaceWeaponVisitor.hpp
 * @brief Заголовочный файл, содержащий определение класса HasPlaceWeaponVisitor
 */

#pragma once

#include "../IShipVisitor.hpp"
#include "../../auxiliary/PlaceForWeapon.hpp"

/**
 * @class HasPlaceWeaponVisitor
 * @brief Посетитель для проверки наличия оружия в определенном месте на корабле
 */
class HasPlaceWeaponVisitor : public IShipVisitor {
    private:
        PlaceForWeapon place_; ///< Место для проверки оружия
        bool has_weapon_ = false; ///< Флаг наличия оружия
    public:
        /**
         * @brief Конструктор
         * @param place Место для проверки оружия
         */
        HasPlaceWeaponVisitor(PlaceForWeapon place);
        
        /**
         * @brief Деструктор
         */
        ~HasPlaceWeaponVisitor() override;

        void visit(TransportShip* ship) override;
        void visit(GuardShip* ship) override;
        void visit(WarShip* ship) override;

        /**
         * @brief Получает место для проверки оружия
         * @return PlaceForWeapon Место для проверки оружия
         */
        PlaceForWeapon get_place() const;
        
        /**
         * @brief Проверяет наличие оружия в указанном месте
         * @return bool true если оружие есть, false в противном случае
         */
        bool has_weapon() const;
};