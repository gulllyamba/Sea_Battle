/**
 * @file IGuard.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IGuard
 */

#pragma once

#include "../../weapon/Interfaces/IWeapon.hpp"
#include "../../../auxiliary/PlaceForWeapon.hpp"

/**
 * @class IGuard
 * @brief Интерфейс, представляющий вооружение корабля
 */
class IGuard {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IGuard() = default;

        /**
         * @brief Получает оружие в указанном месте
         * @param place Место расположения оружия
         * @return IWeapon* Указатель на оружие или nullptr если оружия нет
         */
        virtual IWeapon* get_weapon_in_place(PlaceForWeapon place) const = 0;

        /**
         * @brief Проверяет наличие оружия в указанном месте
         * @param place Место расположения оружия
         * @return bool true если оружие есть, false в противном случае
         */
        virtual bool has_weapon_in_place(PlaceForWeapon place) const = 0;
        
        /**
         * @brief Устанавливает оружие в указанное место
         * @param place Место расположения оружия
         * @param weapon Указатель на устанавливаемое оружие
         */
        virtual void set_weapon_in_place(PlaceForWeapon place, std::unique_ptr<IWeapon> weapon) = 0;

        /**
         * @brief Удаляет оружие из указанного места
         * @param place Место расположения оружия
         */
        virtual void remove_weapon_from_place(PlaceForWeapon place) = 0;
        
        /**
         * @brief Получает количество установленного оружия
         * @return size_t Количество установленного оружия
         */
        virtual size_t get_weapon_count() const = 0;
};