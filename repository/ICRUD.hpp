/**
 * @file ICRUD.hpp
 * @brief Заголовочный файл, содержащий определение шаблонного интерфейса ICRUD
 */

#pragma once

#include <memory>
#include <vector>
#include <optional>

/**
 * @class ICRUD
 * @brief Шаблонный интерфейс операций Create, Read, Update, Delete (CRUD)
 * @tparam T Тип сущности
 * @tparam ID Тип идентификатора сущности
 */
template<typename T, typename ID>
class ICRUD {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~ICRUD() = default;
        
        /**
         * @brief Создает новую сущность
         * @param entity Указатель на создаваемую сущность
         */
        virtual void create(std::unique_ptr<T> entity) = 0;
        
        /**
         * @brief Читает сущность по идентификатору
         * @param id Идентификатор сущности
         * @return std::unique_ptr<T> Указатель на найденную сущность или nullptr
         */
        virtual std::unique_ptr<T> read(const ID& id) const = 0;
        
        /**
         * @brief Читает все сущности
         * @return std::vector<std::unique_ptr<T>> Вектор всех сущностей
         */
        virtual std::vector<std::unique_ptr<T>> read_all() const = 0;
        
        /**
         * @brief Проверяет существование сущности по идентификатору
         * @param id Идентификатор сущности
         * @return bool true если сущность существует, false в противном случае
         */
        virtual bool exists(const ID& id) const = 0;
        
        /**
         * @brief Считает количество сущностей
         * @return size_t Количество сущностей
         */
        virtual size_t count() const = 0;
        
        /**
         * @brief Обновляет сущность
         * @param entity Указатель на обновляемую сущность
         */
        virtual void update(std::unique_ptr<T> entity) = 0;
        
        /**
         * @brief Удаляет сущность по идентификатору
         * @param id Идентификатор сущности для удаления
         */
        virtual void remove(const ID& id) = 0;
        
        /**
         * @brief Очищает все сущности
         */
        virtual void clear() = 0;
};