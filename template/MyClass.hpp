#pragma once

#include <iostream>

class MyClass {
    private:
        int* data_;
        static inline size_t cnt = 0;
    public:
        MyClass() {
            data_ = new int[3];
            ++cnt;
            for (int i = 0; i < 3; ++i) {
                data_[i] = cnt * (i + 1);
            }
        }
        MyClass(const MyClass& other) {
            data_ = new int[3];
            for (int i = 0 ; i < 3; ++i) {
                data_[i] = other.data_[i];
            }
        }
        MyClass(MyClass&& other) {
            data_ = other.data_;
            other.data_ = nullptr;
        }

        const int* data() const {
            return data_;
        }

        MyClass& operator=(const MyClass& other) {
            if (this != &other) {
                for (int i = 0; i < 3; ++i) {
                    data_[i] = other.data_[i];
                }
            }
            return *this;
        }

        MyClass& operator=(MyClass&& other) noexcept {
            if (this != &other) {
                delete[] data_;
                data_ = nullptr;
                data_ = other.data_;
                other.data_ = nullptr;
            }
            return *this;
        }

        bool operator==(const MyClass& other) const {
            for (size_t i = 0; i < 3; ++i) {
                if (data_[i] != other.data_[i]) return false;
            }
            return true;
        }

        int& operator[](size_t index) {
            return data_[index];
        }

        const int& operator[](size_t index) const {
            return data_[index];
        }

        ~MyClass() {
            delete [] data_;
        }

        friend std::ostream& operator<<(std::ostream& os, const MyClass& my_class) {
            os << "MyClass(";
            for (size_t i = 0; i < 2; ++i) {
                os << my_class.data_[i] << ", ";
            }
            os << my_class.data_[2] << ")";
            return os;
        }
};