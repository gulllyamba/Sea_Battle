#include "loader/Loader.hpp"
#include <fstream>

int main() {
    try {
        std::ofstream file("filename.txt");
        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл!" << std::endl;
            throw;
        }

        for (size_t i = 100; i <= 2000; i += 100) {
            std::cout << "\nКоличество кораблей: " << i << "\n";
            {
                ShipIDGenerator::reset();
                double dt = 0.1;
                Loader loader;
                size_t convoy_count = i, pirate_count = i;
                auto presenter = loader.create_presenter_test(convoy_count, pirate_count);
                for (size_t j = 0; j < convoy_count; ++j) {
                    presenter->purchase_ship("war_light");
                }
                presenter->auto_distribute_cargo();

                std::vector<ShipDTO> shoot_ships = presenter->get_attack_ships();
                for (size_t j = 0; j < shoot_ships.size(); ++j) {
                    presenter->install_weapon(shoot_ships[j].id, PlaceForWeapon::bow, "rocket_heavy");
                    presenter->install_weapon(shoot_ships[j].id, PlaceForWeapon::stern, "gun_medium");
                }

                presenter->set_pirate_strategy("closest");
                presenter->set_convoy_strategy("closest");

                presenter->start_convoy();
                while (!presenter->has_reached_destination()) {
                    presenter->move_convoy(dt);
                    size_t base_index = presenter->has_activated_base();
                    if (base_index != -1) {
                        presenter->stop_convoy();
                        presenter->start_pirates();
                        presenter->move_pirates(dt);
                        presenter->stop_pirates();

                        auto start = std::chrono::steady_clock::now();
                        while (presenter->count_alive_convoy_ships() != 0 && presenter->count_alive_pirate_ships() != 0) {
                            presenter->auto_combat_sequential();
                        }
                        auto end = std::chrono::steady_clock::now();
                        size_t total = duration_cast<std::chrono::microseconds>(end - start).count();

                        std::cout << "Время(один поток): " << total << "\n";
                        file << total << "\t";
                        
                        if (presenter->count_alive_convoy_ships() == 0) break;
                        else presenter->update_base_status(base_index);
                    }
                    presenter->start_convoy();
                }
                std::cout << "Живые корабли: " << presenter->count_alive_convoy_ships() << "\n";
                std::cout << "Живые пираты: " << presenter->count_alive_pirate_ships() << "\n";
            }

            {
                ShipIDGenerator::reset();
                double dt = 0.1;
                Loader loader;
                size_t convoy_count = i, pirate_count = i;
                auto presenter = loader.create_presenter_test(convoy_count, pirate_count);
                for (size_t j = 0; j < convoy_count; ++j) {
                    presenter->purchase_ship("war_light");
                }
                presenter->auto_distribute_cargo();

                std::vector<ShipDTO> shoot_ships = presenter->get_attack_ships();
                for (size_t j = 0; j < shoot_ships.size(); ++j) {
                    presenter->install_weapon(shoot_ships[j].id, PlaceForWeapon::bow, "rocket_heavy");
                    presenter->install_weapon(shoot_ships[j].id, PlaceForWeapon::stern, "gun_medium");
                }

                presenter->set_pirate_strategy("closest");
                presenter->set_convoy_strategy("closest");

                presenter->start_convoy();
                while (!presenter->has_reached_destination()) {
                    presenter->move_convoy(dt);
                    size_t base_index = presenter->has_activated_base();
                    if (base_index != -1) {
                        presenter->stop_convoy();
                        presenter->start_pirates();
                        presenter->move_pirates(dt);
                        presenter->stop_pirates();
                        
                        auto start = std::chrono::steady_clock::now();
                        while (presenter->count_alive_convoy_ships() != 0 && presenter->count_alive_pirate_ships() != 0) {
                            presenter->auto_combat_parallel();
                        }
                        auto end = std::chrono::steady_clock::now();
                        size_t total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                        std::cout << "Время(многопоток): " << total << "\n";
                        file << total << "\t";

                        if (presenter->count_alive_convoy_ships() == 0) break;
                        else presenter->update_base_status(base_index);
                    }
                    presenter->start_convoy();
                }
                std::cout << "Живые корабли: " << presenter->count_alive_convoy_ships() << "\n";
                std::cout << "Живые пираты: " << presenter->count_alive_pirate_ships() << "\n";
            }
            file << std::endl;
        }
        file.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
