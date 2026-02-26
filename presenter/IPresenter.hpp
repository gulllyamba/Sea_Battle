/**
 * @file IPresenter.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IPresenter
 */

#pragma once

#include <vector>
#include "../DTO/ShipDTO.hpp"
#include "../DTO/WeaponDTO.hpp"
#include "../DTO/MissionDTO.hpp"
#include "../DTO/PirateBaseDTO.hpp"
#include "../service/catalog/ship/ShipTemplate.hpp"
#include "../service/catalog/weapon/WeaponTemplate.hpp"

/**
 * @class IPresenter
 * @brief Интерфейс презентера, управляющего игровым процессом
 */
class IPresenter {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IPresenter() = default;

        /**
         * @brief Получает список доступных кораблей
         * @return std::vector<ShipTemplate> Вектор доступных шаблонов кораблей
         */
        virtual const std::vector<ShipTemplate> get_available_ships() const = 0;
        
        /**
         * @brief Получает список доступного оружия
         * @return std::vector<WeaponTemplate> Вектор доступных шаблонов оружия
         */
        virtual const std::vector<WeaponTemplate> get_available_weapons() const = 0;

        /**
         * @brief Покупает корабль по шаблону
         * @param template_id Идентификатор шаблона корабля
         * @return bool true если покупка успешна, false в противном случае
         */
        virtual bool purchase_ship(const std::string &template_id) = 0;

        /**
         * @brief Продает корабль
         * @param template_id Идентификатор шаблона корабля
         * @return bool true если продажа успешна, false в противном случае
         */
        virtual bool sell_ship(const std::string &template_id) = 0;

        /**
         * @brief Продает оружие с корабля
         * @param ship_id Идентификатор корабля
         * @param place Место установки оружия
         * @return bool true если продажа успешна, false в противном случае
         */
        virtual bool sell_weapon(const std::string &ship_id, PlaceForWeapon place) = 0;
        
        /**
         * @brief Получает текущий бюджет
         * @return double Текущий бюджет
         */
        virtual double get_current_budget() const = 0;
        
        /**
         * @brief Получает общий бюджет
         * @return double Общий бюджет
         */
        virtual double get_total_budget() const = 0;
        
        /**
         * @brief Устанавливает оружие на корабль
         * @param ship_id Идентификатор корабля
         * @param place Место установки оружия
         * @param weapon_template_id Идентификатор шаблона оружия
         * @return bool true если установка успешна, false в противном случае
         */
        virtual bool install_weapon(const std::string &ship_id, PlaceForWeapon place, const std::string &weapon_template_id) = 0;

        /**
         * @brief Проверяет наличие оружия в указанном месте на корабле
         * @param ship_id Идентификатор корабля
         * @param place Место установки оружия
         * @return bool true если оружие есть, false в противном случае
         */
        virtual bool has_weapon_in_place(const std::string &ship_id, PlaceForWeapon place) const = 0;

        /**
         * @brief Проверяет возможность потратить указанную сумму
         * @param amount Сумма для проверки
         * @return bool true если сумму можно потратить, false в противном случае
         */
        virtual bool can_spend(double amount) const = 0;

        /**
         * @brief Проверяет наличие свободного места на кораблях
         * @return bool true если есть свободное место, false в противном случае
         */
        virtual bool has_free_place() const = 0;

        /**
         * @brief Проверяет наличие занятого места на кораблях
         * @return bool true если есть занятое место, false в противном случае
         */
        virtual bool has_occupied_place() const = 0;

        /**
         * @brief Получает общий объем груза
         * @return double Общий объем груза
         */
        virtual double get_total_cargo() const = 0;
        
        /**
         * @brief Получает текущий груз
         * @return double Текущий груз
         */
        virtual double get_current_cargo() const = 0;
        
        /**
         * @brief Получает оставшийся груз
         * @return double Оставшийся груз
         */
        virtual double get_remaining_cargo() const = 0;
        
        /**
         * @brief Получает вместимость корабля
         * @param ship_id Идентификатор корабля
         * @return double Вместимость корабля
         */
        virtual double get_ship_capacity(const std::string &ship_id) const = 0;
        
        /**
         * @brief Получает текущий груз корабля
         * @param ship_id Идентификатор корабля
         * @return double Текущий груз корабля
         */
        virtual double get_ship_current_cargo(const std::string &ship_id) const = 0;
        
        /**
         * @brief Загружает груз на корабль
         * @param ship_id Идентификатор корабля
         * @param amount Количество груза
         * @return bool true если загрузка успешна, false в противном случае
         */
        virtual bool load_cargo(const std::string& ship_id, double amount) = 0;
        
        /**
         * @brief Выгружает груз с корабля
         * @param ship_id Идентификатор корабля
         * @param amount Количество груза
         * @return bool true если выгрузка успешна, false в противном случае
         */
        virtual bool unload_cargo(const std::string &ship_id, double amount) = 0;
        
        /**
         * @brief Автоматически распределяет груз между кораблями
         */
        virtual void auto_distribute_cargo() = 0;

        /**
         * @brief Получает информацию о миссии
         * @return MissionDTO Миссия в формате DTO
         */
        virtual MissionDTO get_mission() const = 0;
        
        /**
         * @brief Получает корабли конвоя
         * @return std::vector<ShipDTO> Вектор кораблей конвоя в формате DTO
         */
        virtual std::vector<ShipDTO> get_convoy_ships() const = 0;

        /**
         * @brief Получает грузовые корабли
         * @return std::vector<ShipDTO> Вектор грузовых кораблей в формате DTO
         */
        virtual std::vector<ShipDTO> get_cargo_ships() const = 0;

        /**
         * @brief Получает атакующие корабли
         * @return std::vector<ShipDTO> Вектор атакующих кораблей в формате DTO
         */
        virtual std::vector<ShipDTO> get_attack_ships() const = 0;
        
        /**
         * @brief Считает количество кораблей в конвое
         * @return size_t Количество кораблей в конвое
         */
        virtual size_t count_convoy_ships() const = 0;
        
        /**
         * @brief Считает количество живых кораблей в конвое
         * @return size_t Количество живых кораблей в конвое
         */
        virtual size_t count_alive_convoy_ships() const = 0;
        
        /**
         * @brief Получает пиратские корабли
         * @return std::vector<ShipDTO> Вектор пиратских кораблей в формате DTO
         */
        virtual std::vector<ShipDTO> get_pirate_ships() const = 0;
        
        /**
         * @brief Считает количество живых пиратских кораблей
         * @return size_t Количество живых пиратских кораблей
         */
        virtual size_t count_alive_pirate_ships() const = 0;
        
        /**
         * @brief Получает корабль по идентификатору
         * @param ship_id Идентификатор корабля
         * @return ShipDTO Корабль в формате DTO
         */
        virtual ShipDTO get_ship_by_id(std::string& ship_id) const = 0;
        
        /**
         * @brief Получает пиратские базы
         * @return std::vector<PirateBaseDTO> Вектор пиратских баз в формате DTO
         */
        virtual std::vector<PirateBaseDTO> get_pirate_bases() const = 0;

        /**
         * @brief Двигает конвой
         * @param dt Временной шаг
         */
        virtual void move_convoy(double dt) = 0;
        
        /**
         * @brief Начинает движение конвоя
         */
        virtual void start_convoy() = 0;
        
        /**
         * @brief Останавливает конвой
         */
        virtual void stop_convoy() = 0;

        /**
         * @brief Двигает пиратов
         * @param dt Временной шаг
         */
        virtual void move_pirates(double dt) = 0;
        
        /**
         * @brief Начинает движение пиратов
         */
        virtual void start_pirates() = 0;
        
        /**
         * @brief Останавливает пиратов
         */
        virtual void stop_pirates() = 0;
        
        /**
         * @brief Выполняет автоматический бой(последовательно)
         */
        virtual void auto_combat_sequential() = 0;

        /**
         * @brief Выполняет автоматический бой(параллельно)
         */
        virtual void auto_combat_parallel() = 0;

        /**
         * @brief Проверяет наличие активированной базы
         * @return int Индекс активированной базы или -1 если нет активированных
         */
        virtual int has_activated_base() const = 0;

        /**
         * @brief Обновляет статус базы по индексу
         * @param index Индекс базы для обновления
         */
        virtual void update_base_status(size_t index) = 0;

        /**
         * @brief Проверяет, достиг ли конвой пункта назначения
         * @return bool true если конвой достиг пункта назначения, false в противном случае
         */
        virtual bool has_reached_destination() const = 0;

        /**
         * @brief Проверяет, завершена ли миссия
         * @return bool true если миссия завершена, false в противном случае
         */
        virtual bool mission_completed() const = 0;
        
        /**
         * @brief Получает скорость конвоя
         * @return double Скорость конвоя
         */
        virtual double get_convoy_speed() const = 0;
        
        /**
         * @brief Получает центр конвоя
         * @return Vector Центр конвоя
         */
        virtual Vector get_convoy_center() const = 0;
        
        /**
         * @brief Получает расстояние до пункта назначения
         * @return double Расстояние до пункта назначения
         */
        virtual double get_distanse_to_destination() const = 0;

        /**
         * @brief Устанавливает стратегию конвоя
         * @param strategy Название стратегии
         */
        virtual void set_convoy_strategy(const std::string& strategy) = 0;
        
        /**
         * @brief Устанавливает стратегию пиратов
         * @param strategy Название стратегии
         */
        virtual void set_pirate_strategy(const std::string& strategy) = 0;
        
        /**
         * @brief Сохраняет игру
         * @param path Путь для сохранения
         */
        virtual void save_game(const std::string& path) = 0;
        
        /**
         * @brief Загружает игру
         * @param path Путь для загрузки
         */
        virtual void load_game(const std::string& path) = 0;

        /**
         * @brief Получает информацию о конвое
         * @return std::string Информация о конвое
         */
        virtual std::string convoy_info() const = 0;

        /**
         * @brief Получает информацию о пиратах
         * @return std::string Информация о пиратах
         */
        virtual std::string pirate_info() const = 0;
};