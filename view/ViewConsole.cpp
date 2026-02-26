#include "ViewConsole.hpp"

ViewConsole::ViewConsole(std::unique_ptr<Presenter> presenter) : presenter_(std::move(presenter)) {}

void process_error(std::istream& in, const std::string& error) {
    if (in.eof()) {
        throw std::runtime_error("EOF");
    }
    if (in.bad()) {
        throw std::runtime_error("Corrupted input stream");
    }
    if (in.fail()) {
        std::cout << error << std::endl;
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void ViewConsole::save_or_new_game() {
    std::cout << "{ИГРА}\n";
    std::cout << "-----------------Выберите------------------\n";
    std::cout << "\t1) Новая игра\n";
    std::cout << "\t2) Загрузить игру(последняя загруженная)\n";
    std::cout << "\t0) Выход\n";

    size_t choice;
    std::cin >> choice;
    std::string error = "Неправильный формат. Введите значение от 0 до 2";
    if (choice > 2) std::cin.setstate(std::ios::failbit);

    while (!std::cin.good()) {
        try {
            process_error(std::cin, error);
        }
        catch (...) {
            throw;
        }
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        if (choice > 2) std::cin.setstate(std::ios::failbit);
    }

    switch (choice) {
        case 0: {
            break;
        }
        case 1: {
            std::cout << presenter_->get_pirate_bases().size() << "\n";
            return;
        }
        case 2: {
            // presenter_->load_game("/home/ilya/OOP/twenty_thread_atomic/laba3/view/saved_game.yaml");
            presenter_->load_game("saved_game.yaml");
            auto ships = presenter_->get_convoy_ships();
            std::string max_char = "A";
            for (const auto& ship : ships) {
                if (max_char < ship.id) max_char = ship.id;
            }

            size_t index = 0;
            for (char c : max_char) {
                if (!std::isalpha(c)) throw std::invalid_argument("Invalid ID format");
                size_t digit = std::toupper(c) - 'A';
                index = index * 26 + digit;
            }
            ShipIDGenerator::set_convoy_counter(index + 1);
            std::cout << "\n";
            break;
        }
    }

}

void ViewConsole::mission_info() {
    std::cout << "{ИНФОРМАЦИЯ}\n";
    MissionDTO mission = presenter_->get_mission();
    std::cout << "------------------Миссия-------------------\n";
    std::cout << "\tБюджет: " << mission.current_budget << " Р\n";
    std::cout << "\tВесь груз(Загруженный): " << mission.total_cargo << "(" << mission.current_cargo << ")\n";
    std::cout << "\tПроцент груза, который необходимо доставить: " << mission.required_cargo_percentage << "\n";
    std::cout << "\tМакс кол-во кораблей конвоя: " << mission.max_convoy_ships << "\n";
    std::cout << "\tМакс кол-во кораблей пиратов: " << mission.max_pirate_ships << "\n";
    std::cout << "\tБаза A: [" << mission.base_a.x << ", " << mission.base_a.y << "]\n";
    std::cout << "\tБаза B: [" << mission.base_b.x << ", " << mission.base_b.y << "]\n";
    std::cout << "\tБазы пиратов: ";
    std::vector<PirateBaseDTO> pirate_bases = mission.pirate_bases;
    for (size_t i = 0; i < pirate_bases.size(); ++i) {
        std::cout << "[" << pirate_bases[i].position.x << ", " << pirate_bases[i].position.y << "] ";
    }
    std::cout << "\n";
    std::cout << "-------------------------------------------\n";
}

void ViewConsole::purchase_ships() {
    std::cout << "{ЗАКУПКА КОРАБЛЕЙ}\n";
    size_t available_ships_cnt = presenter_->get_mission().max_convoy_ships - presenter_->count_alive_convoy_ships();
    std::vector<ShipTemplate> templates = presenter_->get_available_ships();
    LookupTable<std::string, size_t> shop_cart;
    std::vector<ShipDTO> ships = presenter_->get_convoy_ships();
    for (const auto& ship_dto : ships) {
        for (const auto& temp : templates) {
            if (temp.display_name == ship_dto.name) ++shop_cart[temp.id];
        }
    }
    while (true) {
        std::cout << "------------------Корзина-------------------\n";
        ships = presenter_->get_convoy_ships();
        for (const auto& temp : templates) {
            if (shop_cart[temp.id] > 0) {
                std::cout << "\t" << temp.id << ": " << shop_cart[temp.id] << "\n";
            }
        }
        if (available_ships_cnt == presenter_->get_mission().max_convoy_ships) std::cout << "\tПусто\n";
        std::cout << "--------------Каталог кораблей--------------\n";
        std::cout << "[Бюджет: " << presenter_->get_current_budget() << " Р, Кол-во доступных кораблей: " << available_ships_cnt << ", Весь груз: " << presenter_->get_remaining_cargo() << "]\n";
        for (size_t i = 0; i < templates.size(); ++i) {
            std::cout << "\t" << templates[i].id << ": " << templates[i].get_description() << "\n";
        }
        std::cout << "1) Купить\n";
        std::cout << "2) Продать\n";
        std::cout << "3) Далее\n";
        std::cout << "0) Загрузить игру\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "Выберите действие\n";
        std::cout << "--------------------------------------------\n";

        size_t choice;
        std::cin >> choice;
        std::string error = "Неправильный формат. Введите значение от 0 до 3";
        if (choice > 3) std::cin.setstate(std::ios::failbit);

        while (!std::cin.good()) {
            try {
                process_error(std::cin, error);
            }
            catch (...) {
                throw;
            }
            std::cout << "Выберите действие: ";
            std::cin >> choice;
            if (choice > 3) std::cin.setstate(std::ios::failbit);
        }

        switch (choice) {
            case 1: {
                if (available_ships_cnt <= 0) {
                    std::cout << "Ошибка! Уже максимальное количество кораблей...\n";
                    break;
                }
                while (true) {
                    std::cout << "Введите наименование корабля: ";
                    std::string id;
                    std::cin >> id;
                    bool contain = false, can_buy = false;
                    for (const auto& temp : templates) {
                        if (temp.id == id) {
                            contain = true;
                            if (presenter_->purchase_ship(id)) {
                                can_buy = true;
                                ++shop_cart[id];
                                --available_ships_cnt;
                            }
                            break;
                        }
                    }
                    if (!contain) std::cout << "Ошибка! Такого наименования корабля нет...\n";
                    else if (!can_buy) std::cout << "Ошибка! Недостаточно средств...\n";
                    else break;
                }
                std::cout << "Отлично! Корабль куплен\n";
                break;
            }
            case 2: {
                if (available_ships_cnt == presenter_->get_mission().max_convoy_ships) {
                    std::cout << "Ошибка! Пустая корзина...\n";
                    break;
                }
                while (true) {
                    std::cout << "Введите наименование корабля: ";
                    std::string id;
                    std::cin >> id;
                    bool contain = false, can_sell = false;
                    for (const auto& temp : templates) {
                        if (temp.id == id) {
                            contain = true;
                            if (shop_cart[id] > 0) {
                                std::vector<ShipDTO> cargo_ships = presenter_->get_cargo_ships();
                                std::string ship_id = "";
                                for (const auto& ship : cargo_ships) {
                                    if (ship.name == temp.display_name) {
                                        ship_id = ship.id;
                                        break;
                                    }
                                }
                                double cargo = presenter_->get_ship_current_cargo(ship_id);
                                presenter_->unload_cargo(ship_id, cargo);
                                if (presenter_->sell_ship(id)) {
                                    can_sell = true;
                                    --shop_cart[id];
                                    ++available_ships_cnt;
                                }
                            }
                            break;
                        }
                    }
                    if (!contain) std::cout << "Ошибка! Такого наименования корабля нет...\n";
                    else if (!can_sell) std::cout << "Ошибка! Нет кораблей этого наименования\n";
                    else break;
                }
                std::cout << "Отлично! Корабль продан\n";
                break;
            }
            case 3: {
                std::vector<ShipDTO> cargo_ships = presenter_->get_cargo_ships();
                double cargo_capacity = 0.0;
                for (const auto& ship : cargo_ships) cargo_capacity += (ship.max_cargo - ship.current_cargo);
                if (cargo_capacity > presenter_->get_remaining_cargo() || std::abs(cargo_capacity - presenter_->get_remaining_cargo()) < 1e-9) return;
                else {
                    std::cout << "Ошибка! Не получится разместить весь груз по кораблям...\n";
                    break;
                }
            }
            case 0: {
                // presenter_->save_game("/home/ilya/OOP/twenty_thread_atomic/laba3/view/saved_game.yaml");
                presenter_->save_game("saved_game.yaml");
                break;
            }
        }
    }
}

void ViewConsole::load_ships() {
    std::cout << "{ЗАГРУЗКА КОРАБЛЕЙ}\n";
    while (true) {
        std::vector<ShipDTO> cargo_ships = presenter_->get_cargo_ships();
        std::cout << "-------------Все грузовые корабли-----------\n";
        if (std::abs(presenter_->get_remaining_cargo()) < 1e-9)
            std::cout << "[Оставшийся груз: " << 0.0 << "]\n";
        else std::cout << "[Оставшийся груз: " << presenter_->get_remaining_cargo() << "]\n";
        std::vector<ShipTemplate> templates = presenter_->get_available_ships();
        size_t i = 1;
        for (const auto& ship_dto : cargo_ships) {
            for (const auto& temp : templates) {
                if (temp.display_name == ship_dto.name) std::cout << "\t" << i << ") " << temp.id << ": " << ship_dto.current_cargo << "/" << ship_dto.max_cargo << "\n";
            }
            ++i;
        }
        std::cout << "1) Автоматически загрузить весь груз\n";
        std::cout << "2) Загрузить корабль\n";
        std::cout << "3) Разгрузить корабль\n";
        std::cout << "4) Далее\n";
        std::cout << "0) Загрузить игру\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "Выберите действие\n";
        std::cout << "--------------------------------------------\n";

        size_t choice;
        std::cin >> choice;
        std::string error = "Неправильный формат. Введите значение от 0 до 4";
        if (choice > 4) std::cin.setstate(std::ios::failbit);

        while (!std::cin.good()) {
            try {
                process_error(std::cin, error);
            }
            catch (...) {
                throw;
            }
            std::cout << "Выберите действие: ";
            std::cin >> choice;
            if (choice > 4) std::cin.setstate(std::ios::failbit);
        }

        switch (choice) {
            case 1: {
                presenter_->auto_distribute_cargo();
                break;
            }
            case 2: {
                if (presenter_->get_remaining_cargo() < 1e-9) {
                    std::cout << "Весь груз загружен\n";
                    break;
                }
                size_t size = cargo_ships.size();
                std::cout << "Выберите корабль(индекс): ";
                size_t ship_load_choice;
                std::cin >> ship_load_choice;
                std::string error = "Неправильный формат. Введите значение от 1 до " + size;
                if (ship_load_choice < 1 || ship_load_choice > size) std::cin.setstate(std::ios::failbit);

                while (!std::cin.good()) {
                    try {
                        process_error(std::cin, error);
                    }
                    catch (...) {
                        throw;
                    }
                    std::cout << "Выберите корабль(индекс): ";
                    std::cin >> ship_load_choice;
                    if (ship_load_choice < 1 || ship_load_choice > size) std::cin.setstate(std::ios::failbit);
                }

                double cargo = 0.0, max_cargo = cargo_ships[ship_load_choice - 1].max_cargo;
                std::cout << "Введите массу груза: ";
                std::cin >> cargo;
                error = "Неправильный формат. Введите значение от 0.0 до " + std::to_string(std::min(max_cargo, presenter_->get_remaining_cargo()));
                if (cargo <= 0.0 || cargo > max_cargo || cargo > presenter_->get_remaining_cargo()) std::cin.setstate(std::ios::failbit);

                while (!std::cin.good()) {
                    try {
                        process_error(std::cin, error);
                    }
                    catch (...) {
                        throw;
                    }
                    std::cout << "Введите массу груза: ";
                    std::cin >> cargo;
                    if (cargo <= 0.0 || cargo > max_cargo) std::cin.setstate(std::ios::failbit);
                }

                if (presenter_->load_cargo(cargo_ships[ship_load_choice - 1].id, cargo))
                    std::cout << "Отлично! Груз загружен\n";
                else std::cout << "Ошибка! Что-то пошло не так...\n";
                break;
            }
            case 3: {
                if (std::abs(presenter_->get_remaining_cargo() - presenter_->get_total_cargo()) < 1e-9) {
                    std::cout << "Нет груза на кораблях\n";
                    break;
                }
                size_t size = cargo_ships.size();
                std::cout << "Выберите корабль(индекс): ";
                size_t ship_load_choice;
                std::cin >> ship_load_choice;
                std::string error = "Неправильный формат. Введите значение от 1 до " + std::to_string(size) + "\nНельзя разгрузить корабль без груза.";
                if (ship_load_choice < 1 || ship_load_choice > size || cargo_ships[ship_load_choice - 1].current_cargo <= 0.0) std::cin.setstate(std::ios::failbit);

                while (!std::cin.good()) {
                    try {
                        process_error(std::cin, error);
                    }
                    catch (...) {
                        throw;
                    }
                    std::cout << "Выберите корабль(индекс): ";
                    std::cin >> ship_load_choice;
                    if (ship_load_choice < 1 || ship_load_choice > size || cargo_ships[ship_load_choice - 1].current_cargo <= 0.0) std::cin.setstate(std::ios::failbit);
                }

                double cargo = 0.0, current_cargo = cargo_ships[ship_load_choice - 1].current_cargo;
                std::cout << "Введите массу груза: ";
                std::cin >> cargo;
                error = "Неправильный формат. Введите значение от 0.0 до " + std::to_string(current_cargo);
                if (cargo <= 0.0 || cargo > current_cargo) std::cin.setstate(std::ios::failbit);

                while (!std::cin.good()) {
                    try {
                        process_error(std::cin, error);
                    }
                    catch (...) {
                        throw;
                    }
                    std::cout << "Введите массу груза: ";
                    std::cin >> cargo;
                    if (cargo <= 0.0 || cargo > current_cargo) std::cin.setstate(std::ios::failbit);
                }

                if (presenter_->unload_cargo(cargo_ships[ship_load_choice - 1].id, cargo))
                    std::cout << "Отлично! Корабль разгружен\n";
                else std::cout << "Ошибка! Что-то пошло не так...\n";
                break;
            }
            case 4: {
                if (presenter_->get_remaining_cargo() < 1e-9) return;
                else {
                    std::cout << "Ошибка! Не весь груз размещен...\n";
                    break;
                }
            }
            case 0: {
                presenter_->save_game("/home/ilya/OOP/twenty_thread_atomic/laba3/view/saved_game.yaml");
                // presenter_->save_game("saved_game.yaml");
                break;
            }
        }
    }
}
void ViewConsole::purchase_weapons() {
    std::cout << "{ЗАКУПКА ОРУЖИЯ}\n";
    std::vector<WeaponTemplate> templates = presenter_->get_available_weapons();
    std::vector<ShipTemplate> ship_templates = presenter_->get_available_ships();
    while (true) {
        std::vector<ShipDTO> shoot_ships = presenter_->get_attack_ships();
        std::cout << "-------------Все корабли атаки--------------\n";
        size_t i = 1;
        for (const auto& ship_dto : shoot_ships) {
            for (const auto& temp : ship_templates) {
                if (temp.display_name == ship_dto.name) {
                    std::cout << "\t" << i << ") " << temp.id << ": ";
                    if (ship_dto.weapons.contains(PlaceForWeapon::bow)) {
                        std::cout << "bow[" << ship_dto.weapons.at(PlaceForWeapon::bow).name << "] ";
                    }
                    if (ship_dto.weapons.contains(PlaceForWeapon::port)) {
                        std::cout << "port[" << ship_dto.weapons.at(PlaceForWeapon::port).name << "] ";
                    }
                    if (ship_dto.weapons.contains(PlaceForWeapon::starboard)) {
                        std::cout << "starboard[" << ship_dto.weapons.at(PlaceForWeapon::starboard).name << "] ";
                    }
                    if (ship_dto.weapons.contains(PlaceForWeapon::stern)) {
                        std::cout << "stern[" << ship_dto.weapons.at(PlaceForWeapon::stern).name << "] ";
                    }
                }
            }
            std::cout << "\n";
            ++i;
        }
        if (shoot_ships.size() == 0) {
            std::cout << "\tПусто\n";
            break;
        }
        std::cout << "--------------Каталог оружия--------------\n";
        std::cout << "[Бюджет: " << presenter_->get_current_budget() << " Р]\n";
        for (size_t i = 0; i < templates.size(); ++i) {
            std::cout << "\t" << templates[i].id << ": " << templates[i].get_description() << "\n";
        }
        std::cout << "1) Купить и установить\n";
        std::cout << "2) Продать\n";
        std::cout << "3) Далее\n";
        std::cout << "0) Загрузить игру\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "Выберите действие\n";
        std::cout << "--------------------------------------------\n";

        size_t choice;
        std::cin >> choice;
        std::string error = "Неправильный формат. Введите значение от 0 до 3";
        if (choice > 3) std::cin.setstate(std::ios::failbit);

        while (!std::cin.good()) {
            try {
                process_error(std::cin, error);
            }
            catch (...) {
                throw;
            }
            std::cout << "Выберите действие: ";
            std::cin >> choice;
            if (choice > 3) std::cin.setstate(std::ios::failbit);
        }

        switch (choice) {
            case 1: {
                if (presenter_->get_current_budget() < presenter_->get_min_weapon_cost()) {
                    std::cout << "Ошибка! Недостаточно средств...\n";
                    break;
                }
                if (!presenter_->has_free_place()) {
                    std::cout << "Ошибка! Нет свободных мест для оружий...\n";
                    break;
                }

                WeaponTemplate weapon;
                while (true) {
                    std::cout << "Введите наименование оружия: ";
                    std::string id;
                    std::cin >> id;
                    bool contain = false, can_buy = false;
                    for (const auto& temp : templates) {
                        if (temp.id == id) {
                            contain = true;
                            if (presenter_->can_spend(temp.cost)) {
                                weapon = temp;
                                can_buy = true;
                            }
                            break;
                        }
                    }
                    if (!contain) std::cout << "Ошибка! Такого наименования оружия нет...\n";
                    else if (!can_buy) std::cout << "Ошибка! Недостаточно средств...\n";
                    else break;
                }
                std::cout << "Отлично! Оружие куплено\n";

                size_t ship_choice = 0;
                while (true) {
                    std::cout << "Выберите корабль для установки оружия: ";
                    std::cin >> ship_choice;
                    std::string error = "Неправильный формат. Введите значение от 1 до " + std::to_string(shoot_ships.size());
                    if (ship_choice < 1 || ship_choice > shoot_ships.size()) std::cin.setstate(std::ios::failbit);

                    while (!std::cin.good()) {
                        try {
                            process_error(std::cin, error);
                        }
                        catch (...) {
                            throw;
                        }
                        std::cout << "Выберите корабль для установки оружия: ";
                        std::cin >> ship_choice;
                        if (ship_choice < 1 || ship_choice > shoot_ships.size()) std::cin.setstate(std::ios::failbit);
                    }

                    LookupTable<PlaceForWeapon, WeaponDTO> weapons = shoot_ships[ship_choice - 1].weapons;
                    if (weapons.contains(PlaceForWeapon::bow) && weapons.contains(PlaceForWeapon::port) && weapons.contains(PlaceForWeapon::starboard) && weapons.contains(PlaceForWeapon::stern)) {
                        std::cout << "Ошибка! На корабле нет свободных мест для оружия...\n";
                    }
                    else break;
                }

                PlaceForWeapon place_for_weapon = PlaceForWeapon::bow;
                while (true) {
                    std::cout << "Введите место для оружия: ";
                    std::string place;
                    std::cin >> place;

                    if (place == "bow" || place == "stern" || place == "starboard" || place == "port") {
                        place_for_weapon = PlaceForWeapon::bow;
                        if (place == "bow") place_for_weapon = PlaceForWeapon::bow;
                        else if (place == "stern") place_for_weapon = PlaceForWeapon::stern;
                        else if (place == "starboard") place_for_weapon = PlaceForWeapon::starboard;
                        else place_for_weapon = PlaceForWeapon::port;
                        if (shoot_ships[ship_choice - 1].weapons.contains(place_for_weapon)) {
                            std::cout << "Ошибка! На этом месте есть оружие...\n";
                        }
                        else break;
                    }
                    else std::cout << "Неправильный формат. Введите название места\n";
                }
                presenter_->install_weapon(shoot_ships[ship_choice - 1].id, place_for_weapon, weapon.id);
                break;
            }
            case 2: {
                if (!presenter_->has_occupied_place()) {
                    std::cout << "Ошибка! Нет мест с оружием...\n";
                    break;
                }

                size_t ship_choice = 0;
                while (true) {
                    std::cout << "Выберите корабль для продажи оружия: ";
                    std::cin >> ship_choice;
                    std::string error = "Неправильный формат. Введите значение от 1 до " + std::to_string(shoot_ships.size());
                    if (ship_choice < 1 || ship_choice > shoot_ships.size()) std::cin.setstate(std::ios::failbit);

                    while (!std::cin.good()) {
                        try {
                            process_error(std::cin, error);
                        }
                        catch (...) {
                            throw;
                        }
                        std::cout << "Выберите корабль для продажи оружия: ";
                        std::cin >> ship_choice;
                        if (ship_choice < 1 || ship_choice > shoot_ships.size()) std::cin.setstate(std::ios::failbit);
                    }

                    LookupTable<PlaceForWeapon, WeaponDTO> weapons = shoot_ships[ship_choice - 1].weapons;
                    if (!weapons.contains(PlaceForWeapon::bow) && !weapons.contains(PlaceForWeapon::port) && !weapons.contains(PlaceForWeapon::starboard) && !weapons.contains(PlaceForWeapon::stern)) {
                        std::cout << "Ошибка! На корабле нет мест с оружием...\n";
                    }
                    else break;
                }

                PlaceForWeapon place_for_weapon = PlaceForWeapon::bow;
                while (true) {
                    std::cout << "Введите место оружия для продажи: ";
                    std::string place;
                    std::cin >> place;

                    if (place == "bow" || place == "stern" || place == "starboard" || place == "port") {
                        place_for_weapon = PlaceForWeapon::bow;
                        if (place == "bow") place_for_weapon = PlaceForWeapon::bow;
                        else if (place == "stern") place_for_weapon = PlaceForWeapon::stern;
                        else if (place == "starboard") place_for_weapon = PlaceForWeapon::starboard;
                        else place_for_weapon = PlaceForWeapon::port;
                        if (!shoot_ships[ship_choice - 1].weapons.contains(place_for_weapon)) {
                            std::cout << "Ошибка! На этом месте нет оружия...\n";
                        }
                        else break;
                    }
                    else std::cout << "Неправильный формат. Введите название места\n";
                }
                presenter_->sell_weapon(shoot_ships[ship_choice - 1].id, place_for_weapon);

                break;
            }
            case 3: {
                return;
            }
            case 0: {
                presenter_->save_game("/home/ilya/OOP/twenty_thread_atomic/laba3/view/saved_game.yaml");
                // presenter_->save_game("saved_game.yaml");
                break;
            }
        }
    }
}

void ViewConsole::mission_sequential() {
    double dt = 0.1;
    std::cout << "{МИССИЯ}\n";
    presenter_->start_convoy();
    while (!presenter_->has_reached_destination()) {
        std::cout << "\nКонвой:" << presenter_->convoy_info();
        presenter_->move_convoy(dt);
        size_t base_index = presenter_->has_activated_base();
        if (base_index != -1) {
            std::cout << "\n-----------База " << base_index << " активирована----------\n";
            presenter_->stop_convoy();
            presenter_->start_pirates();
            presenter_->move_pirates(dt);
            presenter_->stop_pirates();
            std::cout << "\n-----------Пираты напали на конвой----------\n";
            
            while (true) {
                std::cout << "Введите стратегию для конвоя(random, closest, weakest, strongest): ";
                std::string strategy;
                std::cin >> strategy;

                if (strategy == "random" || strategy == "closest" || strategy == "strongest" || strategy == "weakest") {
                    presenter_->set_convoy_strategy(strategy);
                    break;
                }
                else {
                    std::cout << "Неправильный ввод. Введите название стратегии\n";
                }
            }
            while (true) {
                std::cout << "Введите стратегию для пиратов(random, closest, weakest, strongest): ";
                std::string strategy;
                std::cin >> strategy;

                if (strategy == "random" || strategy == "closest" || strategy == "strongest" || strategy == "weakest") {
                    presenter_->set_pirate_strategy(strategy);
                    break;
                }
                else {
                    std::cout << "Неправильный ввод. Введите название стратегии\n";
                }
            }

            while (presenter_->count_alive_convoy_ships() != 0 && presenter_->count_alive_pirate_ships() != 0) {
                presenter_->auto_combat_sequential();
                std::cout << "\nКонвой:" << presenter_->convoy_info();
                std::cout << "\nПираты:" << presenter_->pirate_info();
            }

            if (presenter_->count_alive_convoy_ships() == 0) break;
            else {
                presenter_->update_base_status(base_index);
            }


            std::cout << "\n-------------База "<< base_index << " повержена------------\n";
        }
        presenter_->start_convoy();
    }
    if (presenter_->has_reached_destination()) {
        std::cout << "\n\nПоздравляю, конвой достиг пункта назначения!\n";
        if (presenter_->mission_completed()) {
            std::cout << "Миссия выполнена! Доставилось требуемое кол-во груза\n\n";
        }
        else std::cout << "\n\nНеудача, миссия провалена(\n\n";
    }
    else std::cout << "\n\nНеудача, миссия провалена(\n\n";
}

void ViewConsole::mission_parallel() {
    double dt = 0.1;
    std::cout << "{МИССИЯ}\n";
    presenter_->start_convoy();
    while (!presenter_->has_reached_destination()) {
        std::cout << "\nКонвой:" << presenter_->convoy_info();
        presenter_->move_convoy(dt);
        size_t base_index = presenter_->has_activated_base();
        if (base_index != -1) {
            std::cout << "\n-----------База " << base_index << " активирована----------\n";
            presenter_->stop_convoy();
            presenter_->start_pirates();
            presenter_->move_pirates(dt);
            presenter_->stop_pirates();
            std::cout << "\n-----------Пираты напали на конвой----------\n";
            
            while (true) {
                std::cout << "Введите стратегию для конвоя(random, closest, weakest, strongest): ";
                std::string strategy;
                std::cin >> strategy;

                if (strategy == "random" || strategy == "closest" || strategy == "strongest" || strategy == "weakest") {
                    presenter_->set_convoy_strategy(strategy);
                    break;
                }
                else {
                    std::cout << "Неправильный ввод. Введите название стратегии\n";
                }
            }
            while (true) {
                std::cout << "Введите стратегию для пиратов(random, closest, weakest, strongest): ";
                std::string strategy;
                std::cin >> strategy;

                if (strategy == "random" || strategy == "closest" || strategy == "strongest" || strategy == "weakest") {
                    presenter_->set_pirate_strategy(strategy);
                    break;
                }
                else {
                    std::cout << "Неправильный ввод. Введите название стратегии\n";
                }
            }

            while (presenter_->count_alive_convoy_ships() != 0 && presenter_->count_alive_pirate_ships() != 0) {
                presenter_->auto_combat_parallel();
                std::cout << "\nКонвой:" << presenter_->convoy_info();
                std::cout << "\nПираты:" << presenter_->pirate_info();
            }

            if (presenter_->count_alive_convoy_ships() == 0) break;
            else {
                presenter_->update_base_status(base_index);
            }


            std::cout << "\n-------------База "<< base_index << " повержена------------\n";
        }
        presenter_->start_convoy();
    }
    if (presenter_->has_reached_destination()) {
        std::cout << "\n\nПоздравляю, конвой достиг пункта назначения!\n";
        if (presenter_->mission_completed()) {
            std::cout << "Миссия выполнена! Доставилось требуемое кол-во груза\n\n";
        }
        else std::cout << "\n\nНеудача, миссия провалена(\n\n";
    }
    else std::cout << "\n\nНеудача, миссия провалена(\n\n";
}

void ViewConsole::run(bool is_parallel) {
    save_or_new_game();
    mission_info();
    purchase_ships();
    load_ships();
    purchase_weapons();
    if (is_parallel) mission_parallel();
    else mission_sequential();
}