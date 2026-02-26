/**
 * @file TableNode.hpp
 * @brief Заголовочный файл, содержащий определение структур для узлов таблицы
 */

#pragma once

#include <utility>
#include <variant>
#include <string>
#include <memory>

/**
 * @struct empty_t
 * @brief Структура, представляющая пустую ячейку в таблице
 */
struct empty_t {};

/**
 * @struct empty_first_t
 * @brief Структура, представляющая первую пустую ячейку в таблице
 */
struct empty_first_t {};

/**
 * @struct empty_last_t
 * @brief Структура, представляющую последнюю пустую ячейку в таблице
 */
struct empty_last_t {};

/**
 * @struct occupied_t
 * @brief Структура, представляющая занятую ячейку в таблице
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 */
template <typename Key, typename T>
struct occupied_t {
    std::pair<const Key, T> data_; ///< Пара ключ-значение

    /**
     * @brief Конструктор по умолчанию
     */
    occupied_t() : data_() {}
    
    /**
     * @brief Конструктор с параметрами (копирование)
     * @param key Ключ
     * @param value Значение
     */
    occupied_t(const Key& key, const T& value) : data_(key, value) {}
    
    /**
     * @brief Конструктор с параметрами (перемещение)
     * @param key Ключ
     * @param value Значение
     */
    occupied_t(Key&& key, T&& value) : data_(std::move(key), std::move(value)) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Другой объект occupied_t
     */
    occupied_t(const occupied_t& other) : data_(other.data_) {}
    
    /**
     * @brief Конструктор перемещения
     * @param other Другой объект occupied_t
     */
    occupied_t(occupied_t&& other) noexcept : data_(std::move(other.data_)) {}

    /**
     * @brief Оператор перемещающего присваивания
     * @param other Другой объект occupied_t
     * @return occupied_t& Ссылка на текущий объект
     */
    occupied_t& operator=(occupied_t&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }
};

/**
 * @struct occupied_first_t
 * @brief Структура, представляющая первую занятую ячейку в таблице
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 */
template <typename Key, typename T>
struct occupied_first_t {
    std::pair<const Key, T> data_; ///< Пара ключ-значение

    /**
     * @brief Конструктор по умолчанию
     */
    occupied_first_t() : data_() {}
    
    /**
     * @brief Конструктор с параметрами (копирование)
     * @param key Ключ
     * @param value Значение
     */
    occupied_first_t(const Key& key, const T& value) : data_(key, value) {}
    
    /**
     * @brief Конструктор с параметрами (перемещение)
     * @param key Ключ
     * @param value Значение
     */
    occupied_first_t(Key&& key, T&& value) : data_(std::move(key), std::move(value)) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Другой объект occupied_first_t
     */
    occupied_first_t(const occupied_first_t& other) : data_(other.data_) {}
    
    /**
     * @brief Конструктор перемещения
     * @param other Другой объект occupied_first_t
     */
    occupied_first_t(occupied_first_t&& other) noexcept : data_(std::move(other.data_)) {}

    /**
     * @brief Оператор перемещающего присваивания
     * @param other Другой объект occupied_first_t
     * @return occupied_first_t& Ссылка на текущий объект
     */
    occupied_first_t& operator=(occupied_first_t&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }
};

/**
 * @struct occupied_last_t
 * @brief Структура, представляющая последнюю занятую ячейку в таблице
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 */
template <typename Key, typename T>
struct occupied_last_t {
    std::pair<const Key, T> data_; ///< Пара ключ-значение

    /**
     * @brief Конструктор по умолчанию
     */
    occupied_last_t() : data_() {}
    
    /**
     * @brief Конструктор с параметрами (копирование)
     * @param key Ключ
     * @param value Значение
     */
    occupied_last_t(const Key& key, const T& value) : data_(key, value) {}
    
    /**
     * @brief Конструктор с параметрами (перемещение)
     * @param key Ключ
     * @param value Значение
     */
    occupied_last_t(Key&& key, T&& value) : data_(std::move(key), std::move(value)) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Другой объект occupied_last_t
     */
    occupied_last_t(const occupied_last_t& other) : data_(other.data_) {}
    
    /**
     * @brief Конструктор перемещения
     * @param other Другой объект occupied_last_t
     */
    occupied_last_t(occupied_last_t&& other) noexcept : data_(std::move(other.data_)) {}

    /**
     * @brief Оператор перемещающего присваивания
     * @param other Другой объект occupied_last_t
     * @return occupied_last_t& Ссылка на текущий объект
     */
    occupied_last_t& operator=(occupied_last_t&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }
};

/**
 * @typedef TableNode
 * @brief Тип узла таблицы, представляющий собой variant из всех возможных состояний ячейки
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 */
template <typename Key, typename T>
using TableNode = std::variant<empty_first_t, empty_t, empty_last_t, occupied_first_t<Key, T>, occupied_t<Key, T>, occupied_last_t<Key, T>>;

/**
 * @brief Обменивает содержимое двух variant узлов
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 * @param a Первый узел
 * @param b Второй узел
 */
template <typename Key, typename T>
void swap_variants(TableNode<Key, T>& a, TableNode<Key, T>& b) {
    size_t idx_a = a.index();
    size_t idx_b = b.index();

    TableNode<Key, T> temp_a;

    switch (idx_a) {
        case 0: temp_a.template emplace<empty_first_t>(); break;
        case 1: temp_a.template emplace<empty_t>(); break;
        case 2: temp_a.template emplace<empty_last_t>(); break;
        case 3: {
            auto& node_a = std::get<3>(a);
            temp_a.template emplace<3>(node_a.data_.first, std::move(node_a.data_.second));
            break;
        }
        case 4: {
            auto& node_a = std::get<4>(a);
            temp_a.template emplace<4>(node_a.data_.first, std::move(node_a.data_.second));
            break;
        }
        case 5: {
            auto& node_a = std::get<5>(a);
            temp_a.template emplace<5>(node_a.data_.first, std::move(node_a.data_.second));
            break;
        }
    }
    
    switch (idx_b) {
        case 0: a.template emplace<empty_first_t>(); break;
        case 1: a.template emplace<empty_t>(); break;
        case 2: a.template emplace<empty_last_t>(); break;
        case 3: {
            auto& node_b = std::get<3>(b);
            a.template emplace<3>(node_b.data_.first, std::move(node_b.data_.second));
            break;
        }
        case 4: {
            auto& node_b = std::get<4>(b);
            a.template emplace<4>(node_b.data_.first, std::move(node_b.data_.second));
            break;
        }
        case 5: {
            auto& node_b = std::get<5>(b);
            a.template emplace<5>(node_b.data_.first, std::move(node_b.data_.second));
            break;
        }
    }

    switch (idx_a) {
        case 0: b.template emplace<empty_first_t>(); break;
        case 1: b.template emplace<empty_t>(); break;
        case 2: b.template emplace<empty_last_t>(); break;
        case 3: {
            auto& node_temp = std::get<3>(temp_a);
            b.template emplace<3>(node_temp.data_.first, std::move(node_temp.data_.second));
            break;
        }
        case 4: {
            auto& node_temp = std::get<4>(temp_a);
            b.template emplace<4>(node_temp.data_.first, std::move(node_temp.data_.second));
            break;
        }
        case 5: {
            auto& node_temp = std::get<5>(temp_a);
            b.template emplace<5>(node_temp.data_.first, std::move(node_temp.data_.second));
            break;
        }
    }
}

/**
 * @struct occupied_t<Key, std::unique_ptr<T>>
 * @brief Специализация для occupied_t с уникальными указателями
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 */
template<typename Key, typename T>
struct occupied_t<Key, std::unique_ptr<T>> {
    std::pair<const Key, std::unique_ptr<T>> data_; ///< Пара ключ-значение с уникальным указателем
    
    /**
     * @brief Конструктор с параметрами
     * @param key Ключ
     * @param value Значение (уникальный указатель)
     */
    occupied_t(const Key& key, std::unique_ptr<T>&& value) : data_(key, std::move(value)) {}
    
    /**
     * @brief Удаленный конструктор копирования
     */
    occupied_t(const occupied_t&) = delete;
    
    /**
     * @brief Конструктор перемещения
     * @param other Другой объект occupied_t
     */
    occupied_t(occupied_t&& other) noexcept : data_(std::move(other.data_)) {}
    
    /**
     * @brief Удаленный оператор копирующего присваивания
     */
    occupied_t& operator=(const occupied_t&) = delete;
    
    /**
     * @brief Оператор перемещающего присваивания
     * @param other Другой объект occupied_t
     * @return occupied_t& Ссылка на текущий объект
     */
    occupied_t& operator=(occupied_t&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }
};

/**
 * @struct occupied_first_t<Key, std::unique_ptr<T>>
 * @brief Специализация для occupied_first_t с уникальными указателями
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 */
template<typename Key, typename T>
struct occupied_first_t<Key, std::unique_ptr<T>> {
    std::pair<const Key, std::unique_ptr<T>> data_; ///< Пара ключ-значение с уникальным указателем
    
    /**
     * @brief Конструктор с параметрами
     * @param key Ключ
     * @param value Значение (уникальный указатель)
     */
    occupied_first_t(const Key& key, std::unique_ptr<T>&& value) : data_(key, std::move(value)) {}
    
    /**
     * @brief Удаленный конструктор копирования
     */
    occupied_first_t(const occupied_first_t&) = delete;
    
    /**
     * @brief Конструктор перемещения
     * @param other Другой объект occupied_first_t
     */
    occupied_first_t(occupied_first_t&& other) noexcept : data_(std::move(other.data_)) {}
    
    /**
     * @brief Удаленный оператор копирующего присваивания
     */
    occupied_first_t& operator=(const occupied_first_t&) = delete;
    
    /**
     * @brief Оператор перемещающего присваивания
     * @param other Другой объект occupied_first_t
     * @return occupied_first_t& Ссылка на текущий объект
     */
    occupied_first_t& operator=(occupied_first_t&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }
};

/**
 * @struct occupied_last_t<Key, std::unique_ptr<T>>
 * @brief Специализация для occupied_last_t с уникальными указателями
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 */
template<typename Key, typename T>
struct occupied_last_t<Key, std::unique_ptr<T>> {
    std::pair<const Key, std::unique_ptr<T>> data_; ///< Пара ключ-значение с уникальным указателем
    
    /**
     * @brief Конструктор с параметрами
     * @param key Ключ
     * @param value Значение (уникальный указатель)
     */
    occupied_last_t(const Key& key, std::unique_ptr<T>&& value) : data_(key, std::move(value)) {}
    
    /**
     * @brief Удаленный конструктор копирования
     */
    occupied_last_t(const occupied_last_t&) = delete;
    
    /**
     * @brief Конструктор перемещения
     * @param other Другой объект occupied_last_t
     */
    occupied_last_t(occupied_last_t&& other) noexcept : data_(std::move(other.data_)) {}
    
    /**
     * @brief Удаленный оператор копирующего присваивания
     */
    occupied_last_t& operator=(const occupied_last_t&) = delete;
    
    /**
     * @brief Оператор перемещающего присваивания
     * @param other Другой объект occupied_last_t
     * @return occupied_last_t& Ссылка на текущий объект
     */
    occupied_last_t& operator=(occupied_last_t&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }
};