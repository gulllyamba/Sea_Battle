/**
 * @file IStateService.hpp
 * @brief Заголовочный файл, содержащий определение интерфейса IStateService
 */

#pragma once

#include <string>
#include <memory>

/**
 * @class IStateService
 * @brief Интерфейс сервиса для сохранения и загрузки состояния игры
 */
class IStateService {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~IStateService() = default;

        /**
         * @brief Сохраняет состояние игры
         * @param path Путь для сохранения
         * @return bool true если сохранение успешно, false в противном случае
         */
        virtual bool save(const std::string& path) = 0;
        
        /**
         * @brief Загружает состояние игры
         * @param path Путь для загрузки
         * @return bool true если загрузка успешна, false в противном случае
         */
        virtual bool load(const std::string& path) = 0;

        /**
         * @brief Загружает миссию
         * @param path Путь для загрузки
         * @return bool true если загрузка успешна, false в противном случае
         */
        virtual bool load_mission(const std::string& path) = 0;
};