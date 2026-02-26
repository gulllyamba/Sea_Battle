/**
 * @file TableIterator.hpp
 * @brief Заголовочный файл, содержащий определение класса итератора для LookupTable
 */

#pragma once

#include "TableNode.hpp"
#include <iterator>
#include <type_traits>

template<typename Key, typename T>
class LookupTable;

/**
 * @class TableIterator
 * @brief Итератор для LookupTable
 * @tparam Key Тип ключа
 * @tparam T Тип значения
 * @tparam IsConst Флаг константности итератора
 */
template<typename Key, typename T, bool IsConst>
class TableIterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag; ///< Категория итератора
        using value_type = std::pair<const Key, T>; ///< Тип значения
        using difference_type = std::ptrdiff_t; ///< Тип разницы
        using pointer = std::conditional_t<IsConst, const std::pair<const Key, T>, std::pair<const Key, T>>*; ///< Тип указателя
        using reference = std::conditional_t<IsConst, const std::pair<const Key, T>, std::pair<const Key, T>>&; ///< Тип ссылки

    private:
        friend class LookupTable<Key, T>;
        friend class TableIterator<Key, T, !IsConst>;

        using NodeType = std::conditional_t<IsConst, const TableNode<Key, T>, TableNode<Key, T>>*; ///< Тип узла
        NodeType node_; ///< Текущий узел
        size_t left_; ///< Количество элементов слева
        size_t right_; ///< Количество элементов справа

        /**
         * @brief Конструктор
         * @param node Указатель на узел
         * @param left Количество элементов слева
         * @param right Количество элементов справа
         */
        TableIterator(NodeType node, size_t left, size_t right) : node_(node), left_(left), right_(right) {
            skip_empty_forward();
        }

        /**
         * @brief Пропускает пустые ячейки при движении вперед
         */
        void skip_empty_forward() {
            while (right_ > 0 && node_->index() < 3) {
                ++node_;
                --right_;
                ++left_;
            }
            // while (node_->index() < 3) {
            //     ++node_;
            //     --size_;
            // }
        }

        /**
         * @brief Пропускает пустые ячейки при движении назад
         */
        void skip_empty_backward() {
            while (left_ > 0 && node_->index() < 3) {
                --node_;
                --left_;
                ++right_;
            }
            // while (node_->index() < 3) {
            //     --node_;
            // }
        }
    public:
        /**
         * @brief Конструктор по умолчанию
         */
        TableIterator() noexcept : node_(nullptr), left_(0), right_(0) {}

        /**
         * @brief Конструктор преобразования из другого итератора
         * @tparam OtherConst Флаг константности другого итератора
         * @param other Другой итератор
         */
        template<bool OtherConst>
        TableIterator(const TableIterator<Key, T, OtherConst>& other) noexcept requires (IsConst >= OtherConst) : node_(other.node_), left_(other.left_), right_(other.right_) {}

        /**
         * @brief Оператор присваивания из другого итератора
         * @tparam OtherConst Флаг константности другого итератора
         * @param other Другой итератор
         * @return TableIterator& Ссылка на текущий итератор
         */
        template<bool OtherConst>
        TableIterator& operator=(const TableIterator<Key, T, OtherConst>& other) noexcept requires (IsConst >= OtherConst) {
            node_ = other.node_;
            left_ = other.left_;
            right_ = other.right_;
            return *this;
        }

        /**
         * @brief Оператор разыменования
         * @return reference Ссылка на текущий элемент
         */
        reference operator*() const noexcept {
            switch (node_->index()) {
                case 3: {
                    return (std::get<3>(*node_)).data_;
                }
                case 4: {
                    return (std::get<4>(*node_)).data_;
                }
                case 5: {
                    return (std::get<5>(*node_)).data_;
                }
            }
        }

        /**
         * @brief Оператор доступа к члену
         * @return pointer Указатель на текущий элемент
         */
        pointer operator->() const noexcept {
            switch (node_->index()) {
                case 3: {
                    return &((std::get<3>(*node_)).data_);
                }
                case 4: {
                    return &((std::get<4>(*node_)).data_);
                }
                case 5: {
                    return &((std::get<5>(*node_)).data_);
                }
            }
        }

        /**
         * @brief Префиксный оператор инкремента
         * @return TableIterator& Ссылка на текущий итератор после инкремента
         */
        TableIterator& operator++() noexcept {
            ++node_;
            --right_;
            ++left_;
            skip_empty_forward();
            // if (node_->index() == 5) {
            //     ++node_;
            //     if (node_->index() < 3) {
            //         while (node_->index() != 2) ++node_;
            //         ++node_;
            //     }
            // }
            // else if (node_->index() > 2) {
            //     ++node_;
            //     skip_empty_forward();
            // }
            return *this;
        }
        
        /**
         * @brief Постфиксный оператор инкремента
         * @return TableIterator Итератор до инкремента
         */
        TableIterator operator++(int) noexcept {
            TableIterator res = *this;
            ++(*this);
            return res;
        }

        /**
         * @brief Префиксный оператор декремента
         * @return TableIterator& Ссылка на текущий итератор после декремента
         */
        TableIterator& operator--() noexcept {
            --node_;
            --left_;
            ++right_;
            skip_empty_backward();
            // if (node_->index() == 3) --node_;
            // else if (node_->index() > 3) {
            //     --node_;
            //     skip_empty_backward();
            // }
            return *this;
        }
        
        /**
         * @brief Постфиксный оператор декремента
         * @return TableIterator Итератор до декремента
         */
        TableIterator operator--(int) noexcept {
            TableIterator res = *this;
            --(*this);
            return res;
        }

        /**
         * @brief Оператор сравнения на равенство
         * @tparam OtherConst Флаг константности другого итератора
         * @param other Другой итератор
         * @return bool true если итераторы равны, false в противном случае
         */
        template<bool OtherConst>
        bool operator==(const TableIterator<Key, T, OtherConst>& other) const noexcept {
            return node_ == other.node_;
        }

        /**
         * @brief Оператор сравнения "меньше"
         * @tparam OtherConst Флаг константности другого итератора
         * @param other Другой итератор
         * @return bool true если текущий итератор меньше другого, false в противном случае
         */
        template<bool OtherConst>
        bool operator<(const TableIterator<Key, T, OtherConst>& other) const noexcept {
            return node_ < other.node_;
        }
        
        /**
         * @brief Оператор сравнения "больше"
         * @tparam OtherConst Флаг константности другого итератора
         * @param other Другой итератор
         * @return bool true если текущий итератор больше другого, false в противном случае
         */
        template<bool OtherConst>
        bool operator>(const TableIterator<Key, T, OtherConst>& other) const noexcept {
            return node_ > other.node_;
        }

        /**
         * @brief Оператор сравнения "меньше или равно"
         * @tparam OtherConst Флаг константности другого итератора
         * @param other Другой итератор
         * @return bool true если текущий итератор меньше или равен другому, false в противном случае
         */
        template<bool OtherConst>
        bool operator<=(const TableIterator<Key, T, OtherConst>& other) const noexcept {
            return node_ <= other.node_;
        }
        
        /**
         * @brief Оператор сравнения "больше или равно"
         * @tparam OtherConst Флаг константности другого итератора
         * @param other Другой итератор
         * @return bool true если текущий итератор больше или равен другому, false в противном случае
         */
        template<bool OtherConst>
        bool operator>=(const TableIterator<Key, T, OtherConst>& other) const noexcept {
            return node_ >= other.node_;
        }
};