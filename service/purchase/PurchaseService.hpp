/**
 * @file PurchaseService.hpp
 * @brief Заголовочный файл, содержащий определение класса PurchaseService
 */

#pragma once

#include "../../mission/Mission.hpp"
#include "../../repository/ShipRepository.hpp"
#include "../../repository/PirateRepository.hpp"
#include "../catalog/ship/ShipCatalog.hpp"
#include "../catalog/weapon/WeaponCatalog.hpp"
#include "../../auxiliary/PlaceForWeapon.hpp"

/**
 * @class PurchaseService
 * @brief Сервис для управления покупкой и продажей кораблей и оружия
 */
class PurchaseService {
    private:
        Mission& mission_; ///< Ссылка на миссию
        ShipRepository& convoy_repo_; ///< Ссылка на репозиторий конвоя
        PirateRepository& pirate_repo_; ///< Ссылка на репозиторий пиратов
        ShipCatalog& ship_catalog_; ///< Ссылка на каталог кораблей
        WeaponCatalog& weapon_catalog_; ///< Ссылка на каталог оружия

        /**
         * @brief Тратит деньги из бюджета
         * @param amount Сумма для траты
         * @return bool true если деньги успешно потрачены, false в противном случае
         */
        bool spend_money(double amount);
        
        /**
         * @brief Добавляет деньги в бюджет
         * @param amount Сумма для добавления
         * @return bool true если деньги успешно добавлены, false в противном случае
         */
        bool add_money(double amount);
        
        /**
         * @brief Находит корабль по идентификатору
         * @param ship_id Идентификатор корабля
         * @return IShip* Указатель на корабль или nullptr
         */
        IShip* find_ship(const std::string& ship_id) const;
        
    public:
        /**
         * @brief Конструктор
         * @param mission Миссия
         * @param convoy_repo Репозиторий конвоя
         * @param pirate_repo Репозиторий пиратов
         * @param ship_catalog Каталог кораблей
         * @param weapon_catalog Каталог оружия
         */
        PurchaseService(Mission& mission, ShipRepository& convoy_repo, PirateRepository& pirate_repo, ShipCatalog& ship_catalog, WeaponCatalog& weapon_catalog);
        
        /**
         * @brief Покупает корабль
         * @param template_id Идентификатор шаблона корабля
         * @param is_convoy true если корабль для конвоя, false для пиратов (по умолчанию true)
         * @param position Позиция корабля (по умолчанию (0, 0))
         * @return bool true если покупка успешна, false в противном случае
         */
        bool buy_ship(const std::string& template_id, bool is_convoy = true, const Vector& position = Vector(0, 0));
        
        /**
         * @brief Продает корабль по идентификатору
         * @param ship_id Идентификатор корабля
         * @return double Сумма, полученная от продажи
         */
        double sell_ship(const std::string& ship_id);
        
        /**
         * @brief Продает корабль
         * @param ship Указатель на корабль
         * @return double Сумма, полученная от продажи
         */
        double sell_ship(IShip* ship);
        
        /**
         * @brief Покупает оружие
         * @param template_id Идентификатор шаблона оружия
         * @return std::unique_ptr<IWeapon> Указатель на купленное оружие
         */
        std::unique_ptr<IWeapon> buy_weapon(const std::string& template_id);

        /**
         * @brief Устанавливает оружие на корабль
         * @param ship_id Идентификатор корабля
         * @param place Место установки оружия
         * @param weapon_template_id Идентификатор шаблона оружия
         * @return bool true если установка успешна, false в противном случае
         */
        bool install_weapon(const std::string& ship_id, PlaceForWeapon place, const std::string& weapon_template_id);
        
        /**
         * @brief Устанавливает оружие на корабль
         * @param ship_id Идентификатор корабля
         * @param place Место установки оружия
         * @param weapon Указатель на оружие
         * @return bool true если установка успешна, false в противном случае
         */
        bool install_weapon(const std::string& ship_id, PlaceForWeapon place, std::unique_ptr<IWeapon> weapon);

        /**
         * @brief Продает оружие с корабля
         * @param ship_id Идентификатор корабля
         * @param place Место установки оружия
         * @return double Сумма, полученная от продажи
         */
        double sell_weapon(const std::string& ship_id, PlaceForWeapon place);
        
        /**
         * @brief Получает список доступных кораблей
         * @return std::vector<ShipTemplate> Вектор доступных шаблонов кораблей
         */
        std::vector<ShipTemplate> get_available_ships() const;
        
        /**
         * @brief Получает список доступного оружия
         * @return std::vector<WeaponTemplate> Вектор доступных шаблонов оружия
         */
        std::vector<WeaponTemplate> get_available_weapons() const;
        
        /**
         * @brief Получает список доступных для покупки кораблей (с учетом бюджета)
         * @return std::vector<ShipTemplate> Вектор доступных для покупки шаблонов кораблей
         */
        std::vector<ShipTemplate> get_affordable_ships() const;
        
        /**
         * @brief Получает список доступного для покупки оружия (с учетом бюджета)
         * @return std::vector<WeaponTemplate> Вектор доступных для покупки шаблонов оружия
         */
        std::vector<WeaponTemplate> get_affordable_weapons() const;
        
        /**
         * @brief Проверяет возможность потратить указанную сумму
         * @param amount Сумма для проверки
         * @return bool true если сумму можно потратить, false в противном случае
         */
        bool can_spend(double amount) const;
        
        /**
         * @brief Получает текущий бюджет
         * @return double Текущий бюджет
         */
        double get_current_budget() const;
        
        /**
         * @brief Получает начальный бюджет
         * @return double Начальный бюджет
         */
        double get_initial_budget() const;
        
        /**
         * @brief Проверяет наличие оружия в указанном месте на корабле
         * @param ship_id Идентификатор корабля
         * @param place Место установки оружия
         * @return bool true если оружие есть, false в противном случае
         */
        bool has_weapon_in_place(const std::string &ship_id, PlaceForWeapon place) const;
        
        /**
         * @brief Проверяет наличие свободного места на кораблях
         * @return bool true если есть свободное место, false в противном случае
         */
        bool has_free_place() const;
        
        /**
         * @brief Проверяет наличие занятого места на кораблях
         * @return bool true если есть занятое место, false в противном случае
         */
        bool has_occupied_place() const;
        
        /**
         * @brief Проверяет валидность покупки корабля
         * @param template_id Идентификатор шаблона корабля
         * @return bool true если покупка валидна, false в противном случае
         */
        bool validate_ship_purchase(const std::string& template_id) const;
        
        /**
         * @brief Проверяет валидность покупки оружия
         * @param template_id Идентификатор шаблона оружия
         * @return bool true если покупка валидна, false в противном случае
         */
        bool validate_weapon_purchase(const std::string& template_id) const;
};