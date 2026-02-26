/**
 * @file LookupTable.hpp
 * @brief Заголовочный файл, содержащий определение класса LookupTable
 */

#pragma once

#include <vector>
#include "TableIterator.hpp"
#include <concepts>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <memory>

/**
 * @class LookupTable
 * @brief Шаблонный класс(Просматриваемая таблица)
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 */
template <typename Key, typename T>
class LookupTable {
    private:
        std::vector<TableNode<Key, T>> array_; ///< Вектор узлов таблицы
        size_t size_ = 0; ///< Количество занятых элементов в таблице
        size_t n = 0; ///< Количество всех элементов в таблице

        /**
         * @brief Получает приоритет состояния ячейки для сортировки
         * @param index Индекс состояния в variant
         * @return size_t Приоритет состояния
         */
        size_t get_priority(size_t index) const {
            switch (index) {
                case 3: return 1; ///< occupied_first_t
                case 4: return 2; ///< occupied_t
                case 5: return 3; ///< occupied_last_t
                case 1: return 4; ///< empty_t
                case 2: return 5; ///< empty_last_t
            }
        }

        /**
         * @brief Находит индекс элемента по ключу
         * @param key Ключ для поиска
         * @return size_t Индекс элемента или n если не найден
         */
        size_t find_index(const Key& key) const {
            for (size_t i = 0; i < n; ++i) {
                switch (array_[i].index()) {
                    case 3: {
                        if (std::get<3>(array_[i]).data_.first == key) {
                            return i;
                        }
                        break;
                    }
                    case 4: {
                        if (std::get<4>(array_[i]).data_.first == key) {
                            return i;
                        }
                        break;
                    }
                    case 5: {
                        if (std::get<5>(array_[i]).data_.first == key) {
                            return i;
                        }
                        break;
                    }
                }
            }
            return n;
        }

        /**
         * @brief Выполняет сборку мусора (bucket collection)
         */
        void bucket_collection() {
            for (size_t i = 0; i < array_.size(); ++i) {
                for (size_t j = 0; j < array_.size() - i - 1; ++j) {
                    if (get_priority(array_[j].index()) > get_priority(array_[j + 1].index())) {
                        swap_variants(array_[j], array_[j + 1]);
                    }
                }
            }
            n = size_;
        }

    public:
        using key_type = Key; ///< Тип ключа
        using mapped_type = T; ///< Тип значения
        using value_type = std::pair<const Key, T>; ///< Тип элемента
        using reference = value_type&; ///< Тип ссылки на элемент
        using const_reference = const value_type&; ///< Тип константной ссылки на элемент
        using iterator = TableIterator<Key, T, false>; ///< Тип итератора
        using const_iterator = TableIterator<Key, T, true>; ///< Тип константного итератора
        using difference_type = ptrdiff_t; ///< Тип разницы итераторов
        using size_type = size_t; ///< Тип размера

        // void print() const {
        //     std::cout << "array_size: " << array_.size() << std::endl;
        //     std::cout << "size_: " << size_ << " " << "n : " << n << std::endl;
        //     std::cout << "array: ";
        //     for (size_t i = 0; i < array_.size(); ++i) {
        //         switch (array_[i].index()) {
        //             case 0: std::cout << "ef "; break;
        //             case 1: std::cout << "e "; break;
        //             case 2: std::cout << "el "; break;
        //             case 3: {
        //                 std::cout << "of("; 
        //                 occupied_first_t<Key, T> temp = std::get<3>(array_[i]);
        //                 std::cout << temp.data_.first << ", " << temp.data_.second << ") ";
        //                 break;
        //             }
        //             case 4: {
        //                 std::cout << "o("; 
        //                 occupied_t<Key, T> temp = std::get<4>(array_[i]);
        //                 std::cout << temp.data_.first << ", " << temp.data_.second << ") ";
        //                 break;
        //             }
        //             case 5: {
        //                 std::cout << "ol("; 
        //                 occupied_last_t<Key, T> temp = std::get<5>(array_[i]);
        //                 std::cout << temp.data_.first << ", " << temp.data_.second << ") ";
        //                 break;
        //             }
        //         }
        //     }
        //     std::cout << std::endl;
        // }

        /**
         * @brief Получает итератор на начало таблицы
         * @return iterator Итератор на первый элемент
         */
        iterator begin() noexcept {
            if (empty()) return end();
            return iterator(array_.data(), 0, array_.size());
        }
        
        /**
         * @brief Получает итератор на конец таблицы
         * @return iterator Итератор на позицию после последнего элемента
         */
        iterator end() noexcept {
            return iterator(array_.data() + array_.size(), array_.size(), 0);
        }

        /**
         * @brief Получает константный итератор на начало таблицы
         * @return const_iterator Константный итератор на первый элемент
         */
        const_iterator begin() const noexcept { 
            if (empty()) return cend();
            return const_iterator(array_.data(), 0, array_.size());
        }
        
        /**
         * @brief Получает константный итератор на конец таблицы
         * @return const_iterator Константный итератор на позицию после последнего элемента
         */
        const_iterator end() const noexcept { 
            return const_iterator(array_.data() + array_.size(), array_.size(), 0);
        }

        /**
         * @brief Получает константный итератор на начало таблицы
         * @return const_iterator Константный итератор на первый элемент
         */
        const_iterator cbegin() const noexcept { 
            if (empty()) return cend();
            return const_iterator(array_.data(), 0, array_.size());
        }
        
        /**
         * @brief Получает константный итератор на конец таблицы
         * @return const_iterator Константный итератор на позицию после последнего элемента
         */
        const_iterator cend() const noexcept { 
            return const_iterator(array_.data() + array_.size(), array_.size(), 0);
        }

        /**
         * @brief Конструктор по умолчанию
         */
        LookupTable() noexcept(std::is_nothrow_default_constructible_v<std::vector<TableNode<Key, T>>>) : array_(), size_(0), n(0) {}

        /**
         * @brief Конструктор копирования
         * @param other Другой объект LookupTable
         * @requires std::copy_constructible<Key> && std::copy_constructible<T>
         */
        LookupTable(const LookupTable& other) requires (std::copy_constructible<Key> && std::copy_constructible<T>) :LookupTable() {
            array_.reserve(other.array_.size());
            size_ = other.size_;
            n = other.n;

            for (size_t i = 0; i < other.array_.size(); ++i) {
                array_.push_back(other.array_[i]);
            }
        }

        /**
         * @brief Конструктор перемещения
         * @param other Другой объект LookupTable
         */
        LookupTable(LookupTable&& other) noexcept(std::is_nothrow_move_constructible_v<std::vector<TableNode<Key, T>>>) : LookupTable() {
            swap(other);
        }

        /**
         * @brief Конструктор из диапазона итераторов
         * @tparam It Тип итератора
         * @param first Начало диапазона
         * @param last Конец диапазона
         * @requires std::constructible_from<std::pair<const Key, T>, typename std::iterator_traits<It>::value_type>
         */
        template<std::input_iterator It>
        LookupTable(It first, It last) requires std::constructible_from<std::pair<const Key, T>, typename std::iterator_traits<It>::value_type> : LookupTable() {
            size_type count = 0;
            for (auto it = first; it != last; ++it) ++count;
            
            array_.reserve(count);
            for (; first != last; ++first) {
                insert(first->first, first->second);
            }
        }

        /**
         * @brief Конструктор из списка инициализации
         * @param il Список инициализации
         * @requires std::copy_constructible<Key> && std::copy_constructible<T>
         */
        LookupTable(std::initializer_list<value_type> il) requires (std::copy_constructible<Key> && std::copy_constructible<T>) : LookupTable() {
            array_.reserve(il.size());
            for (const auto& [key, value] : il) {
                insert(key, value);
            }
        }

        /**
         * @brief Деструктор
         */
        ~LookupTable() noexcept(std::is_nothrow_destructible_v<std::vector<TableNode<Key, T>>>) = default;

        /**
         * @brief Получает количество элементов в таблице
         * @return size_type Количество элементов
         */
        size_type size() const noexcept {
            return size_;
        }

        /**
         * @brief Получает максимально возможный размер таблицы
         * @return size_type Максимальный размер
         */
        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(TableNode<Key, T>);
        }

        /**
         * @brief Проверяет, пуста ли таблица
         * @return bool true если таблица пуста, false в противном случае
         */
        bool empty() const noexcept {
            return size_ == 0;
        }

        /**
         * @brief Очищает таблицу
         */
        void clear() noexcept {
            array_.clear();
            size_ = 0;
            n = 0;
        }

        /**
         * @brief Обменивает содержимое с другой таблицей
         * @param other Другая таблица
         */
        void swap(LookupTable& other) noexcept {
            array_.swap(other.array_);
            std::swap(size_, other.size_);
            std::swap(n, other.n);
        }

        /**
         * @brief Создает элемент на месте
         * @tparam Args Типы аргументов для создания значения
         * @param key Ключ элемента
         * @param args Аргументы для создания значения
         * @return std::pair<iterator, bool> Пара: итератор на элемент и флаг успешного создания
         * @requires std::constructible_from<T, Args...>
         */
        template <typename... Args>
        std::pair<iterator, bool> emplace(const Key& key, Args&&... args) requires std::constructible_from<T, Args...> {
            size_t index = find_index(key);
            if (index != n) return {iterator(&array_[index], index, array_.size() - index), false};

            if (array_.empty()) {
                array_.push_back(occupied_first_t<Key, T>(key, T(std::forward<Args>(args)...)));
            }
            else if (size_ == array_.size()) {
                if (size_ == 1) {
                    array_.push_back(occupied_last_t<Key, T>(key, T(std::forward<Args>(args)...)));
                }
                else {
                    occupied_last_t<Key, T> temp = std::get<5>(array_[size_ - 1]);
                    array_[size_ - 1].template emplace<occupied_t<Key, T>>(temp.data_.first, temp.data_.second);
                    array_.push_back(occupied_last_t<Key, T>(key, T(std::forward<Args>(args)...)));
                }
            }
            else if (n == array_.size()) {
                bucket_collection();

                if (n == 0) array_[n].template emplace<occupied_first_t<Key, T>>(key, T(std::forward<Args>(args)...));
                else if (n == 1) array_[n].template emplace<occupied_last_t<Key, T>>(key, T(std::forward<Args>(args)...));
                else {
                    occupied_last_t<Key, T> temp = std::get<5>(array_[n - 1]);
                    array_[n - 1].template emplace<occupied_t<Key, T>>(temp.data_.first, temp.data_.second);
                    array_[n].template emplace<occupied_last_t<Key, T>>(key, T(std::forward<Args>(args)...));
                }
            }
            else {
                if (size_ == 0) array_[n].template emplace<occupied_first_t<Key, T>>(key, T(std::forward<Args>(args)...));
                else if (size_ == 1) array_[n].template emplace<occupied_last_t<Key, T>>(key, T(std::forward<Args>(args)...));
                else {
                    int i = n;
                    while (array_[i].index() != 5) --i;
                    occupied_last_t<Key, T> temp = std::get<5>(array_[i]);
                    array_[i].template emplace<occupied_t<Key, T>>(temp.data_.first, temp.data_.second);
                    array_[n].template emplace<occupied_last_t<Key, T>>(key, T(std::forward<Args>(args)...));
                }
            }

            ++size_;
            ++n;
            return {iterator(&array_[n - 1], n - 1, array_.size() - (n - 1)), true};
        }

        /**
         * @brief Вставляет элемент (копирование)
         * @param value Элемент для вставки
         * @return std::pair<iterator, bool> Пара: итератор на элемент и флаг успешной вставки
         * @requires std::copy_constructible<Key> && std::copy_constructible<T>
         */
        std::pair<iterator, bool> insert(const value_type& value) requires (std::copy_constructible<Key> && std::copy_constructible<T>) {
            return emplace(value.first, value.second);
        }

        /**
         * @brief Вставляет элемент (перемещение)
         * @param value Элемент для вставки
         * @return std::pair<iterator, bool> Пара: итератор на элемент и флаг успешной вставки
         * @requires std::move_constructible<Key> && std::move_constructible<T>
         */
        std::pair<iterator, bool> insert(value_type&& value) requires (std::move_constructible<Key> && std::move_constructible<T>) {
            return emplace(std::move(value.first), std::move(value.second));
        }

        /**
         * @brief Вставляет элемент по ключу и значению (копирование)
         * @param key Ключ элемента
         * @param value Значение элемента
         * @return std::pair<iterator, bool> Пара: итератор на элемент и флаг успешной вставки
         * @requires std::copy_constructible<Key> && std::copy_constructible<T>
         */
        std::pair<iterator, bool> insert(const Key& key, const T& value) requires (std::copy_constructible<Key> && std::copy_constructible<T>) {
            return emplace(key, value);
        }

        /**
         * @brief Вставляет элемент по ключу и значению (перемещение)
         * @param key Ключ элемента
         * @param value Значение элемента
         * @return std::pair<iterator, bool> Пара: итератор на элемент и флаг успешной вставки
         * @requires std::move_constructible<Key> && std::move_constructible<T>
         */
        std::pair<iterator, bool> insert(Key&& key, T&& value) requires (std::move_constructible<Key> && std::move_constructible<T>) {
            return emplace(std::move(key), std::move(value));
        }

        /**
         * @brief Вставляет элементы из диапазона итераторов
         * @tparam It Тип итератора
         * @param first Начало диапазона
         * @param last Конец диапазона
         */
        template<std::input_iterator It>
        void insert(It first, It last) {
            LookupTable temp(*this);
            for (; first != last; ++first) {
                temp.insert(first->first, first->second);
            }
            swap(temp);
        }

        /**
         * @brief Вставляет элементы из списка инициализации
         * @param il Список инициализации
         * @requires std::copy_constructible<Key> && std::copy_constructible<T>
         */
        void insert(std::initializer_list<value_type> il) requires (std::copy_constructible<Key> && std::copy_constructible<T>) {
            LookupTable temp(*this);
            for (const auto& pair : il) {
                temp.insert(pair.first, pair.second);
            }
            swap(temp);
            // for (const auto& pair : il) {
            //     insert(pair.first, pair.second);
            // }
        }

        /**
         * @brief Удаляет элемент по ключу
         * @param key Ключ элемента для удаления
         * @return size_type Количество удаленных элементов (0 или 1)
         */
        size_type erase(const Key& key) {
            size_t index = find_index(key);
            if (index == n) return 0;

            switch (array_[index].index()) {
                case 3: {
                    for (size_t j = index + 1; j < n; ++j) {
                        if (array_[j].index() == 4) {
                            occupied_t<Key, T> temp = std::get<4>(array_[j]);
                            array_[j].template emplace<occupied_first_t<Key, T>>(temp.data_.first, temp.data_.second);
                            break;
                        }
                        if (array_[j].index() == 5) {
                            occupied_last_t<Key, T> temp = std::get<5>(array_[j]);
                            array_[j].template emplace<occupied_first_t<Key, T>>(temp.data_.first, temp.data_.second);
                            break;
                        }
                    }
                    break;
                }
                case 5: {
                    for (int j = index - 1; j >= 0; --j) {
                        if (array_[j].index() == 4) {
                            occupied_t<Key, T> temp = std::get<4>(array_[j]);
                            array_[j].template emplace<occupied_last_t<Key, T>>(temp.data_.first, temp.data_.second);
                            break;
                        }
                    }
                    break;
                }
            }

            if (size_ == array_.size()) array_[index].template emplace<empty_last_t>();
            else {
                array_[index].template emplace<empty_t>();
                for (int j = index - 1; j >= 0; --j) {
                    if (array_[j].index() == 2) {
                        array_[j].template emplace<empty_t>();
                        array_[index].template emplace<empty_last_t>();
                        break;
                    }
                }
            }

            --size_;
            return 1;
        }

        /**
         * @brief Удаляет элемент по итератору
         * @param p Итератор на элемент для удаления
         * @return iterator Итератор на следующий элемент
         */
        iterator erase(const_iterator p) noexcept {
            if (p == end() || empty()) return end();

            size_t index = p.node_ - array_.data();
            if (index >= n) return end();

            switch (array_[index].index()) {
                case 3: {
                    erase(std::get<3>(array_[index]).data_.first);
                    break;
                }
                case 4: {
                    erase(std::get<4>(array_[index]).data_.first);
                    break;
                }
                case 5: {
                    erase(std::get<5>(array_[index]).data_.first);
                    break;
                }
            }

            ++index;
            while (index < n && array_[index].index() < 3) {
                ++index;
            }
            return iterator(&array_[index], index, array_.size() - index);
        }

        /**
         * @brief Удаляет диапазон элементов
         * @param first Начало диапазона
         * @param last Конец диапазона
         * @return iterator Итератор на элемент после удаленного диапазона
         */
        iterator erase(const_iterator first, const_iterator last) noexcept {
            if (first == last) return iterator(const_cast<TableNode<Key, T>*>(last.node_), last.left_, last.right_);

            size_t start = first.node_ - array_.data();
            size_t finish = last.node_ - array_.data();
            if (start >= n || finish > n || start >= finish) return end();

            for (size_t i = start; i < finish; ++i) {
                if (array_[i].index() > 2) {
                    switch (array_[i].index()) {
                        case 3: {
                            erase(std::get<3>(array_[i]).data_.first);
                            break;
                        }
                        case 4: {
                            erase(std::get<4>(array_[i]).data_.first);
                            break;
                        }
                        case 5: {
                            erase(std::get<5>(array_[i]).data_.first);
                            break;
                        }
                    }
                }
            }

            return iterator(const_cast<TableNode<Key, T>*>(last.node_), last.left_, last.right_);
        }

        /**
         * @brief Считает количество элементов с заданным ключом
         * @param key Ключ для поиска
         * @return size_type Количество элементов (0 или 1)
         */
        size_type count(const Key& key) const {
            return find_index(key) != n ? 1 : 0;
        }

        /**
         * @brief Находит элемент по ключу
         * @param key Ключ для поиска
         * @return iterator Итератор на найденный элемент или end()
         */
        iterator find(const Key& key) {
            size_t index = find_index(key);
            return index != n ? iterator(&array_[index], index, array_.size() - index) : end();
        }

        /**
         * @brief Находит элемент по ключу (константная версия)
         * @param key Ключ для поиска
         * @return const_iterator Константный итератор на найденный элемент или end()
         */
        const_iterator find(const Key& key) const {
            size_t index = find_index(key);
            return index != n ? const_iterator(&array_[index], index, array_.size() - index) : end();
        }

        /**
         * @brief Проверяет наличие элемента с заданным ключом
         * @param key Ключ для проверки
         * @return bool true если элемент существует, false в противном случае
         */
        bool contains(const Key& key) const {
            return find_index(key) != n;
        }

        /**
         * @brief Оператор копирующего присваивания
         * @param other Другой объект LookupTable
         * @return LookupTable& Ссылка на текущий объект
         * @requires std::copy_constructible<Key> && std::copy_constructible<T>
         */
        LookupTable& operator=(const LookupTable& other) requires (std::copy_constructible<Key> && std::copy_constructible<T>) {
            if (this != &other) {
                clear();

                array_.reserve(other.array_.size());
                size_ = other.size_;
                n = other.n;

                for (size_t i = 0; i < other.array_.size(); ++i) {
                    array_.push_back(other.array_[i]);
            }
            }
            return *this;
        }

        /**
         * @brief Оператор перемещающего присваивания
         * @param other Другой объект LookupTable
         * @return LookupTable& Ссылка на текущий объект
         */
        LookupTable& operator=(LookupTable&& other) noexcept (std::is_nothrow_move_assignable_v<std::vector<TableNode<Key, T>>>) {
            if (this != &other) {
                array_ = std::move(other.array_);
                size_ = other.size_;
                n = other.n;
                other.size_ = 0;
                other.n = 0;
            }
            return *this;
        }

        /**
         * @brief Оператор присваивания из списка инициализации
         * @param il Список инициализации
         * @return LookupTable& Ссылка на текущий объект
         * @requires std::copy_constructible<Key> && std::copy_constructible<T>
         */
        LookupTable& operator=(std::initializer_list<value_type> il) requires (std::copy_constructible<Key> && std::copy_constructible<T>) {
            clear();
            insert(il);
            return *this;
        }

        /**
         * @brief Оператор сравнения на равенство
         * @param other Другой объект LookupTable
         * @return bool true если таблицы равны, false в противном случае
         */
        bool operator==(const LookupTable& other) const {
            if (size_ != other.size_) return false;

            for (size_t i = 0; i < n; ++i) {
                switch (array_[i].index()) {
                    case 3:{
                        occupied_first_t<Key, T> temp = std::get<3>(array_[i]);
                        auto it = other.find(temp.data_.first);
                        if (it == other.end() || it->second != temp.data_.second) return false;
                        break;
                    }
                    case 4: {
                        occupied_t<Key, T> temp = std::get<4>(array_[i]);
                        auto it = other.find(temp.data_.first);
                        if (it == other.end() || it->second != temp.data_.second) return false;
                        break;
                    }
                    case 5: {
                        occupied_last_t<Key, T> temp = std::get<5>(array_[i]);
                        auto it = other.find(temp.data_.first);
                        if (it == other.end() || it->second != temp.data_.second) return false;
                        break;
                    }
                }
            }
            return true;
        }

        /**
         * @brief Оператор доступа к элементу (создает элемент если не существует)
         * @param key Ключ элемента
         * @return T& Ссылка на значение элемента
         */
        T& operator[](const Key& key) {
            size_t index = find_index(key);
            if (index != n) {
                switch (array_[index].index()) {
                    case 3: {
                        return (std::get<3>(array_[index])).data_.second;
                    }
                    case 4: {
                        return (std::get<4>(array_[index])).data_.second;
                    }
                    case 5: {
                        return (std::get<5>(array_[index])).data_.second;
                    }
                }
            }
            
            auto [it, inserted] = emplace(key, T{});
            return it->second;
        }

        /**
         * @brief Оператор доступа к элементу с перемещением ключа (создает элемент если не существует)
         * @param key Ключ элемента
         * @return T& Ссылка на значение элемента
         */
        T& operator[](Key&& key) {
            size_t index = find_index(key);
            if (index != n) {
                switch (array_[index].index()) {
                    case 3: {
                        return (std::get<3>(array_[index])).data_.second;
                    }
                    case 4: {
                        return (std::get<4>(array_[index])).data_.second;
                    }
                    case 5: {
                        return (std::get<5>(array_[index])).data_.second;
                    }
                }
            }
            
            auto [it, inserted] = emplace(std::move(key), T{});
            return it->second;
        }

        /**
         * @brief Доступ к элементу с проверкой границ
         * @param key Ключ элемента
         * @return T& Ссылка на значение элемента
         * @throw std::out_of_range Если элемент не найден
         */
        T& at(const Key& key) {
            size_t index = find_index(key);
            if (index == n) throw std::out_of_range("Key not found");
            switch (array_[index].index()) {
                case 3: {
                    return (std::get<3>(array_[index])).data_.second;
                }
                case 4: {
                    return (std::get<4>(array_[index])).data_.second;
                }
                case 5: {
                    return (std::get<5>(array_[index])).data_.second;
                }
            }
        }

        /**
         * @brief Доступ к элементу с проверкой границ (константная версия)
         * @param key Ключ элемента
         * @return const T& Константная ссылка на значение элемента
         * @throw std::out_of_range Если элемент не найден
         */
        const T& at(const Key& key) const {
            size_t index = find_index(key);
            if (index == n) throw std::out_of_range("Key not found");
            switch (array_[index].index()) {
                case 3: {
                    return (std::get<3>(array_[index])).data_.second;
                }
                case 4: {
                    return (std::get<4>(array_[index])).data_.second;
                }
                case 5: {
                    return (std::get<5>(array_[index])).data_.second;
                }
            }
        }  
};



template <typename Key, typename T>
class LookupTable<Key, std::unique_ptr<T>> {
    private:
        std::vector<TableNode<Key, std::unique_ptr<T>>> array_;
        size_t size_ = 0;
        size_t n = 0;

        size_t get_priority(size_t index) const {
            switch (index) {
                case 3: return 1;
                case 4: return 2;
                case 5: return 3;
                case 1: return 4;
                case 2: return 5;
            }
        }

        size_t find_index(const Key& key) const {
            for (size_t i = 0; i < n; ++i) {
                switch (array_[i].index()) {
                    case 3: {
                        if (std::get<3>(array_[i]).data_.first == key) {
                            return i;
                        }
                        break;
                    }
                    case 4: {
                        if (std::get<4>(array_[i]).data_.first == key) {
                            return i;
                        }
                        break;
                    }
                    case 5: {
                        if (std::get<5>(array_[i]).data_.first == key) {
                            return i;
                        }
                        break;
                    }
                }
            }
            return n;
        }

        void bucket_collection() {
            for (size_t i = 0; i < array_.size(); ++i) {
                for (size_t j = 0; j < array_.size() - i - 1; ++j) {
                    if (get_priority(array_[j].index()) > get_priority(array_[j + 1].index())) {
                        swap_variants(array_[j], array_[j + 1]);
                    }
                }
            }
            n = size_;
        }

    public:
        using key_type = Key;
        using mapped_type = std::unique_ptr<T>;
        using value_type = std::pair<const Key, std::unique_ptr<T>>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = TableIterator<Key, std::unique_ptr<T>, false>;
        using const_iterator = TableIterator<Key, std::unique_ptr<T>, true>;
        using difference_type = ptrdiff_t;
        using size_type = size_t;

        // void print() const {
        //     std::cout << "array_size: " << array_.size() << std::endl;
        //     std::cout << "size_: " << size_ << " " << "n : " << n << std::endl;
        //     std::cout << "array: ";
        //     for (size_t i = 0; i < array_.size(); ++i) {
        //         switch (array_[i].index()) {
        //             case 0: std::cout << "ef "; break;
        //             case 1: std::cout << "e "; break;
        //             case 2: std::cout << "el "; break;
        //             case 3: {
        //                 std::cout << "of("; 
        //                 std::cout << (std::get<3>(array_[i])).data_.first << ", " << *((std::get<3>(array_[i])).data_.second) << ") ";
        //                 break;
        //             }
        //             case 4: {
        //                 std::cout << "o("; 
        //                 std::cout << (std::get<4>(array_[i])).data_.first << ", " << *((std::get<4>(array_[i])).data_.second) << ") ";
        //                 break;
        //             }
        //             case 5: {
        //                 std::cout << "ol("; 
        //                 std::cout << (std::get<5>(array_[i])).data_.first << ", " << *((std::get<5>(array_[i])).data_.second) << ") ";
        //                 break;
        //             }
        //         }
        //     }
        //     std::cout << std::endl;
        // }

        iterator begin() noexcept {
            if (empty()) return end();
            return iterator(array_.data(), 0, array_.size());
        }
        iterator end() noexcept {
            return iterator(array_.data() + array_.size(), array_.size(), 0);
        }

        const_iterator begin() const noexcept { 
            if (empty()) return cend();
            return const_iterator(array_.data(), 0, array_.size());
        }
        const_iterator end() const noexcept { 
            return const_iterator(array_.data() + array_.size(), array_.size(), 0);
        }

        const_iterator cbegin() const noexcept { 
            if (empty()) return cend();
            return const_iterator(array_.data(), 0, array_.size());
        }
        const_iterator cend() const noexcept { 
            return const_iterator(array_.data() + array_.size(), array_.size(), 0);
        }

        LookupTable() = default;

        LookupTable(const LookupTable& other) = delete;

        LookupTable(LookupTable&& other) noexcept : array_(std::move(other.array_)), size_(other.size_), n(other.n) {
            other.size_ = 0;
            other.n = 0;
        }

        template<std::input_iterator It>
        LookupTable(It first, It last) {
            for (; first != last; ++first) insert(std::move(*first));
        }

        ~LookupTable() = default;

        size_type size() const noexcept {
            return size_;
        }

        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(TableNode<Key, std::unique_ptr<T>>);
        }

        bool empty() const noexcept {
            return size_ == 0;
        }

        void clear() noexcept {
            array_.clear();
            size_ = 0;
            n = 0;
        }

        void swap(LookupTable& other) noexcept {
            array_.swap(other.array_);
            std::swap(size_, other.size_);
            std::swap(n, other.n);
        }

        template <typename... Args>
        std::pair<iterator, bool> emplace(const Key& key, Args&&... args)  {
            size_t index = find_index(key);
            if (index != n) return {iterator(&array_[index], index, array_.size() - index), false};

            std::unique_ptr<T> ptr;
            if constexpr (sizeof...(Args) == 1 && (std::is_same_v<std::decay_t<Args>..., std::unique_ptr<T>> || std::is_constructible_v<std::unique_ptr<T>, Args&&...>))
                ptr = std::unique_ptr<T>(std::forward<Args>(args)...);
            else ptr = std::make_unique<T>(std::forward<Args>(args)...);

            if (array_.empty()) {
                array_.push_back(occupied_first_t<Key, std::unique_ptr<T>>(key, std::move(ptr)));
            }
            else if (size_ == array_.size()) {
                if (size_ == 1) {
                    array_.push_back(occupied_last_t<Key, std::unique_ptr<T>>(key, std::move(ptr)));
                }
                else {
                    auto temp = std::move(std::get<5>(array_[size_ - 1]));
                    array_[size_ - 1].template emplace<occupied_t<Key, std::unique_ptr<T>>>(temp.data_.first, std::move(temp.data_.second));
                    array_.push_back(occupied_last_t<Key, std::unique_ptr<T>>(key, std::move(ptr)));
                }
            }
            else if (n == array_.size()) {
                bucket_collection();

                if (n == 0) array_[n].template emplace<occupied_first_t<Key, std::unique_ptr<T>>>(key, std::move(ptr));
                else if (n == 1) array_[n].template emplace<occupied_last_t<Key, std::unique_ptr<T>>>(key, std::move(ptr));
                else {
                    auto temp = std::move(std::get<5>(array_[n - 1]));
                    array_[n - 1].template emplace<occupied_t<Key, std::unique_ptr<T>>>(temp.data_.first, std::move(temp.data_.second));
                    array_[n].template emplace<occupied_last_t<Key, std::unique_ptr<T>>>(key, std::move(ptr));
                }
            }
            else {
                if (size_ == 0) array_[n].template emplace<occupied_first_t<Key, std::unique_ptr<T>>>(key, std::move(ptr));
                else if (size_ == 1) array_[n].template emplace<occupied_last_t<Key, std::unique_ptr<T>>>(key, std::move(ptr));
                else {
                    int i = n;
                    while (array_[i].index() != 5) --i;
                    auto temp = std::move(std::get<5>(array_[i]));
                    array_[i].template emplace<occupied_t<Key, std::unique_ptr<T>>>(temp.data_.first, std::move(temp.data_.second));
                    array_[n].template emplace<occupied_last_t<Key, std::unique_ptr<T>>>(key, std::move(ptr));
                }
            }

            ++size_;
            ++n;
            return {iterator(&array_[n - 1], n - 1, array_.size() - (n - 1)), true};
        }

        std::pair<iterator, bool> insert(value_type&& value) requires (std::move_constructible<Key>) {
            return emplace(std::move(value.first), std::move(value.second));
        }

        template <typename U = T>
        std::pair<iterator, bool> insert(const Key& key, std::unique_ptr<U>&& ptr) {
            return emplace(key, std::move(ptr));
        }

        template<std::input_iterator It>
        void insert(It first, It last) {
            for (; first != last; ++first) {
                insert(std::move(*first));
            }
        }

        size_type erase(const Key& key) {
            size_t index = find_index(key);
            if (index == n) return 0;

            switch (array_[index].index()) {
                case 3: {
                    for (size_t j = index + 1; j < n; ++j) {
                        if (array_[j].index() == 4) {
                            auto temp = std::move(std::get<4>(array_[j]));
                            array_[j].template emplace<occupied_first_t<Key, std::unique_ptr<T>>>(temp.data_.first, std::move(temp.data_.second));
                            break;
                        }
                        if (array_[j].index() == 5) {
                            auto temp = std::move(std::get<5>(array_[j]));
                            array_[j].template emplace<occupied_first_t<Key, std::unique_ptr<T>>>(temp.data_.first, std::move(temp.data_.second));
                            break;
                        }
                    }
                    break;
                }
                case 5: {
                    for (int j = index - 1; j >= 0; --j) {
                        if (array_[j].index() == 4) {
                            auto temp = std::move(std::get<4>(array_[j]));
                            array_[j].template emplace<occupied_last_t<Key, std::unique_ptr<T>>>(temp.data_.first, std::move(temp.data_.second));
                            break;
                        }
                    }
                    break;
                }
            }

            if (size_ == array_.size()) array_[index].template emplace<empty_last_t>();
            else {
                array_[index].template emplace<empty_t>();
                for (int j = index - 1; j >= 0; --j) {
                    if (array_[j].index() == 2) {
                        array_[j].template emplace<empty_t>();
                        array_[index].template emplace<empty_last_t>();
                        break;
                    }
                }
            }

            --size_;
            return 1;
        }

        iterator erase(const_iterator p) noexcept {
            if (p == end() || empty()) return end();

            size_t index = p.node_ - array_.data();
            if (index >= n) return end();

            switch (array_[index].index()) {
                case 3: {
                    erase(std::get<3>(array_[index]).data_.first);
                    break;
                }
                case 4: {
                    erase(std::get<4>(array_[index]).data_.first);
                    break;
                }
                case 5: {
                    erase(std::get<5>(array_[index]).data_.first);
                    break;
                }
            }

            ++index;
            while (index < n && array_[index].index() < 3) {
                ++index;
            }
            return iterator(&array_[index], index, array_.size() - index);
        }

        iterator erase(const_iterator first, const_iterator last) noexcept {
            if (first == last) return iterator(const_cast<TableNode<Key, std::unique_ptr<T>>*>(last.node_), last.left_, last.right_);

            size_t start = first.node_ - array_.data();
            size_t finish = last.node_ - array_.data();
            if (start >= n || finish > n || start >= finish) return end();

            for (size_t i = start; i < finish; ++i) {
                if (array_[i].index() > 2) {
                    switch (array_[i].index()) {
                        case 3: {
                            erase(std::get<3>(array_[i]).data_.first);
                            break;
                        }
                        case 4: {
                            erase(std::get<4>(array_[i]).data_.first);
                            break;
                        }
                        case 5: {
                            erase(std::get<5>(array_[i]).data_.first);
                            break;
                        }
                    }
                }
            }

            return iterator(const_cast<TableNode<Key, std::unique_ptr<T>>*>(last.node_), last.left_, last.right_);
        }

        size_type count(const Key& key) const {
            return find_index(key) != n ? 1 : 0;
        }

        iterator find(const Key& key) {
            size_t index = find_index(key);
            return index != n ? iterator(&array_[index], index, array_.size() - index) : end();
        }

        const_iterator find(const Key& key) const {
            size_t index = find_index(key);
            return index != n ? const_iterator(&array_[index], index, array_.size() - index) : end();
        }

        bool contains(const Key& key) const {
            return find_index(key) != n;
        }

        LookupTable& operator=(const LookupTable& other) = delete;

        LookupTable& operator=(LookupTable&& other) noexcept {
            if (this != &other) {
                array_ = std::move(other.array_);
                size_ = other.size_;
                n = other.n;
                other.size_ = 0;
                other.n = 0;
            }
            return *this;
        }

        bool operator==(const LookupTable& other) const {
            if (size_ != other.size_) return false;

            for (size_t i = 0; i < n; ++i) {
                if (array_[i].index() > 2) {
                    const std::unique_ptr<T>* this_ptr = nullptr;
                    const Key* this_key = nullptr;
                    
                    switch (array_[i].index()) {
                        case 3: 
                            this_ptr = &std::get<3>(array_[i]).data_.second;
                            this_key = &std::get<3>(array_[i]).data_.first;
                            break;
                        case 4: 
                            this_ptr = &std::get<4>(array_[i]).data_.second;
                            this_key = &std::get<4>(array_[i]).data_.first;
                            break;
                        case 5: 
                            this_ptr = &std::get<5>(array_[i]).data_.second;
                            this_key = &std::get<5>(array_[i]).data_.first;
                            break;
                    }
                    
                    if (!this_ptr) continue;
                    
                    auto it = other.find(*this_key);
                    if (it == other.end()) return false;
                    
                    const auto& other_ptr = it->second;
                    
                    if (!this_ptr && !other_ptr) continue;
                    if (!this_ptr || !other_ptr) return false;
                    if (**this_ptr != *other_ptr) return false;
                }
            }
            return true;
        }

        std::unique_ptr<T>& operator[](const Key& key) {
            size_t index = find_index(key);
            if (index != n) {
                switch (array_[index].index()) {
                    case 3: {
                        return (std::get<3>(array_[index])).data_.second;
                    }
                    case 4: {
                        return (std::get<4>(array_[index])).data_.second;
                    }
                    case 5: {
                        return (std::get<5>(array_[index])).data_.second;
                    }
                }
            }
            
            auto [it, inserted] = emplace(key, nullptr);
            return it->second;
        }

        std::unique_ptr<T>& operator[](Key&& key) {
            size_t index = find_index(key);
            if (index != n) {
                switch (array_[index].index()) {
                    case 3: {
                        return (std::get<3>(array_[index])).data_.second;
                    }
                    case 4: {
                        return (std::get<4>(array_[index])).data_.second;
                    }
                    case 5: {
                        return (std::get<5>(array_[index])).data_.second;
                    }
                }
            }
            
            auto [it, inserted] = emplace(std::move(key), nullptr);
            return it->second;
        }

        std::unique_ptr<T>& at(const Key& key) {
            size_t index = find_index(key);
            if (index == n) throw std::out_of_range("Key not found");
            switch (array_[index].index()) {
                case 3: {
                    return (std::get<3>(array_[index])).data_.second;
                }
                case 4: {
                    return (std::get<4>(array_[index])).data_.second;
                }
                case 5: {
                    return (std::get<5>(array_[index])).data_.second;
                }
            }
        }

        const std::unique_ptr<T>& at(const Key& key) const {
            size_t index = find_index(key);
            if (index == n) throw std::out_of_range("Key not found");
            switch (array_[index].index()) {
                case 3: {
                    return (std::get<3>(array_[index])).data_.second;
                }
                case 4: {
                    return (std::get<4>(array_[index])).data_.second;
                }
                case 5: {
                    return (std::get<5>(array_[index])).data_.second;
                }
            }
        }  
};