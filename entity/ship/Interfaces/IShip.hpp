/**
 * @file IShip.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IShip
 */

#pragma once

#include <string>
#include <memory>
#include "../../../auxiliary/Military.hpp"
#include "IShipPosition.hpp"
#include "IShipHealth.hpp"
#include "../../../visitor/IShipVisitor.hpp"

/**
 * @class IShip
 * @brief Интерфейс, представляющий корабль
 */
class IShip : public IShipPosition, public IShipHealth {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IShip() = default;

        /**
         * @brief Получает тип корабля
         * @return std::string Тип корабля
         */
        virtual std::string get_type() const = 0;
        
        /**
         * @brief Получает название корабля
         * @return std::string Название корабля
         */
        virtual std::string get_name() const = 0;
        
        /**
         * @brief Получает капитана корабля
         * @return Military Капитан корабля
         */
        virtual Military get_captain() const = 0;
        
        /**
         * @brief Получает максимальную скорость корабля
         * @return double Максимальная скорость корабля
         */
        virtual double get_max_speed() const = 0;
        
        /**
         * @brief Получает стоимость корабля
         * @return double Стоимость корабля
         */
        virtual double get_cost() const = 0;
        
        /**
         * @brief Получает идентификатор корабля
         * @return std::string Идентификатор корабля
         */
        virtual std::string get_ID() const = 0;

        /**
         * @brief Устанавливает название корабля
         * @param name Новое название корабля
         */
        virtual void set_name(const std::string& name) = 0;
        
        /**
         * @brief Устанавливает капитана корабля
         * @param captain Новый капитан корабля
         */
        virtual void set_captain(const Military& captain) = 0;
        
        /**
         * @brief Устанавливает максимальную скорость корабля
         * @param max_speed Новая максимальная скорость корабля
         */
        virtual void set_max_speed(double max_speed) = 0;
        
        /**
         * @brief Устанавливает стоимость корабля
         * @param cost Новая стоимость корабля
         */
        virtual void set_cost(double cost) = 0;
        
        /**
         * @brief Устанавливает идентификатор корабля
         * @param id Новый идентификатор корабля
         */
        virtual void set_ID(const std::string& id) = 0;

        /**
         * @brief Проверяет, является ли корабль частью конвоя
         * @return bool true если корабль в конвое, false в противном случае
         */
        virtual bool is_convoy() const = 0;
        
        /**
         * @brief Устанавливает флаг конвоя
         * @param is_convoy true если корабль в конвое, false в противном случае
         */
        virtual void set_convoy(bool is_convoy) = 0;

        /**
         * @brief Получает описание корабля
         * @return std::string Описание корабля
         */
        virtual std::string get_description() const = 0;
        
        /**
         * @brief Клонирует корабль
         * @return std::unique_ptr<IShip> Указатель на клон корабля
         */
        virtual std::unique_ptr<IShip> clone() const = 0;

        /**
         * @brief Принимает посетителя
         * @param visitor Посетитель корабля
         */
        virtual void accept(IShipVisitor* visitor) = 0;
};