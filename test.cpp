#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "template/LookupTable.hpp"
#include <vector>
#include <string>
#include <cmath>
#include "template/MyClass.hpp"

#include "entity/ship/Concrete/GuardShip.hpp"
#include "entity/ship/Concrete/WarShip.hpp"
#include "entity/ship/Concrete/TransportShip.hpp"

#include "entity/weapon/Concrete/Gun.hpp"
#include "entity/weapon/Concrete/Rocket.hpp"

#include "entity/ship/Factories/ShipFactoryManager.hpp"
#include "entity/ship/Factories/GuardShipFactory.hpp"
#include "entity/ship/Factories/WarShipFactory.hpp"
#include "entity/ship/Factories/TransportShipFactory.hpp"

#include "entity/weapon/Factories/WeaponFactoryManager.hpp"
#include "entity/weapon/Factories/GunFactory.hpp"
#include "entity/weapon/Factories/RocketFactory.hpp"

#include "mission/Mission.hpp"

#include "mapper/mission/FromDTO/MissionMapper.hpp"
#include "mapper/mission/ToDTO/MissionDTOMapper.hpp"

#include "mapper/ship/Managers/ShipMapperManager.hpp"
#include "mapper/ship/Managers/ShipDTOMapperManager.hpp"

#include "repository/PirateRepository.hpp"
#include "repository/ShipRepository.hpp"

#include "service/cargo/CargoService.hpp"
#include "service/combat/CombatService.hpp"
#include "service/ID/ShipIDGenerator.hpp"
#include "service/movement/MovementService.hpp"
#include "service/pirate/PirateSpawnService.hpp"
#include "service/purchase/PurchaseService.hpp"
#include "service/state/YamlStateService.hpp"

#include "loader/Loader.hpp"

const double EPS = 1e-9;

TEST_CASE("Class LookupTable") {
    SECTION("Constructors") {
        SECTION("Base") {
            LookupTable<int, std::string> table;
            REQUIRE(table.size() == 0);
            REQUIRE(table.empty());
        }

        SECTION("Iter, Iter") {
            std::vector<std::pair<int, std::string>> v = {{1, "apple"}, {2, "peach"}};
            LookupTable<int, std::string> table(v.begin(), v.end());
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
        }

        SECTION("Initial list") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}};
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
        }

        SECTION("copy") {
            LookupTable<int, std::string> copy = {{1, "apple"}, {2, "peach"}};
            LookupTable<int, std::string> table(copy);
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
        }

        SECTION("move") {
            LookupTable<int, std::string> move = {{1, "apple"}, {2, "peach"}};
            LookupTable<int, std::string> table(std::move(move));
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));

            REQUIRE(move.size() == 0);
            REQUIRE(move.empty());
        }
    }

    SECTION("Emplace") {
        SECTION("emplace") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            table.emplace(4, "orange");
            REQUIRE(table.size() == 4);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));

            table.erase(1);
            table.erase(3);
            table.erase(2);
            table.emplace(1, "apple");
            REQUIRE(table.contains(1));
            table.emplace(2, "peach");
            REQUIRE(table.contains(2));
        }
    }

    SECTION("Insert") {
        SECTION("value") {
            std::pair<int, std::string> p(3, "lemon");
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}};
            table.insert(p);
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
        }

        SECTION("&&value") {
            std::pair<int, std::string> p(3, "lemon");
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}};
            table.insert(std::move(p));
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));

            REQUIRE(p.second == std::string());
        }

        SECTION("Key, Value") {
            int k = 3;
            std::string val = "lemon";
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}};
            table.insert(k, val);
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
        }

        SECTION("&&Key, &&Value") {
            int k = 3;
            std::string val = "lemon";
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}};
            table.insert(std::move(k), std::move(val));
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));

            REQUIRE(val == std::string());
        }

        SECTION("Iter, Iter") {
            std::vector<std::pair<int, std::string>> v = {{3, "lemon"}, {4, "melon"}};
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}};
            table.insert(v.begin(), v.end());
            REQUIRE(table.size() == 4);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));
        }

        SECTION("Initial list") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}};
            table.insert({{3, "lemon"}, {4, "melon"}});
            REQUIRE(table.size() == 4);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));
        }
    }

    SECTION("Erase") {
        SECTION("key") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}, {4, "orange"}};
            REQUIRE(table.size() == 4);
            table.erase(3);
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
            REQUIRE(table.contains(4));
            table.erase(4);
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(4));

            REQUIRE(table.erase(5) == 0);
        }

        SECTION("Iter") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}, {4, "orange"}};
            REQUIRE(table.size() == 4);
            table.erase(++table.begin());
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(!table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));

            table.erase(--table.end());
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(3));
            REQUIRE(!table.contains(4));

            table.erase(table.begin());
            REQUIRE(table.size() == 1);
            REQUIRE(!table.contains(1));
            REQUIRE(table.contains(3));

            REQUIRE(table.erase(table.end()) == table.end());
            LookupTable<int, std::string> table_0;
            REQUIRE(table_0.erase(table_0.begin()) == table_0.end());
        }

        SECTION("Iter, Iter") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}, {4, "orange"}};
            REQUIRE(table.size() == 4);
            TableIterator it = --table.end();
            table.erase(table.cbegin(), --it);
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(4));
            REQUIRE(table.contains(3));
            REQUIRE(!table.contains(1));
            REQUIRE(!table.contains(2));

            table.erase(table.begin(), table.end());
            REQUIRE(table.size() == 0);

            LookupTable<int, std::string> other = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            REQUIRE(other.erase(--other.end(), other.begin()) == other.end());
            other.erase(++other.begin(), --other.end());
            REQUIRE(other.size() == 2);
            REQUIRE(other.contains(1));
            REQUIRE(other.contains(3));
            REQUIRE(!other.contains(2));

            other.erase(++other.begin(), other.end());
            REQUIRE(other.size() == 1);
            REQUIRE(other.contains(1));
            REQUIRE(!other.contains(3));
        }
    }

    SECTION("Other methods") {
        SECTION("max_size") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            REQUIRE(table.max_size() == std::numeric_limits<size_t>::max() / sizeof(TableNode<int, std::string>));
        }

        SECTION("count") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            REQUIRE(table.count(1) == 1);
            REQUIRE(table.count(5) == 0);
        }

        SECTION("find(return iterator)") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            REQUIRE(table.find(1) == table.begin());
            REQUIRE(table.find(5) == table.end());
        }

        SECTION("find(return const_iterator)") {
            const LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            REQUIRE(table.find(1) == table.begin());
            REQUIRE(table.find(5) == table.end());
        }

        SECTION("at") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            REQUIRE(table.at(1) == "apple");
            REQUIRE(table.at(2) == "peach");
            REQUIRE(table.at(3) == "lemon");
            REQUIRE_THROWS(table.at(5));
        }

        SECTION("const at") {
            const LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            REQUIRE(table.at(1) == "apple");
            REQUIRE(table.at(2) == "peach");
            REQUIRE(table.at(3) == "lemon");
            REQUIRE_THROWS(table.at(5));
        }

        SECTION("bucket_collection") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}, {4, "orange"}, {5, "melon"}};
            table.erase(2);
            table.erase(1);
            table.insert({{1, "pineapple"}});
        }
    }

    SECTION("Operators") {
        SECTION("operator[] &") {
            int k1 = 1, k2 = 2, k3 = 3;
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            REQUIRE(table[k1] == "apple");
            REQUIRE(table[k2] == "peach");
            REQUIRE(table[k3] == "lemon");


            int new_index = 10;
            table[new_index] = "pineapple";
            REQUIRE(table.size() == 4);
            REQUIRE(table.count(new_index) == 1);
        }

        SECTION("operator[] &&") {
            int k1 = 1, k2 = 2, k3 = 3;
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            REQUIRE(table[std::move(k1)] == "apple");
            REQUIRE(table[std::move(k2)] == "peach");
            REQUIRE(table[std::move(k3)] == "lemon");

            int new_index = 10;
            table[std::move(new_index)] = "pineapple";
            REQUIRE(table.size() == 4);
            REQUIRE(table.count(new_index) == 1);
        }

        SECTION("operator==") {
            LookupTable<int, std::string> table_1 = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            LookupTable<int, std::string> table_2 = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            LookupTable<int, std::string> table_3 = {{1, "apple"}, {2, "peach"}};

            REQUIRE(table_1 == table_2);
            REQUIRE(!(table_1 == table_3));
        }

        SECTION("copy operator=") {
            LookupTable<int, std::string> table_1 = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            LookupTable<int, std::string> table_2 = {{4, "melon"}, {5, "orange"}};
            table_2 = table_1;
            table_1 = table_1;
            REQUIRE(table_2.size() == 3);
            REQUIRE(table_2.contains(1));
            REQUIRE(table_2.contains(2));
            REQUIRE(table_2.contains(3));
        }

        SECTION("move operator=") {
            LookupTable<int, std::string> table_1 = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            LookupTable<int, std::string> table_2 = {{4, "melon"}, {5, "orange"}};
            table_2 = std::move(table_1);
            REQUIRE(table_2.size() == 3);
            REQUIRE(table_2.contains(1));
            REQUIRE(table_2.contains(2));
            REQUIRE(table_2.contains(3));

            REQUIRE(table_1.size() == 0);
            REQUIRE(table_1.empty());
        }

        SECTION("initial list operator=") {
            LookupTable<int, std::string> table_2 = {{4, "melon"}, {5, "orange"}};
            table_2 = {{1, "apple"}, {2, "peach"}};
            REQUIRE(table_2.size() == 2);
            REQUIRE(table_2.contains(1));
            REQUIRE(table_2.contains(2));
        }
    }
}

TEST_CASE("Class TableIterator") {
    SECTION("skip_unoccupied_backward") {
        LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
        table.erase(2);
        REQUIRE((--(--table.end()))->second == "apple");
    }

    SECTION("operator=") {
        LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
        auto it_1 = table.begin();
        auto it_2 = table.cend();
        it_2 = it_1;
        REQUIRE(it_2->second == "apple");
    }

    SECTION("operator*") {
        LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
        auto it = table.begin();
        REQUIRE((*it).second == "apple");
        ++it;
        REQUIRE((*it).second == "peach");
        ++it;
        REQUIRE((*it).second == "lemon");
    }

    SECTION("operator++(int)") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            auto it1 = table.begin();
            auto it2 = it1++;
            REQUIRE(it1->second == "peach");
            REQUIRE(it2->second == "apple");
        }

    SECTION("operator--(int)") {
        LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}};
        auto it1 = --table.end();
        auto it2 = it1--;
        REQUIRE(it1->second == "apple");
        REQUIRE(it2->second == "peach");
    }

    SECTION("operator<") {
        LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
        auto it1 = table.begin();
        auto it2 = --table.end();
        REQUIRE(it1 < it2);
    }

    SECTION("operator>") {
        LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
        auto it1 = --table.end();
        auto it2 = table.begin();
        REQUIRE(it1 > it2);
    }

    SECTION("operator<=") {
        LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
        auto it1 = table.begin();
        auto it2 = --table.end();
        auto it3 = it1;
        REQUIRE(it1 <= it2);
        REQUIRE(it1 <= it3);
    }

    SECTION("operator>=") {
            LookupTable<int, std::string> table = {{1, "apple"}, {2, "peach"}, {3, "lemon"}};
            auto it1 = table.begin();
            auto it2 = --table.end();
            auto it3 = it1;
            REQUIRE(it2 >= it1);
            REQUIRE(it3 >= it1);
        }
}

TEST_CASE("Struct TableNode") {
    SECTION("Swap") {
        TableNode<int, std::string> ef = empty_first_t();
        TableNode<int, std::string> e = empty_t();
        TableNode<int, std::string> el = empty_last_t();
        TableNode<int, std::string> of = occupied_first_t<int, std::string>(3, "of");
        TableNode<int, std::string> o = occupied_t<int, std::string>(4, "o");
        TableNode<int, std::string> ol = occupied_last_t<int, std::string>(5, "ol");

        swap_variants(ef, e);
        REQUIRE(ef.index() == 1);
        REQUIRE(e.index() == 0);
        swap_variants(ef, e);
        swap_variants(ef, el);
        REQUIRE(ef.index() == 2);
        REQUIRE(el.index() == 0);
        swap_variants(ef, el);
        swap_variants(ef, of);
        REQUIRE(ef.index() == 3);
        REQUIRE(of.index() == 0);
        swap_variants(ef, of);
        swap_variants(ef, o);
        REQUIRE(ef.index() == 4);
        REQUIRE(o.index() == 0);
        swap_variants(ef, o);
        swap_variants(ef, ol);
        REQUIRE(ef.index() == 5);
        REQUIRE(ol.index() == 0);
        swap_variants(ef, ol);

        swap_variants(e, el);
        REQUIRE(e.index() == 2);
        REQUIRE(el.index() == 1);
        swap_variants(e, el);
        swap_variants(e, of);
        REQUIRE(e.index() == 3);
        REQUIRE(of.index() == 1);
        swap_variants(e, of);
        swap_variants(e, o);
        REQUIRE(e.index() == 4);
        REQUIRE(o.index() == 1);
        swap_variants(e, o);
        swap_variants(e, ol);
        REQUIRE(e.index() == 5);
        REQUIRE(ol.index() == 1);
        swap_variants(e, ol);

        swap_variants(el, of);
        REQUIRE(el.index() == 3);
        REQUIRE(of.index() == 2);
        swap_variants(el, of);
        swap_variants(el, o);
        REQUIRE(el.index() == 4);
        REQUIRE(o.index() == 2);
        swap_variants(el, o);
        swap_variants(el, ol);
        REQUIRE(el.index() == 5);
        REQUIRE(ol.index() == 2);
        swap_variants(el, ol);

        swap_variants(of, o);
        REQUIRE(of.index() == 4);
        REQUIRE(o.index() == 3);
        swap_variants(of, o);
        swap_variants(of, ol);
        REQUIRE(of.index() == 5);
        REQUIRE(ol.index() == 3);
        swap_variants(of, ol);

        swap_variants(o, ol);
        REQUIRE(o.index() == 5);
        REQUIRE(ol.index() == 4);
        swap_variants(o, ol);
    }
}

TEST_CASE("Class LookupTable with MyClass") {
    SECTION("Constructors") {
        SECTION("Base") {
            LookupTable<int, MyClass> table;
            REQUIRE(table.size() == 0);
            REQUIRE(table.empty());
        }

        SECTION("Iter, Iter") {
            MyClass a, b;
            std::vector<std::pair<int, MyClass>> v = {{1, a}, {2, b}};
            LookupTable<int, MyClass> table(v.begin(), v.end());
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
        }

        SECTION("Initial list") {
            MyClass a, b;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
        }

        SECTION("copy") {
            MyClass a, b;
            LookupTable<int, MyClass> copy = {{1, a}, {2, b}};
            LookupTable<int, MyClass> table(copy);
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
        }

        SECTION("move") {
            MyClass a, b;
            LookupTable<int, MyClass> move = {{1, a}, {2, b}};
            LookupTable<int, MyClass> table(std::move(move));
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));

            REQUIRE(move.size() == 0);
            REQUIRE(move.empty());
        }
    }

    SECTION("Emplace") {
        SECTION("emplace") {
            MyClass a, b, c;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            table.emplace(3, c);
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));

            table.erase(1);
            table.erase(3);
            table.erase(2);
            table.emplace(1, a);
            REQUIRE(table.contains(1));
            table.emplace(2, b);
            REQUIRE(table.contains(2));
        }
    }

    SECTION("Insert") {
        SECTION("value") {
            MyClass a, b, c;
            std::pair<int, MyClass> p(3, c);
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            table.insert(p);
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
        }

        SECTION("&&value") {
            MyClass a, b, c;
            std::pair<int, MyClass> p(3, c);
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            table.insert(std::move(p));
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));

            REQUIRE(p.second.data() == nullptr);
        }

        SECTION("Key, Value") {
            int k = 3;
            MyClass a, b, c;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            table.insert(k, c);
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
        }

        SECTION("&&Key, &&Value") {
            int k = 3;
            MyClass a, b, c;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            table.insert(std::move(k), std::move(c));
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));

            REQUIRE(c.data() == nullptr);
        }

        SECTION("Iter, Iter") {
            MyClass a, b, c, d;
            std::vector<std::pair<int, MyClass>> v = {{3, c}, {4, d}};
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            table.insert(v.begin(), v.end());
            REQUIRE(table.size() == 4);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));
        }

        SECTION("Initial list") {
            MyClass a, b, c, d;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            table.insert({{3, c}, {4, d}});
            REQUIRE(table.size() == 4);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));
        }
    }

    SECTION("Erase") {
        SECTION("key") {
            MyClass a, b, c, d;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}, {3, c}, {4, d}};
            REQUIRE(table.size() == 4);
            table.erase(3);
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
            REQUIRE(table.contains(4));
            table.erase(4);
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(4));

            REQUIRE(table.erase(5) == 0);
        }

        SECTION("Iter") {
            MyClass a, b, c, d;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}, {3, c}, {4, d}};
            REQUIRE(table.size() == 4);
            table.erase(++table.begin());
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(!table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));

            table.erase(--table.end());
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(3));
            REQUIRE(!table.contains(4));

            table.erase(table.begin());
            REQUIRE(table.size() == 1);
            REQUIRE(!table.contains(1));
            REQUIRE(table.contains(3));

            REQUIRE(table.erase(table.end()) == table.end());
            LookupTable<int, MyClass> table_0;
            REQUIRE(table_0.erase(table_0.begin()) == table_0.end());
        }

        SECTION("Iter, Iter") {
            MyClass a, b, c, d;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}, {3, c}, {4, d}};
            REQUIRE(table.size() == 4);
            TableIterator it = --table.end();
            table.erase(table.cbegin(), --it);
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(4));
            REQUIRE(table.contains(3));
            REQUIRE(!table.contains(1));
            REQUIRE(!table.contains(2));

            table.erase(table.begin(), table.end());
            REQUIRE(table.size() == 0);

            LookupTable<int, MyClass> other = {{1, a}, {2, b}, {3, c}};
            REQUIRE(other.erase(--other.end(), other.begin()) == other.end());
            other.erase(++other.begin(), --other.end());
            REQUIRE(other.size() == 2);
            REQUIRE(other.contains(1));
            REQUIRE(other.contains(3));
            REQUIRE(!other.contains(2));

            other.erase(++other.begin(), other.end());
            REQUIRE(other.size() == 1);
            REQUIRE(other.contains(1));
            REQUIRE(!other.contains(3));
        }
    }

    SECTION("Other methods") {
        SECTION("max_size") {
            MyClass a, b, c, d;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}, {3, c}, {4, d}};
            REQUIRE(table.max_size() == std::numeric_limits<size_t>::max() / sizeof(TableNode<int, MyClass>));
        }

        SECTION("count") {
            MyClass a, b;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            REQUIRE(table.count(1) == 1);
            REQUIRE(table.count(5) == 0);
        }

        SECTION("find(return iterator)") {
            MyClass a, b, c, d;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}, {3, c}, {4, d}};
            REQUIRE(table.find(1) == table.begin());
            REQUIRE(table.find(5) == table.end());
        }

        SECTION("find(return const_iterator)") {
            MyClass a, b;
            const LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            REQUIRE(table.find(1) == table.begin());
            REQUIRE(table.find(5) == table.end());
        }

        SECTION("at") {
            MyClass a, b;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            MyClass a_copy = table.at(1);
            MyClass b_copy = table.at(2);
            for (size_t i = 0; i < 3; ++i) {
                REQUIRE(a_copy[i] == a[i]);
                REQUIRE(b_copy[i] == b[i]);
            }
            REQUIRE_THROWS(table.at(5));
        }

        SECTION("const at") {
            MyClass a, b;
            const LookupTable<int, MyClass> table = {{1, a}, {2, b}};
            const MyClass a_copy = table.at(1);
            const MyClass b_copy = table.at(2);
            for (size_t i = 0; i < 3; ++i) {
                REQUIRE(a_copy[i] == a[i]);
                REQUIRE(b_copy[i] == b[i]);
            }
            REQUIRE_THROWS(table.at(5));
        }
    }

    SECTION("Operators") {
        SECTION("operator[] &") {
            MyClass a, b, c, d;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}, {3, c}};
            int k1 = 1, k2 = 2, k3 = 3;
            MyClass a_copy = table[k1];
            MyClass b_copy = table[k2];
            MyClass c_copy = table[k3];
            for (size_t i = 0 ; i < 3; ++i) {
                REQUIRE(a_copy[i] == a[i]);
                REQUIRE(b_copy[i] == b[i]);
                REQUIRE(c_copy[i] == c[i]);
            }

            int new_index = 10;
            table[new_index] = d;
            REQUIRE(table.size() == 4);
            REQUIRE(table.count(new_index) == 1);
        }

        SECTION("operator[] &&") {
            MyClass a, b, c, d;
            LookupTable<int, MyClass> table = {{1, a}, {2, b}, {3, c}};
            int k1 = 1, k2 = 2, k3 = 3;
            MyClass a_copy = table[std::move(k1)];
            MyClass b_copy = table[std::move(k2)];
            MyClass c_copy = table[std::move(k3)];
            for (size_t i = 0 ; i < 3; ++i) {
                REQUIRE(a_copy[i] == a[i]);
                REQUIRE(b_copy[i] == b[i]);
                REQUIRE(c_copy[i] == c[i]);
            }

            int new_index = 10;
            table[std::move(new_index)] = d;
            REQUIRE(table.size() == 4);
            REQUIRE(table.count(new_index) == 1);
        }

        SECTION("operator==") {
            MyClass a, b, c;
            LookupTable<int, MyClass> table_1 = {{1, a}, {2, b}, {3, c}};
            LookupTable<int, MyClass> table_2 = {{1, a}, {2, b}, {3, c}};
            LookupTable<int, MyClass> table_3 = {{1, a}, {2, b}};

            REQUIRE(table_1 == table_2);
            REQUIRE(!(table_1 == table_3));
        }

        SECTION("copy operator=") {
            MyClass a, b, c, d, e;
            LookupTable<int, MyClass> table_1 = {{1, a}, {2, b}, {3, c}};
            LookupTable<int, MyClass> table_2 = {{4, d}, {5, e}};
            table_2 = table_1;
            table_1 = table_1;
            REQUIRE(table_2.size() == 3);
            REQUIRE(table_2.contains(1));
            REQUIRE(table_2.contains(2));
            REQUIRE(table_2.contains(3));
        }

        SECTION("move operator=") {
            MyClass a, b, c, d, e;
            LookupTable<int, MyClass> table_1 = {{1, a}, {2, b}, {3, c}};
            LookupTable<int, MyClass> table_2 = {{4, d}, {5, e}};
            table_2 = std::move(table_1);
            REQUIRE(table_2.size() == 3);
            REQUIRE(table_2.contains(1));
            REQUIRE(table_2.contains(2));
            REQUIRE(table_2.contains(3));

            REQUIRE(table_1.size() == 0);
            REQUIRE(table_1.empty());
        }

        SECTION("initial list operator=") {
            MyClass a, b, d, e;
            LookupTable<int, MyClass> table_2 = {{4, d}, {5, e}};
            table_2 = {{1, a}, {2, b}};
            REQUIRE(table_2.size() == 2);
            REQUIRE(table_2.contains(1));
            REQUIRE(table_2.contains(2));
        }
    }
}

TEST_CASE("Class LookupTable with unique_ptr") {
    SECTION("Constructors") {
        SECTION("Base") {
            LookupTable<int, std::unique_ptr<MyClass>> table;
            REQUIRE(table.size() == 0);
            REQUIRE(table.empty());
        }

        SECTION("Iter, Iter") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::vector<std::pair<int, std::unique_ptr<MyClass>>> v;
            v.push_back({1, std::move(a)});
            v.push_back({2, std::move(b)});
            LookupTable<int, std::unique_ptr<MyClass>> table(v.begin(), v.end());
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
        }

        SECTION("move") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> move;
            move.insert(1, std::move(a));
            move.insert(2, std::move(b));
            LookupTable<int, std::unique_ptr<MyClass>> table(std::move(move));
            REQUIRE(table.size() == 2);
            REQUIRE(!table.empty());
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));

            REQUIRE(move.size() == 0);
            REQUIRE(move.empty());
        }
    }

    SECTION("Emplace") {
        SECTION("emplace") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> e = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> f = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            table.emplace(4, std::move(d));
            table.emplace(5, std::move(e));
            table.emplace(6, std::move(f));
            REQUIRE(table.size() == 6);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));
            REQUIRE(table.contains(5));
            REQUIRE(table.contains(6));

            table.erase(1);
            table.erase(3);
            table.erase(2);
            a = std::make_unique<MyClass>();
            b = std::make_unique<MyClass>();
            table.emplace(1, std::move(a));
            REQUIRE(table.contains(1));
            table.emplace(2, std::move(b));
            REQUIRE(table.contains(2));
        }
    }

    SECTION("Insert") {
        SECTION("&&value") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::pair<int, std::unique_ptr<MyClass>> p(3, std::move(c));
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.insert(1, std::move(a));
            table.insert(2, std::move(b));
            table.insert(std::move(p));
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));

            REQUIRE(a == nullptr);
            REQUIRE(b == nullptr);
            REQUIRE(p.second == nullptr);
        }

        SECTION("Key, unique_ptr") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.insert(1, std::move(a));
            table.insert(2, std::move(b));
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
        }

        SECTION("Iter, Iter") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            std::vector<std::pair<int, std::unique_ptr<MyClass>>> v;
            v.push_back({3, std::move(c)});
            v.push_back({4, std::move(d)});
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.insert(v.begin(), v.end());
            REQUIRE(table.size() == 4);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));
        }
    }

    SECTION("Erase") {
        SECTION("key") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            table.emplace(4, std::move(d));
            REQUIRE(table.size() == 4);
            table.erase(3);
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(3));
            REQUIRE(table.contains(4));
            table.erase(4);
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(2));
            REQUIRE(!table.contains(4));

            REQUIRE(table.erase(5) == 0);
        }

        SECTION("Iter") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            table.emplace(4, std::move(d));
            REQUIRE(table.size() == 4);
            table.erase(++table.begin());
            REQUIRE(table.size() == 3);
            REQUIRE(table.contains(1));
            REQUIRE(!table.contains(2));
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));

            table.erase(--table.end());
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(1));
            REQUIRE(table.contains(3));
            REQUIRE(!table.contains(4));

            table.erase(table.begin());
            REQUIRE(table.size() == 1);
            REQUIRE(!table.contains(1));
            REQUIRE(table.contains(3));

            REQUIRE(table.erase(table.cend()) == table.end());
            LookupTable<int, std::unique_ptr<MyClass>> table_0;
            REQUIRE(table_0.erase(table_0.begin()) == table_0.end());
        }

        SECTION("Iter, Iter") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            table.emplace(4, std::move(d));
            REQUIRE(table.size() == 4);
            TableIterator it = --table.end();
            table.erase(table.cbegin(), --it);
            REQUIRE(table.size() == 2);
            REQUIRE(table.contains(4));
            REQUIRE(table.contains(3));
            REQUIRE(!table.contains(1));
            REQUIRE(!table.contains(2));

            table.erase(table.begin(), table.end());
            REQUIRE(table.size() == 0);

            a = std::make_unique<MyClass>();
            b = std::make_unique<MyClass>();
            c = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> other;
            other.emplace(1, std::move(a));
            other.emplace(2, std::move(b));
            other.emplace(3, std::move(c));
            REQUIRE(other.erase(--other.end(), other.begin()) == other.end());
            other.erase(++other.begin(), --other.end());
            REQUIRE(other.size() == 2);
            REQUIRE(other.contains(1));
            REQUIRE(other.contains(3));
            REQUIRE(!other.contains(2));

            other.erase(++other.begin(), other.end());
            REQUIRE(other.size() == 1);
            REQUIRE(other.contains(1));
            REQUIRE(!other.contains(3));
        }
    }

    SECTION("Other methods") {
        SECTION("max_size") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            table.emplace(4, std::move(d));
            REQUIRE(table.max_size() == std::numeric_limits<size_t>::max() / sizeof(TableNode<int, std::unique_ptr<MyClass>>));
        }

        SECTION("count") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            REQUIRE(table.count(1) == 1);
            REQUIRE(table.count(2) == 1);
            REQUIRE(table.count(5) == 0);
        }

        SECTION("clear") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.clear();
            REQUIRE(table.size() == 0);
            REQUIRE(table.empty());
        }

        SECTION("swap") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> other;
            other.emplace(3, std::move(c));
            other.emplace(4, std::move(d));
            table.swap(other);
            REQUIRE(table.contains(3));
            REQUIRE(table.contains(4));
            REQUIRE(other.contains(1));
            REQUIRE(other.contains(2));
        }

        SECTION("find(return iterator)") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            table.emplace(4, std::move(d));
            REQUIRE(table.find(1) == table.begin());
            REQUIRE(table.find(2) == ++table.begin());
            REQUIRE(table.find(5) == table.end());

            table.erase(++table.begin(), --table.end());
            REQUIRE(table.find(4) == ++table.begin());
        }

        SECTION("find(return const_iterator)") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            REQUIRE(table.find(1) == table.begin());
            REQUIRE(table.find(2) == ++table.begin());
            REQUIRE(table.find(3) == --table.end());
            REQUIRE(table.find(5) == table.end());
        }

        SECTION("at") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            std::unique_ptr<MyClass>& a_ref = table.at(1);
            std::unique_ptr<MyClass>& b_ref = table.at(2);
            std::unique_ptr<MyClass>& c_ref = table.at(3);
            for (int i = 0; i < 3; ++i) {
                REQUIRE((*a_ref)[i] == 142 * (i + 1));
                REQUIRE((*b_ref)[i] == 143 * (i + 1));
                REQUIRE((*c_ref)[i] == 144 * (i + 1));
            }
            REQUIRE_THROWS(table.at(5));
        }

        SECTION("const at") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> move;
            move.emplace(1, std::move(a));
            move.emplace(2, std::move(b));
            move.emplace(3, std::move(c));
            const LookupTable<int, std::unique_ptr<MyClass>> table(std::move(move));
            const std::unique_ptr<MyClass>& a_ref = table.at(1);
            const std::unique_ptr<MyClass>& b_ref = table.at(2);
            const std::unique_ptr<MyClass>& c_ref = table.at(3);
            auto const_begin = table.begin();
            REQUIRE(table.find(1) == const_begin);
            for (int i = 0; i < 3; ++i) {
                REQUIRE((*a_ref)[i] == 145 * (i + 1));
                REQUIRE((*b_ref)[i] == 146 * (i + 1));
                REQUIRE((*c_ref)[i] == 147 * (i + 1));
            }
            REQUIRE_THROWS(table.at(5));
        }
    }

    SECTION("Operators") {
        SECTION("operator[] &") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            int k1 = 1, k2 = 2, k3 = 3;
            std::unique_ptr<MyClass>& a_ref = table[k1];
            std::unique_ptr<MyClass>& b_ref = table[k2];
            std::unique_ptr<MyClass>& c_ref = table[k3];
            for (int i = 0 ; i < 3; ++i) {
                REQUIRE((*a_ref)[i] == 148 * (i + 1));
                REQUIRE((*b_ref)[i] == 149 * (i + 1));
                REQUIRE((*c_ref)[i] == 150 * (i + 1));
            }

            int new_index = 10;
            table[new_index] = std::move(d);
            REQUIRE(table.size() == 4);
            REQUIRE(table.count(new_index) == 1);
        }

        SECTION("operator[] &&") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table;
            table.emplace(1, std::move(a));
            table.emplace(2, std::move(b));
            table.emplace(3, std::move(c));
            int k1 = 1, k2 = 2, k3 = 3;
            std::unique_ptr<MyClass>& a_ref = table[std::move(k1)];
            std::unique_ptr<MyClass>& b_ref = table[std::move(k2)];
            std::unique_ptr<MyClass>& c_ref = table[std::move(k3)];
            for (int i = 0 ; i < 3; ++i) {
                REQUIRE((*a_ref)[i] == 152 * (i + 1));
                REQUIRE((*b_ref)[i] == 153 * (i + 1));
                REQUIRE((*c_ref)[i] == 154 * (i + 1));
            }

            int new_index = 10;
            table[std::move(new_index)] = std::move(d);
            REQUIRE(table.size() == 4);
            REQUIRE(table.count(new_index) == 1);
        }

        SECTION("operator==") {
            MyClass a, b, c;
            std::unique_ptr<MyClass> a_ptr_1 = std::make_unique<MyClass>(a);
            std::unique_ptr<MyClass> b_ptr_1 = std::make_unique<MyClass>(b);
            std::unique_ptr<MyClass> c_ptr_1 = std::make_unique<MyClass>(c);
            std::unique_ptr<MyClass> a_ptr_2 = std::make_unique<MyClass>(a);
            std::unique_ptr<MyClass> b_ptr_2 = std::make_unique<MyClass>(b);
            std::unique_ptr<MyClass> c_ptr_2 = std::make_unique<MyClass>(c);
            std::unique_ptr<MyClass> a_ptr_3 = std::make_unique<MyClass>(a);
            std::unique_ptr<MyClass> b_ptr_3 = std::make_unique<MyClass>(b);
            LookupTable<int, std::unique_ptr<MyClass>> table_1;
            table_1.emplace(1, std::move(a_ptr_1));
            table_1.emplace(2, std::move(b_ptr_1));
            table_1.emplace(3, std::move(c_ptr_1));

            LookupTable<int, std::unique_ptr<MyClass>> table_2;
            table_2.emplace(1, std::move(a_ptr_2));
            table_2.emplace(2, std::move(b_ptr_2));
            table_2.emplace(3, std::move(c_ptr_2));

            LookupTable<int, std::unique_ptr<MyClass>> table_3;
            table_3.emplace(1, std::move(a_ptr_3));
            table_3.emplace(2, std::move(b_ptr_3));

            REQUIRE(table_1 == table_2);
            REQUIRE(!(table_1 == table_3));
        }

        SECTION("move operator=") {
            std::unique_ptr<MyClass> a = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> b = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> c = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> d = std::make_unique<MyClass>();
            std::unique_ptr<MyClass> e = std::make_unique<MyClass>();
            LookupTable<int, std::unique_ptr<MyClass>> table_1;
            table_1.emplace(1, std::move(a));
            table_1.emplace(2, std::move(b));
            table_1.emplace(3, std::move(c));
            LookupTable<int, std::unique_ptr<MyClass>> table_2;
            table_2.emplace(1, std::move(d));
            table_2.emplace(2, std::move(e));
            table_2 = std::move(table_1);
            REQUIRE(table_2.size() == 3);
            REQUIRE(table_2.contains(1));
            REQUIRE(table_2.contains(2));
            REQUIRE(table_2.contains(3));

            REQUIRE(table_1.size() == 0);
            REQUIRE(table_1.empty());
        }
    }
}

TEST_CASE("Class GuardShip") {
    SECTION("Constructor") {
        GuardShip ship;
        REQUIRE(ship.get_captain() == Military("", ""));
        REQUIRE(std::abs(ship.get_cost() - 10000) < EPS);
        REQUIRE(std::abs(ship.get_health() - 100) < EPS);
        REQUIRE(ship.get_ID() == "");
        REQUIRE(std::abs(ship.get_max_health() - 100) < EPS);
        REQUIRE(std::abs(ship.get_max_speed() - 50) < EPS);
        REQUIRE(ship.get_name() == "Сторожевой корабль");
        REQUIRE(ship.get_position() == Vector(0.0, 0.0));
        REQUIRE(ship.get_speed() < EPS);
        REQUIRE(ship.get_type() == "guard");
        REQUIRE(ship.get_weapon_count() == 0);
        REQUIRE(ship.get_weapon_in_place(PlaceForWeapon::stern) == nullptr);

        std::ostringstream oss;
        oss << "Сторожевой корабль: " << ship.get_name() << "\n"
            << "Капитан: " << "" << "\n"
            << "Скорость: " << 0.0 << "/" << 50.0 << "\n"
            << "Здоровье: " << 100.0 << "/" << 100.0 << "\n"
            << "Оружие: " << 0 << "\n"
            << "Стоимость: " << 10000.0;
        std::string description = oss.str();
        REQUIRE(description == ship.get_description());

        REQUIRE(!ship.has_weapon_in_place(PlaceForWeapon::bow));
        REQUIRE(ship.is_alive());
        REQUIRE(ship.is_at_position(Vector(0.0, 0.0)));
        REQUIRE(ship.is_convoy());

        std::unique_ptr<IWeapon> weapon = std::make_unique<Gun>();
        ship.set_weapon_in_place(PlaceForWeapon::bow, std::move(weapon));
        REQUIRE(ship.has_weapon_in_place(PlaceForWeapon::bow));

        auto ship_clone = ship.clone();
        REQUIRE(ship_clone->get_captain() == Military("", ""));
        REQUIRE(std::abs(ship_clone->get_cost() - 10000) < EPS);
        REQUIRE(std::abs(ship_clone->get_health() - 100) < EPS);
        REQUIRE(ship_clone->get_ID() == "");
        REQUIRE(std::abs(ship_clone->get_max_health() - 100) < EPS);
        REQUIRE(std::abs(ship_clone->get_max_speed() - 50) < EPS);
        REQUIRE(ship_clone->get_name() == "Сторожевой корабль");
        REQUIRE(ship_clone->get_position() == Vector(0.0, 0.0));
        REQUIRE(ship_clone->get_speed() < EPS);
        REQUIRE(ship_clone->get_type() == "guard");
    }
}

TEST_CASE("Class TransportShip") {
    SECTION("Constructor") {
        TransportShip ship;
        REQUIRE(ship.get_captain() == Military("", ""));
        REQUIRE(std::abs(ship.get_cost() - 15000) < EPS);
        REQUIRE(std::abs(ship.get_health() - 150) < EPS);
        REQUIRE(ship.get_ID() == "");
        REQUIRE(std::abs(ship.get_max_health() - 150) < EPS);
        REQUIRE(std::abs(ship.get_max_speed() - 30) < EPS);
        REQUIRE(ship.get_name() == "Транспортный корабль");
        REQUIRE(ship.get_position() == Vector(0.0, 0.0));
        REQUIRE(ship.get_speed() < EPS);
        REQUIRE(ship.get_type() == "transport");
        REQUIRE(ship.get_cargo() < EPS);
        REQUIRE(std::abs(ship.get_max_cargo() - 1000) < EPS);
        REQUIRE(std::abs(ship.get_speed_reduction_factor() - 0.1) < EPS);

        std::ostringstream oss;
        oss << "Транспортный корабль: " << "Транспортный корабль" << "\n"
            << "Капитан: " << "" << "\n"
            << "Скорость: " << 0.0 << "/" << 30.0 << "\n"
            << "Здоровье: " << 150.0 << "/" << 150.0 << "\n"
            << "Груз: " << 0.0 << "/" << 1000.0 << "\n"
            << "Стоимость: " << 15000.0;
        std::string description = oss.str();
        REQUIRE(description == ship.get_description());

        REQUIRE(ship.is_alive());
        REQUIRE(ship.is_at_position(Vector(0.0, 0.0)));
        REQUIRE(ship.is_convoy());

        auto ship_clone = ship.clone();
        REQUIRE(ship_clone->get_captain() == Military("", ""));
        REQUIRE(std::abs(ship_clone->get_cost() - 15000) < EPS);
        REQUIRE(std::abs(ship_clone->get_health() - 150) < EPS);
        REQUIRE(ship_clone->get_ID() == "");
        REQUIRE(std::abs(ship_clone->get_max_health() - 150) < EPS);
        REQUIRE(std::abs(ship_clone->get_max_speed() - 30) < EPS);
        REQUIRE(ship_clone->get_name() == "Транспортный корабль");
        REQUIRE(ship_clone->get_position() == Vector(0.0, 0.0));
        REQUIRE(ship_clone->get_speed() < EPS);
        REQUIRE(ship_clone->get_type() == "transport");
    }
}

TEST_CASE("Class WarShip") {
    SECTION("Constructor") {
        WarShip ship;
        REQUIRE(ship.get_captain() == Military("", ""));
        REQUIRE(std::abs(ship.get_cost() - 25000) < EPS);
        REQUIRE(std::abs(ship.get_health() - 200) < EPS);
        REQUIRE(ship.get_ID() == "");
        REQUIRE(std::abs(ship.get_max_health() - 200) < EPS);
        REQUIRE(std::abs(ship.get_max_speed() - 40) < EPS);
        REQUIRE(ship.get_name() == "Военный корабль");
        REQUIRE(ship.get_position() == Vector(0.0, 0.0));
        REQUIRE(ship.get_speed() < EPS);
        REQUIRE(ship.get_type() == "war");
        REQUIRE(ship.get_cargo() < EPS);
        REQUIRE(std::abs(ship.get_max_cargo() - 500) < EPS);
        REQUIRE(std::abs(ship.get_speed_reduction_factor() - 0.15) < EPS);
        REQUIRE(ship.get_weapon_count() == 0);
        REQUIRE(ship.get_weapon_in_place(PlaceForWeapon::stern) == nullptr);

        std::ostringstream oss;
        oss << "Военный корабль: " << "Военный корабль" << "\n"
            << "Капитан: " << "" << "\n"
            << "Скорость: " << 0.0 << "/" << 40.0 << "\n"
            << "Здоровье: " << 200.0 << "/" << 200.0 << "\n"
            << "Груз: " << 0.0 << "/" << 500.0 << "\n"
            << "Оружие: " << 0 << "\n"
            << "Стоимость: " << 25000.0;
        std::string description = oss.str();
        REQUIRE(description == ship.get_description());

        REQUIRE(!ship.has_weapon_in_place(PlaceForWeapon::bow));
        REQUIRE(ship.is_alive());
        REQUIRE(ship.is_at_position(Vector(0.0, 0.0)));
        REQUIRE(ship.is_convoy());

        std::unique_ptr<IWeapon> weapon = std::make_unique<Gun>();
        ship.set_weapon_in_place(PlaceForWeapon::bow, std::move(weapon));
        REQUIRE(ship.has_weapon_in_place(PlaceForWeapon::bow));

        auto ship_clone = ship.clone();
        REQUIRE(ship_clone->get_captain() == Military("", ""));
        REQUIRE(std::abs(ship_clone->get_cost() - 25000) < EPS);
        REQUIRE(std::abs(ship_clone->get_health() - 200) < EPS);
        REQUIRE(ship_clone->get_ID() == "");
        REQUIRE(std::abs(ship_clone->get_max_health() - 200) < EPS);
        REQUIRE(std::abs(ship_clone->get_max_speed() - 40) < EPS);
        REQUIRE(ship_clone->get_name() == "Военный корабль");
        REQUIRE(ship_clone->get_position() == Vector(0.0, 0.0));
        REQUIRE(ship_clone->get_speed() < EPS);
        REQUIRE(ship_clone->get_type() == "war");
    }
}

TEST_CASE("Class DefaultCargo") {
    SECTION("Constructor") {
        DefaultCargo cargo(200.0, 0.15);
        REQUIRE(std::abs(cargo.get_max_cargo() - 200.0) < EPS);
        REQUIRE(cargo.get_cargo() < EPS);
        REQUIRE(std::abs(cargo.get_speed_reduction_factor() - 0.15) < EPS);
        cargo.set_max_cargo(250.0);
        REQUIRE(std::abs(cargo.get_max_cargo() - 250.0) < EPS);
        cargo.set_cargo(200.0);
        REQUIRE(std::abs(cargo.get_cargo() - 200) < EPS);
        REQUIRE(std::abs(cargo.get_max_speed_with_current_cargo() - 0.88) < EPS);
        cargo.add_cargo(50.0);
        REQUIRE(std::abs(cargo.get_cargo() - 250) < EPS);
        cargo.remove_cargo(50.0);
        REQUIRE(std::abs(cargo.get_cargo() - 200) < EPS);
        REQUIRE(cargo.can_add_cargo(40));
        REQUIRE(!cargo.can_add_cargo(100));
        REQUIRE(cargo.can_remove_cargo(100));
        REQUIRE(!cargo.can_remove_cargo(250));
        cargo.set_speed_reduction_factor(0.25);
        REQUIRE(std::abs(cargo.get_speed_reduction_factor() - 0.25) < EPS);
    }
}

TEST_CASE("Class DefaultGuard") {
    SECTION("Constructor") {
        DefaultGuard guard;
        std::unique_ptr<IWeapon> gun = std::make_unique<Gun>();
        guard.set_weapon_in_place(PlaceForWeapon::bow, std::move(gun));
        std::unique_ptr<IWeapon> rocket = std::make_unique<Rocket>();
        guard.set_weapon_in_place(PlaceForWeapon::stern, std::move(rocket));
        REQUIRE((guard.get_max_range() - 5.0) < EPS);
    }
}

TEST_CASE("Class DefaultShip") {
    SECTION("Constructor") {
        GuardShip ship("Аврора", Military("Иванов", "Капитан"), 100.0, 100.0, 1000.0);
        ship.set_position(Vector(1.5, -10.2));
        REQUIRE(std::abs(ship.get_position().x - 1.5) < EPS);
        REQUIRE(std::abs(ship.get_position().y + 10.2) < EPS);

        ship.set_speed(-1.1);
        REQUIRE(std::abs(ship.get_speed()) < EPS);
        ship.set_speed(50.5);
        REQUIRE(std::abs(ship.get_speed() - 50.5) < EPS);
        ship.set_speed(150.0);
        REQUIRE(std::abs(ship.get_speed() - 100.0) < EPS);
        REQUIRE_THROWS(ship.set_max_speed(-1.0));
        ship.set_max_speed(50.0);
        REQUIRE(std::abs(ship.get_speed() - 50.0) < EPS);
        REQUIRE(std::abs(ship.get_max_speed() - 50.0) < EPS);

        ship.set_health(-1.0);
        REQUIRE(std::abs(ship.get_health()) < EPS);
        REQUIRE(!ship.is_alive());
        REQUIRE(std::abs(ship.get_speed()) < EPS);
        ship.set_health(50.0);
        REQUIRE(std::abs(ship.get_health() - 50.0) < EPS);
        REQUIRE(ship.is_alive());
        ship.set_health(150.0);
        REQUIRE(std::abs(ship.get_health() - 100.0) < EPS);
        REQUIRE(ship.is_alive());

        REQUIRE_THROWS(ship.set_max_health(-1.0));
        ship.set_max_health(50.0);
        REQUIRE(std::abs(ship.get_max_health() - 50.0) < EPS);
        REQUIRE(std::abs(ship.get_health() - 50.0) < EPS);

        ship.set_name("Титаник");
        REQUIRE(ship.get_name() == "Титаник");
        ship.set_captain(Military("Барсуков", "Майор"));
        REQUIRE(ship.get_captain().FIO == "Барсуков");
        REQUIRE(ship.get_captain().rank == "Майор");
        ship.set_cost(2000.0);
        REQUIRE(std::abs(ship.get_cost() - 2000.0) < EPS);
        ship.set_ID("ABC");
        REQUIRE(ship.get_ID() == "ABC");
        ship.set_convoy(true);
        REQUIRE(ship.is_convoy());

        ship.take_damage(-1.0);
        ship.take_damage(56.0);
        REQUIRE(std::abs(ship.get_health()) < EPS);
        REQUIRE(std::abs(ship.get_speed()) < EPS);
        REQUIRE(!ship.is_alive());

    }
}

TEST_CASE("Class ShipFactoryManager") {
    SECTION("Constructor") {
        ShipFactoryManager manager;
        std::unique_ptr<IShip> war_ship_def = manager.create_ship("war");
        REQUIRE(war_ship_def->get_name() == "");
        REQUIRE(war_ship_def->get_captain().FIO == "");
        REQUIRE(war_ship_def->get_captain().rank == "");
        REQUIRE(std::abs(war_ship_def->get_max_speed()) < EPS);
        REQUIRE(std::abs(war_ship_def->get_max_health()) < EPS);
        REQUIRE(std::abs(war_ship_def->get_cost()) < EPS);
        REQUIRE(war_ship_def->get_ID() == "A");

        std::unique_ptr<IShip> guard_ship_def = manager.create_ship("guard");
        REQUIRE(guard_ship_def->get_name() == "");
        REQUIRE(guard_ship_def->get_captain().FIO == "");
        REQUIRE(guard_ship_def->get_captain().rank == "");
        REQUIRE(std::abs(guard_ship_def->get_max_speed()) < EPS);
        REQUIRE(std::abs(guard_ship_def->get_max_health()) < EPS);
        REQUIRE(std::abs(guard_ship_def->get_cost()) < EPS);
        REQUIRE(guard_ship_def->get_ID() == "B");

        std::unique_ptr<IShip> guard_ship_pirate_def = manager.create_ship("guard", false);
        REQUIRE(guard_ship_pirate_def->get_name() == "");
        REQUIRE(guard_ship_pirate_def->get_captain().FIO == "");
        REQUIRE(guard_ship_pirate_def->get_captain().rank == "");
        REQUIRE(std::abs(guard_ship_pirate_def->get_max_speed()) < EPS);
        REQUIRE(std::abs(guard_ship_pirate_def->get_max_health()) < EPS);
        REQUIRE(std::abs(guard_ship_pirate_def->get_cost()) < EPS);
        REQUIRE(guard_ship_pirate_def->get_ID() == "1");

        std::unique_ptr<IShip> transport_ship_def = manager.create_ship("transport");
        REQUIRE(transport_ship_def->get_name() == "");
        REQUIRE(transport_ship_def->get_captain().FIO == "");
        REQUIRE(transport_ship_def->get_captain().rank == "");
        REQUIRE(std::abs(transport_ship_def->get_max_speed()) < EPS);
        REQUIRE(std::abs(transport_ship_def->get_max_health()) < EPS);
        REQUIRE(std::abs(transport_ship_def->get_cost()) < EPS);
        REQUIRE(transport_ship_def->get_ID() == "C");

        IShipFactory* factory = manager.get_factory("guard");
        REQUIRE(factory != nullptr);
        IShipFactory* factory_null = manager.get_factory("guardian");
        REQUIRE(factory_null == nullptr);

        REQUIRE(manager.has_factory("guard"));
        REQUIRE(!manager.has_factory("guardian"));
        manager.set_default_max_cargo("transport", 100.0);
        manager.set_default_max_cargo("war", 100.0);

        std::unique_ptr<IShip> war_ship = manager.create_ship("war", "Титаник", Military("Барсуков", "Майор"), 100.0, 100.0, 1000.0);
        REQUIRE(war_ship->get_name() == "Титаник");
        REQUIRE(war_ship->get_captain().FIO == "Барсуков");
        REQUIRE(war_ship->get_captain().rank == "Майор");
        REQUIRE(std::abs(war_ship->get_max_speed() - 100.0) < EPS);
        REQUIRE(std::abs(war_ship->get_max_health() - 100.0) < EPS);
        REQUIRE(std::abs(war_ship->get_cost() - 1000.0) < EPS);
        REQUIRE(war_ship->get_ID() == "D");

        std::unique_ptr<IShip> guard_pirate_ship = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 100.0, 100.0, 1000.0, false);
        REQUIRE(guard_pirate_ship->get_name() == "Титаник");
        REQUIRE(guard_pirate_ship->get_captain().FIO == "Барсуков");
        REQUIRE(guard_pirate_ship->get_captain().rank == "Майор");
        REQUIRE(std::abs(guard_pirate_ship->get_max_speed() - 100.0) < EPS);
        REQUIRE(std::abs(guard_pirate_ship->get_max_health() - 100.0) < EPS);
        REQUIRE(std::abs(guard_pirate_ship->get_cost() - 1000.0) < EPS);
        REQUIRE(guard_pirate_ship->get_ID() == "2");

        std::unique_ptr<IShip> null_ship = manager.create_ship("warrior", "Титаник", Military("Барсуков", "Майор"), 100.0, 100.0, 1000.0);
        REQUIRE(null_ship == nullptr);

        std::unique_ptr<GuardShip> guard_prototype = std::make_unique<GuardShip>("Аврора", Military(), 20.0, 50.0, 5000.0);
        GuardShipFactory guard_factory;
        guard_factory.set_prototype(std::move(guard_prototype));
        std::unique_ptr<IShip> guard_clone = guard_factory.create_ship();
        REQUIRE("Аврора" == guard_clone->get_name());
        REQUIRE(Military() == guard_clone->get_captain());
        REQUIRE(std::abs(guard_clone->get_max_speed() - 20.0) < EPS);
        REQUIRE(std::abs(guard_clone->get_max_health() - 50.0) < EPS);
        REQUIRE(std::abs(guard_clone->get_cost() - 5000.0) < EPS);
        REQUIRE(guard_clone->get_ID() == "");

        std::unique_ptr<WarShip> war_prototype = std::make_unique<WarShip>("Аврора", Military(), 20.0, 50.0, 5000.0);
        WarShipFactory war_factory;
        war_factory.set_prototype(std::move(war_prototype));
        std::unique_ptr<IShip> war_clone = war_factory.create_ship();
        REQUIRE("Аврора" == war_clone->get_name());
        REQUIRE(Military() == war_clone->get_captain());
        REQUIRE(std::abs(war_clone->get_max_speed() - 20.0) < EPS);
        REQUIRE(std::abs(war_clone->get_max_health() - 50.0) < EPS);
        REQUIRE(std::abs(war_clone->get_cost() - 5000.0) < EPS);
        REQUIRE(war_clone->get_ID() == "");

        std::unique_ptr<TransportShip> transport_prototype = std::make_unique<TransportShip>("Аврора", Military(), 20.0, 50.0, 5000.0);
        TransportShipFactory transport_factory;
        transport_factory.set_prototype(std::move(transport_prototype));
        std::unique_ptr<IShip> transport_clone = transport_factory.create_ship();
        REQUIRE("Аврора" == transport_clone->get_name());
        REQUIRE(Military() == transport_clone->get_captain());
        REQUIRE(std::abs(transport_clone->get_max_speed() - 20.0) < EPS);
        REQUIRE(std::abs(transport_clone->get_max_health() - 50.0) < EPS);
        REQUIRE(std::abs(transport_clone->get_cost() - 5000.0) < EPS);
        REQUIRE(transport_clone->get_ID() == "");
    }
}

TEST_CASE("Class Gun") {
    SECTION("Constructor") {
        Gun weapon;
        REQUIRE(weapon.get_type() == "gun");
        REQUIRE(weapon.get_name() == "Пушка");
        REQUIRE(std::abs(weapon.get_damage() - 25.0) < EPS);
        REQUIRE(std::abs(weapon.get_range() - 3.0) < EPS);
        REQUIRE(weapon.get_fire_rate() == 2);
        REQUIRE(weapon.get_max_ammo() == 50);
        REQUIRE(weapon.get_current_ammo() == 50);
        REQUIRE(std::abs(weapon.get_cost() - 5000.0) < EPS);
        REQUIRE(std::abs(weapon.get_accuracy() - 0.7) < EPS);
        REQUIRE(weapon.get_explosion_radius() < EPS);

        std::ostringstream oss;
	    oss << std::fixed << std::setprecision(1);
	    oss << "Пушка" << " [Урон: " << 25.0
	        << ", Дальность: " << 3.0
	        << ", Скорострельность: " << 2
	        << ", Боезапас: " << 50 << "/" << 50
	        << ", Точность: " << std::setprecision(0) << (0.7 * 100) << "%"
	        << std::setprecision(1) << ", Стоимость: " << 5000.0 << "]";
        REQUIRE(oss.str() == weapon.get_description());

        weapon.set_current_ammo(20);
        REQUIRE(weapon.get_current_ammo() == 20);
        weapon.set_current_ammo(100);
        REQUIRE(weapon.get_current_ammo() == 50);

        weapon.set_damage(-20.0);
        REQUIRE(std::abs(weapon.get_damage()) < EPS);
        weapon.set_damage(20.0);
        REQUIRE(std::abs(weapon.get_damage() - 20.0) < EPS);

        weapon.set_range(-10.0);
        REQUIRE(std::abs(weapon.get_range()) < EPS);
        weapon.set_range(10.0);
        REQUIRE(std::abs(weapon.get_range() - 10.0) < EPS);

        weapon.set_accuracy(-1.0);
        REQUIRE(std::abs(weapon.get_accuracy()) < EPS);
        weapon.set_accuracy(1.5);
        REQUIRE(std::abs(weapon.get_accuracy() - 1.0) < EPS);
        weapon.set_accuracy(0.99);
        REQUIRE(std::abs(weapon.get_accuracy() - 0.99) < EPS);
    }
}

TEST_CASE("Class WeaponFactoryManager") {
    SECTION("Constructor") {
        WeaponFactoryManager manager;
        std::unique_ptr<IWeapon> gun_def = manager.create_weapon("gun");
        REQUIRE(gun_def->get_name() == "Пушка");
        REQUIRE(std::abs(gun_def->get_damage() - 25.0) < EPS);
        REQUIRE(std::abs(gun_def->get_range() - 3.0) < EPS);
        REQUIRE(gun_def->get_fire_rate() == 2);
        REQUIRE(gun_def->get_max_ammo() == 50);
        REQUIRE(std::abs(gun_def->get_cost() - 5000.0) < EPS);
        REQUIRE(std::abs(gun_def->get_accuracy() - 0.7) < EPS);
        REQUIRE(std::abs(gun_def->get_explosion_radius()) < EPS);

        std::unique_ptr<IWeapon> rocket_def = manager.create_weapon("rocket");
        REQUIRE(rocket_def->get_name() == "Ракета");
        REQUIRE(std::abs(rocket_def->get_damage() - 40.0) < EPS);
        REQUIRE(std::abs(rocket_def->get_range() - 5.0) < EPS);
        REQUIRE(rocket_def->get_fire_rate() == 1);
        REQUIRE(rocket_def->get_max_ammo() == 20);
        REQUIRE(std::abs(rocket_def->get_cost() - 8000.0) < EPS);
        REQUIRE(std::abs(rocket_def->get_accuracy() - 0.9) < EPS);
        REQUIRE(std::abs(rocket_def->get_explosion_radius() - 1.0) < EPS);

        IWeaponFactory* factory = manager.get_factory("gun");
        REQUIRE(factory != nullptr);
        IWeaponFactory* factory_null = manager.get_factory("gundball");
        REQUIRE(factory_null == nullptr);

        REQUIRE(manager.has_factory("gun"));
        REQUIRE(!manager.has_factory("guardian"));

        std::unique_ptr<IWeapon> gun = manager.create_weapon("gun", "АК-47", 47.0, 30.0, 5, 100, 2500.0, 0.9);
        REQUIRE(gun->get_name() == "АК-47");
        REQUIRE(std::abs(gun->get_damage() - 47.0) < EPS);
        REQUIRE(std::abs(gun->get_range() - 30.0) < EPS);
        REQUIRE(gun->get_fire_rate() == 5);
        REQUIRE(gun->get_max_ammo() == 100);
        REQUIRE(std::abs(gun->get_cost() - 2500.0) < EPS);
        REQUIRE(std::abs(gun->get_accuracy() - 0.9) < EPS);
        REQUIRE(std::abs(gun->get_explosion_radius()) < EPS);

        std::unique_ptr<IWeapon> rocket = manager.create_weapon("rocket", "АК-47", 47.0, 30.0, 5, 100, 2500.0, 0.9, 5.0);
        REQUIRE(rocket->get_name() == "АК-47");
        REQUIRE(std::abs(rocket->get_damage() - 47.0) < EPS);
        REQUIRE(std::abs(rocket->get_range() - 30.0) < EPS);
        REQUIRE(rocket->get_fire_rate() == 5);
        REQUIRE(rocket->get_max_ammo() == 100);
        REQUIRE(std::abs(rocket->get_cost() - 2500.0) < EPS);
        REQUIRE(std::abs(rocket->get_accuracy() - 0.9) < EPS);
        REQUIRE(std::abs(rocket->get_explosion_radius() - 5.0) < EPS);

        std::unique_ptr<IWeapon> null_weapon = manager.create_weapon("rocketmen", "АК-47", 47.0, 30.0, 5, 100, 2500.0, 0.9, 5.2);
        REQUIRE(null_weapon == nullptr);

        std::unique_ptr<IWeapon> null_weapon_2 = manager.create_weapon("rocketmen");
        REQUIRE(null_weapon_2 == nullptr);

        std::unique_ptr<Gun> gun_prototype = std::make_unique<Gun>("АК-47", 47.0, 30.0, 5, 100, 2500.0, 0.9);
        GunFactory gun_factory;
        gun_factory.set_prototype(std::move(gun_prototype));
        std::unique_ptr<IWeapon> gun_clone = gun_factory.create_weapon();
        REQUIRE(gun_clone->get_name() == "АК-47");
        REQUIRE(std::abs(gun_clone->get_damage() - 47.0) < EPS);
        REQUIRE(std::abs(gun_clone->get_range() - 30.0) < EPS);
        REQUIRE(gun_clone->get_fire_rate() == 5);
        REQUIRE(gun_clone->get_max_ammo() == 100);
        REQUIRE(std::abs(gun_clone->get_cost() - 2500.0) < EPS);
        REQUIRE(std::abs(gun_clone->get_accuracy() - 0.9) < EPS);
        REQUIRE(std::abs(gun_clone->get_explosion_radius()) < EPS);

        std::unique_ptr<Rocket> rocket_prototype = std::make_unique<Rocket>("АК-47", 47.0, 30.0, 5, 100, 2500.0, 0.9, 5.0);
        RocketFactory rocket_factory;
        rocket_factory.set_prototype(std::move(rocket_prototype));
        std::unique_ptr<IWeapon> rocket_clone = rocket_factory.create_weapon();
        REQUIRE(rocket_clone->get_name() == "АК-47");
        REQUIRE(std::abs(rocket_clone->get_damage() - 47.0) < EPS);
        REQUIRE(std::abs(rocket_clone->get_range() - 30.0) < EPS);
        REQUIRE(rocket_clone->get_fire_rate() == 5);
        REQUIRE(rocket_clone->get_max_ammo() == 100);
        REQUIRE(std::abs(rocket_clone->get_cost() - 2500.0) < EPS);
        REQUIRE(std::abs(rocket_clone->get_accuracy() - 0.9) < EPS);
        REQUIRE(std::abs(rocket_clone->get_explosion_radius() - 5.0) < EPS);
    }
}

TEST_CASE("Mission") {
    SECTION("Constructor") {
        PirateBase pb;
        pb.trigger_distance = 5.0;
        pb.ship_count = 2;
        pb.is_activated = false;
        pb.is_defeated = false;
        std::vector<PirateBase> p_bases;
        for (size_t i = 0; i < 3; ++i) {
            pb.position.x = (i + 1) * 2.0;
            pb.position.y = (i + 1) * 1.5;
            if (i == 0) pb.is_activated = true;
            else pb.is_activated = false;
            p_bases.push_back(pb);
        }
        Mission mission("mission_1", Military("Барсуков", "Майор"), 100000.0, 1000.0, 50.0, 5, 5, Vector(), Vector(25.0, 25.0), 3.0, p_bases);
        REQUIRE(mission.get_id() == "mission_1");
        REQUIRE(mission.get_commander() == Military("Барсуков", "Майор"));
        REQUIRE(std::abs(mission.get_total_budget() - 100000.0) < EPS);
        REQUIRE(std::abs(mission.get_current_budget() - 100000.0) < EPS);
        REQUIRE(std::abs(mission.get_spent_budget()) < EPS);
        REQUIRE(mission.can_spend(50000));
        mission.add_budget(10000.0);
        REQUIRE(std::abs(mission.get_current_budget() - 110000.0) < EPS);
        mission.remove_budget(10000.0);
        REQUIRE(std::abs(mission.get_current_budget() - 100000.0) < EPS);
        REQUIRE(std::abs(mission.get_total_cargo() - 1000.0) < EPS);
        REQUIRE(std::abs(mission.get_current_cargo()) < EPS);
        REQUIRE(std::abs(mission.get_required_cargo() - 500.0) < EPS);
        REQUIRE(!mission.add_cargo(-50.0));
        mission.add_cargo(100.0);
        REQUIRE(std::abs(mission.get_current_cargo() - 100.0) < EPS);
        REQUIRE(!mission.remove_cargo(-50.0));
        mission.remove_cargo(10.0);
        REQUIRE(std::abs(mission.get_current_cargo() - 90.0) < EPS);
        REQUIRE(mission.get_max_convoy_ships() == 5);
        REQUIRE(mission.get_max_pirate_ships() == 5);
        REQUIRE(mission.get_base_a() == Vector());
        REQUIRE(mission.get_base_b() == Vector(25.0, 25.0));
        REQUIRE(std::abs(mission.get_base_size() - 3.0) < EPS);
        REQUIRE(mission.get_pirate_bases() == p_bases);
        REQUIRE(mission.count_pirate_bases() == 3);
        REQUIRE(mission.get_pirate_base(0) == p_bases[0]);
        REQUIRE(mission.count_active_pirate_bases() == 1);
        mission.clear_pirate_bases();
        REQUIRE(mission.count_pirate_bases() == 0);
        REQUIRE(!mission.is_completed());
        REQUIRE(!mission.is_successful());
        REQUIRE(mission.is_in_progress());
        REQUIRE(std::abs(mission.get_completion_percentage() - 9.0) < EPS);
        REQUIRE(!mission.is_goal_achieved());
        mission.set_current_budget(20000.0);
        mission.set_current_cargo(200.0);
        mission.set_is_completed(true);
        mission.set_is_successful(true);

        const Mission mission2("mission_2", Military("Барсуков", "Майор"), 100000.0, 1000.0, 50.0, 5, 5, Vector(), Vector(25.0, 25.0), 3.0, p_bases);
        const PirateBase pb2 = mission2.get_pirate_base(1);
        REQUIRE(pb2 == p_bases[1]);
    }
}

TEST_CASE("Mission mapper") {
    SECTION("From-To dto") {
        PirateBaseDTO pb_dto;
        pb_dto.trigger_distance = 5.0;
        pb_dto.ship_count = 2;
        pb_dto.is_activated = false;
        pb_dto.is_defeated = false;
        std::vector<PirateBaseDTO> p_bases_dto;
        for (size_t i = 0; i < 3; ++i) {
            pb_dto.position.x = (i + 1) * 2.0;
            pb_dto.position.y = (i + 1) * 1.5;
            if (i == 0) pb_dto.is_activated = true;
            else pb_dto.is_activated = false;
            p_bases_dto.push_back(pb_dto);
        }
        MissionDTO mission_dto;
        mission_dto.id = "mission_1";
        mission_dto.commander =Military("Барсуков", "Майор");
        mission_dto.total_budget = 100000.0;
        mission_dto.current_budget = 100000.0;
        mission_dto.total_cargo = 1000.0;
        mission_dto.current_cargo = 0.0;
        mission_dto.required_cargo_percentage = 50.0;
        mission_dto.max_convoy_ships = 5;
        mission_dto.max_pirate_ships = 5;
        mission_dto.base_a = Vector();
        mission_dto.base_b = Vector(25.0, 25.0);
        mission_dto.base_size = 3.0;
        mission_dto.pirate_bases = p_bases_dto;
        mission_dto.is_completed = false;
        mission_dto.is_successful = false;
        MissionMapper mapper_to_entity; 

        std::unique_ptr<Mission> mission = mapper_to_entity.transform(mission_dto);
        REQUIRE(mission->get_id() == "mission_1");
        REQUIRE(mission->get_commander() == Military("Барсуков", "Майор"));
        REQUIRE(std::abs(mission->get_total_budget() - 100000.0) < EPS);
        REQUIRE(std::abs(mission->get_current_budget() - 100000.0) < EPS);
        REQUIRE(std::abs(mission->get_spent_budget()) < EPS);
        REQUIRE(std::abs(mission->get_total_cargo() - 1000.0) < EPS);
        REQUIRE(std::abs(mission->get_current_cargo()) < EPS);
        REQUIRE(std::abs(mission->get_required_cargo() - 500.0) < EPS);
        REQUIRE(mission->get_max_convoy_ships() == 5);
        REQUIRE(mission->get_max_pirate_ships() == 5);
        REQUIRE(mission->get_base_a() == Vector());
        REQUIRE(mission->get_base_b() == Vector(25.0, 25.0));
        REQUIRE(std::abs(mission->get_base_size() - 3.0) < EPS);
        REQUIRE(mission->count_pirate_bases() == 3);
        REQUIRE(mission->count_active_pirate_bases() == 1);
        REQUIRE(!mission->is_completed());
        REQUIRE(!mission->is_successful());

        MissionDTOMapper mapper_to_dto;
        MissionDTO mission_dto_1 = mapper_to_dto.transform(mission.get());
        REQUIRE(mission_dto_1.id == "mission_1");
        REQUIRE(mission_dto_1.commander == Military("Барсуков", "Майор"));
        REQUIRE(std::abs(mission_dto_1.total_budget - 100000.0) < EPS);
        REQUIRE(std::abs(mission_dto_1.current_budget - 100000.0) < EPS);
        REQUIRE(std::abs(mission_dto_1.total_cargo - 1000.0) < EPS);
        REQUIRE(std::abs(mission_dto_1.current_cargo) < EPS);
        REQUIRE(std::abs(mission_dto_1.required_cargo_percentage - 50.0) < EPS);
        REQUIRE(mission_dto_1.max_convoy_ships == 5);
        REQUIRE(mission_dto_1.max_pirate_ships == 5);
        REQUIRE(mission_dto_1.base_a == Vector());
        REQUIRE(mission_dto_1.base_a == Vector(25.0, 25.0));
        REQUIRE(std::abs(mission_dto_1.base_size - 3.0) < EPS);
        REQUIRE(mission_dto_1.pirate_bases == p_bases_dto);
        REQUIRE(!mission_dto_1.is_completed);
        REQUIRE(!mission_dto_1.is_successful);
    }
}

TEST_CASE("Ship mapper") {
    SECTION("Mapper from dto manager") {
        ShipMapperManager manager;
        ShipDTO ship_dto;
        ship_dto.type = "guard";
        ship_dto.id = "A";
        ship_dto.name = "Охранник";
        ship_dto.captain = Military("Барсуков", "Майор");
        ship_dto.max_speed = 50.0;
        ship_dto.current_speed = 25.0;
        ship_dto.cost = 10000.0;
        ship_dto.position = Vector();
        ship_dto.max_health = 100.0;
        ship_dto.current_health = 75.0;
        ship_dto.is_alive = true;
        ship_dto.is_convoy = true;
        WeaponDTO weapon_dto;
        weapon_dto.type = "gun";
        weapon_dto.name = "Пушка";
        weapon_dto.damage = 10.0;
        weapon_dto.range = 10.0;
        weapon_dto.fire_rate = 5;
        weapon_dto.max_ammo = 50;
        weapon_dto.current_ammo = 50;
        weapon_dto.cost = 1000.0;
        weapon_dto.accuracy = 0.99;
        weapon_dto.explosion_radius = 0.0;
        ship_dto.weapons.insert(PlaceForWeapon::stern, weapon_dto);
        std::unique_ptr<IShip> guard_ship = manager.create_ship(ship_dto);
        REQUIRE(guard_ship->get_position() == Vector());
        REQUIRE(std::abs(guard_ship->get_speed() - 25.0) < EPS);
        REQUIRE(std::abs(guard_ship->get_max_speed() - 50.0) < EPS);
        REQUIRE(std::abs(guard_ship->get_health() - 75.0) < EPS);
        REQUIRE(std::abs(guard_ship->get_max_health() - 100.0) < EPS);
        REQUIRE(std::abs(guard_ship->get_cost() - 10000.0) < EPS);
        REQUIRE(guard_ship->is_alive());
        REQUIRE(guard_ship->is_convoy());
        REQUIRE(guard_ship->get_name() == "Охранник");
        REQUIRE(guard_ship->get_captain() == Military("Барсуков", "Майор"));
        REQUIRE(guard_ship->get_ID() == "A");

        ShipDTO transport_ship_dto;
        transport_ship_dto.type = "transport";
        transport_ship_dto.id = "B";
        transport_ship_dto.name = "Транспорт";
        transport_ship_dto.captain = Military("Барсуков", "Майор");
        transport_ship_dto.max_speed = 50.0;
        transport_ship_dto.current_speed = 25.0;
        transport_ship_dto.cost = 10000.0;
        transport_ship_dto.position = Vector();
        transport_ship_dto.max_health = 100.0;
        transport_ship_dto.current_health = 75.0;
        transport_ship_dto.is_alive = true;
        transport_ship_dto.is_convoy = true;
        transport_ship_dto.max_cargo = 50.0;
        transport_ship_dto.current_cargo = 50.0;
        transport_ship_dto.speed_reduction_factor = 0.15;
        std::unique_ptr<IShip> transport_ship = manager.create_ship(transport_ship_dto);
        REQUIRE(transport_ship->get_position() == Vector());
        REQUIRE(std::abs(transport_ship->get_speed() - 21.25) < EPS);
        REQUIRE(std::abs(transport_ship->get_max_speed() - 50.0) < EPS);
        REQUIRE(std::abs(transport_ship->get_health() - 75.0) < EPS);
        REQUIRE(std::abs(transport_ship->get_max_health() - 100.0) < EPS);
        REQUIRE(std::abs(transport_ship->get_cost() - 10000.0) < EPS);
        REQUIRE(transport_ship->is_alive());
        REQUIRE(transport_ship->is_convoy());
        REQUIRE(transport_ship->get_name() == "Транспорт");
        REQUIRE(transport_ship->get_captain() == Military("Барсуков", "Майор"));
        REQUIRE(transport_ship->get_ID() == "B");

        ShipDTO war_ship_dto;
        war_ship_dto.type = "war";
        war_ship_dto.id = "C";
        war_ship_dto.name = "Военный";
        war_ship_dto.captain = Military("Барсуков", "Майор");
        war_ship_dto.max_speed = 50.0;
        war_ship_dto.current_speed = 25.0;
        war_ship_dto.cost = 10000.0;
        war_ship_dto.position = Vector();
        war_ship_dto.max_health = 100.0;
        war_ship_dto.current_health = 75.0;
        war_ship_dto.is_alive = true;
        war_ship_dto.is_convoy = true;
        war_ship_dto.max_cargo = 50.0;
        war_ship_dto.current_cargo = 50.0;
        war_ship_dto.speed_reduction_factor = 0.15;
        weapon_dto.type = "rocket";
        weapon_dto.name = "Ракета";
        weapon_dto.explosion_radius = 1.0;
        war_ship_dto.weapons.insert(PlaceForWeapon::stern, weapon_dto);
        std::unique_ptr<IShip> war_ship = manager.create_ship(war_ship_dto);
        REQUIRE(war_ship->get_position() == Vector());
        REQUIRE(std::abs(war_ship->get_speed() - 21.25) < EPS);
        REQUIRE(std::abs(war_ship->get_max_speed() - 50.0) < EPS);
        REQUIRE(std::abs(war_ship->get_health() - 75.0) < EPS);
        REQUIRE(std::abs(war_ship->get_max_health() - 100.0) < EPS);
        REQUIRE(std::abs(war_ship->get_cost() - 10000.0) < EPS);
        REQUIRE(war_ship->is_alive());
        REQUIRE(war_ship->is_convoy());
        REQUIRE(war_ship->get_name() == "Военный");
        REQUIRE(war_ship->get_captain() == Military("Барсуков", "Майор"));
        REQUIRE(war_ship->get_ID() == "C");
    }

    SECTION("Mapper to dto manager") {
        ShipDTOMapperManager manager;
        std::unique_ptr<GuardShip> ship = std::make_unique<GuardShip>();
        std::unique_ptr<IWeapon> weapon = std::make_unique<Gun>();
        ship->set_weapon_in_place(PlaceForWeapon::bow, std::move(weapon));
        std::unique_ptr<IShip> guard_ship = std::move(ship);
        ShipDTO guard_ship_dto = manager.create_ship_dto(guard_ship.get());
        REQUIRE(guard_ship_dto.type == "guard");
        REQUIRE(guard_ship_dto.id == "");
        REQUIRE(guard_ship_dto.name == "Сторожевой корабль");
        REQUIRE(guard_ship_dto.captain == Military("", ""));
        REQUIRE(std::abs(guard_ship_dto.max_speed - 50.0) < EPS);
        REQUIRE(guard_ship_dto.current_speed < EPS);
        REQUIRE(std::abs(guard_ship_dto.cost - 10000.0) < EPS);
        REQUIRE(guard_ship_dto.position == Vector());
        REQUIRE(std::abs(guard_ship_dto.max_health - 100.0) < EPS);
        REQUIRE(std::abs(guard_ship_dto.current_health - 100.0) < EPS);
        REQUIRE(guard_ship_dto.is_alive);
        REQUIRE(guard_ship_dto.is_convoy);
        REQUIRE(guard_ship_dto.weapons.contains(PlaceForWeapon::bow));

        std::unique_ptr<WarShip> ship_1 = std::make_unique<WarShip>();
        std::unique_ptr<IWeapon> rocket = std::make_unique<Rocket>();
        ship_1->set_weapon_in_place(PlaceForWeapon::bow, std::move(rocket));
        std::unique_ptr<IShip> war_ship = std::move(ship_1);
        ShipDTO war_ship_dto = manager.create_ship_dto(war_ship.get());
        REQUIRE(war_ship_dto.type == "war");
        REQUIRE(war_ship_dto.id == "");
        REQUIRE(war_ship_dto.name == "Военный корабль");
        REQUIRE(war_ship_dto.captain == Military("", ""));
        REQUIRE(std::abs(war_ship_dto.max_speed - 40.0) < EPS);
        REQUIRE(war_ship_dto.current_speed < EPS);
        REQUIRE(std::abs(war_ship_dto.cost - 25000.0) < EPS);
        REQUIRE(war_ship_dto.position == Vector());
        REQUIRE(std::abs(war_ship_dto.max_health - 200.0) < EPS);
        REQUIRE(std::abs(war_ship_dto.current_health - 200.0) < EPS);
        REQUIRE(war_ship_dto.is_alive);
        REQUIRE(war_ship_dto.is_convoy);
        REQUIRE(war_ship_dto.current_cargo < EPS);
        REQUIRE(std::abs(war_ship_dto.max_cargo - 500) < EPS);
        REQUIRE(std::abs(war_ship_dto.speed_reduction_factor - 0.15) < EPS);
        REQUIRE(war_ship_dto.weapons.contains(PlaceForWeapon::bow));

        std::unique_ptr<TransportShip> ship_2 = std::make_unique<TransportShip>();
        std::unique_ptr<IShip> transport_ship = std::move(ship_2);
        ShipDTO transport_ship_dto = manager.create_ship_dto(transport_ship.get());
        REQUIRE(transport_ship_dto.type == "transport");
        REQUIRE(transport_ship_dto.id == "");
        REQUIRE(transport_ship_dto.name == "Транспортный корабль");
        REQUIRE(transport_ship_dto.captain == Military("", ""));
        REQUIRE(std::abs(transport_ship_dto.max_speed - 30.0) < EPS);
        REQUIRE(transport_ship_dto.current_speed < EPS);
        REQUIRE(std::abs(transport_ship_dto.cost - 15000.0) < EPS);
        REQUIRE(transport_ship_dto.position == Vector());
        REQUIRE(std::abs(transport_ship_dto.max_health - 150.0) < EPS);
        REQUIRE(std::abs(transport_ship_dto.current_health - 150.0) < EPS);
        REQUIRE(transport_ship_dto.is_alive);
        REQUIRE(transport_ship_dto.is_convoy);
        REQUIRE(transport_ship_dto.current_cargo < EPS);
        REQUIRE(std::abs(transport_ship_dto.max_cargo - 1000) < EPS);
        REQUIRE(std::abs(transport_ship_dto.speed_reduction_factor - 0.1) < EPS);
    }
}

TEST_CASE("Repository") {
    SECTION("Ship repo") {
        ShipRepository ship_repo;
        ShipFactoryManager manager;
        std::unique_ptr<IShip> guard_ship = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 100.0, 100.0, 1000.0, true, std::nullopt, Vector());
        std::unique_ptr<IShip> war_ship = manager.create_ship("war", "Титаник", Military("Барсуков", "Майор"), 150.0, 150.0, 1000.0, true, 100.0, Vector(1.0, 1.0));
        std::unique_ptr<IShip> transport_ship = manager.create_ship("transport", "Титаник", Military("Барсуков", "Майор"), 200.0, 200.0, 1000.0, true, 200.0, Vector(-1.0, -1.0));

        ship_repo.create(std::move(guard_ship));
        ship_repo.create(std::move(war_ship));
        ship_repo.create(std::move(transport_ship));
        REQUIRE(ship_repo.exists("E"));
        REQUIRE(ship_repo.exists("F"));
        REQUIRE(ship_repo.exists("G"));
        REQUIRE(ship_repo.count() == 3);

        std::unique_ptr<IShip> guard_ship_update = manager.create_ship("guard", "Титаник", Military("Голубев", "Майор"), 250.0, 250.0, 2000.0, true, std::nullopt, Vector());
        guard_ship_update->set_ID("E");
        ship_repo.update(std::move(guard_ship_update));
        IShip* guard_ship_update_ptr = ship_repo.get_ship_ptr("E");
        REQUIRE(guard_ship_update_ptr->get_captain().FIO == "Голубев");

        std::vector<IShip*> ships_in_range = ship_repo.get_ships_in_range(Vector(), 0.5);
        REQUIRE(ships_in_range.size() == 1);
        std::vector<IShip*> ships_by_type = ship_repo.get_ships_by_type("transport");
        REQUIRE(ships_by_type.size() == 1);
        std::vector<IShip*> ships_alive = ship_repo.get_alive_ships();
        REQUIRE(ships_alive.size() == 3);
        std::vector<IShip*> ships_damaged = ship_repo.get_damaged_ships();
        REQUIRE(ships_damaged.size() == 0);
        std::vector<IShip*> ships_cargo = ship_repo.get_cargo_ships();
        REQUIRE(ships_cargo.size() == 2);
        IShip* strongest_ship = ship_repo.get_strongest_ship();
        REQUIRE(strongest_ship->get_type() == "guard");
        REQUIRE(std::abs(strongest_ship->get_health() - 250.0) < EPS);
        IShip* weakest_ship = ship_repo.get_weakest_ship();
        REQUIRE(weakest_ship->get_type() == "war");
        REQUIRE(std::abs(weakest_ship->get_health() - 150.0) < EPS);
        IShip* closest_ship = ship_repo.get_closest_ship_to(Vector(0.1, -0.1));
        REQUIRE(closest_ship->get_type() == "guard");
        REQUIRE(std::abs(closest_ship->get_health() - 250) < EPS);
        IShip* fastest_ship = ship_repo.get_fastest_ship();
        REQUIRE(fastest_ship->get_type() == "guard");
        REQUIRE(std::abs(fastest_ship->get_speed() - 0.0) < EPS);

        REQUIRE(ship_repo.is_ship_alive("E"));
        REQUIRE(ship_repo.count_alive() == 3);
        REQUIRE(ship_repo.count_by_type("guard") == 1);
        REQUIRE(ship_repo.count_by_type("war") == 1);
        REQUIRE(ship_repo.count_by_type("transport") == 1);
        REQUIRE(std::abs(ship_repo.get_total_health() - 600.0) < EPS);
        REQUIRE(std::abs(ship_repo.get_average_health() - 200.0) < EPS);

        ship_repo.remove("E");
        REQUIRE(ship_repo.count() == 2);

        std::vector<IShip*> all_ship_ptrs = ship_repo.get_all_ship_ptrs();
        REQUIRE(all_ship_ptrs.size() == 2);
        REQUIRE((all_ship_ptrs[0])->get_ID() == "F");

        std::unique_ptr<IShip> guard_ship_copy = ship_repo.read("A");
        REQUIRE(guard_ship_copy == nullptr);
        guard_ship_copy = ship_repo.read("F");
        REQUIRE(guard_ship_copy->get_ID() == "F");
        std::vector<std::unique_ptr<IShip>> all_ships_copy = ship_repo.read_all();
        REQUIRE((all_ships_copy[1])->get_ID() == "G");

        ship_repo.clear();
        REQUIRE(ship_repo.count() == 0);
    }

    SECTION("Pirate repo") {
        PirateRepository pirate_repo;
        ShipFactoryManager manager;
        std::unique_ptr<IShip> guard_ship_0 = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 100.0, 100.0, 1000.0, false, std::nullopt, Vector());
        std::unique_ptr<IShip> guard_ship_1 = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 150.0, 150.0, 1000.0, false, std::nullopt, Vector(1.0, 1.0));
        std::unique_ptr<IShip> guard_ship_2 = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 200.0, 200.0, 1000.0, false, std::nullopt, Vector(-1.0, -1.0));

        REQUIRE(pirate_repo.validate_pirate_ship(guard_ship_0.get()));
        pirate_repo.create(std::move(guard_ship_0));
        pirate_repo.create(std::move(guard_ship_1));
        pirate_repo.create(std::move(guard_ship_2));
        REQUIRE(pirate_repo.exists("3"));
        REQUIRE(pirate_repo.exists("4"));
        REQUIRE(pirate_repo.exists("5"));
        REQUIRE(pirate_repo.count() == 3);

        std::unique_ptr<IShip> guard_ship_update = manager.create_ship("guard", "Титаник", Military("Голубев", "Майор"), 250.0, 250.0, 2000.0, false, std::nullopt, Vector());
        guard_ship_update->set_ID("3");
        pirate_repo.update(std::move(guard_ship_update));
        IShip* guard_ship_update_ptr = pirate_repo.get_ship_ptr("3");
        REQUIRE(guard_ship_update_ptr->get_captain().FIO == "Голубев");

        std::vector<IShip*> ships_in_range = pirate_repo.get_ships_in_range(Vector(), 0.5);
        REQUIRE(ships_in_range.size() == 1);
        std::vector<IShip*> ships_by_type = pirate_repo.get_ships_by_type("guard");
        REQUIRE(ships_by_type.size() == 3);
        std::vector<IShip*> ships_alive = pirate_repo.get_alive_ships();
        REQUIRE(ships_alive.size() == 3);
        std::vector<IShip*> ships_damaged = pirate_repo.get_damaged_ships();
        REQUIRE(ships_damaged.size() == 0);
        std::vector<IShip*> ships_cargo = pirate_repo.get_cargo_ships();
        REQUIRE(ships_cargo.size() == 0);
        IShip* strongest_ship = pirate_repo.get_strongest_ship();
        REQUIRE(strongest_ship->get_type() == "guard");
        REQUIRE(std::abs(strongest_ship->get_health() - 250.0) < EPS);
        IShip* weakest_ship = pirate_repo.get_weakest_ship();
        REQUIRE(weakest_ship->get_type() == "guard");
        REQUIRE(std::abs(weakest_ship->get_health() - 150.0) < EPS);
        IShip* closest_ship = pirate_repo.get_closest_ship_to(Vector(0.1, -0.1));
        REQUIRE(closest_ship->get_type() == "guard");
        REQUIRE(std::abs(closest_ship->get_health() - 250) < EPS);
        IShip* fastest_ship = pirate_repo.get_fastest_ship();
        REQUIRE(fastest_ship->get_type() == "guard");
        REQUIRE(std::abs(fastest_ship->get_speed() - 0.0) < EPS);

        REQUIRE(pirate_repo.is_ship_alive("3"));
        REQUIRE(pirate_repo.count_alive() == 3);
        REQUIRE(pirate_repo.count_by_type("guard") == 3);
        REQUIRE(std::abs(pirate_repo.get_total_health() - 600.0) < EPS);
        REQUIRE(std::abs(pirate_repo.get_average_health() - 200.0) < EPS);

        pirate_repo.remove("3");
        REQUIRE(pirate_repo.count() == 2);

        std::vector<IShip*> all_ship_ptrs = pirate_repo.get_all_ship_ptrs();
        REQUIRE(all_ship_ptrs.size() == 2);
        REQUIRE((all_ship_ptrs[0])->get_ID() == "4");

        std::unique_ptr<IShip> guard_ship_copy = pirate_repo.read("A");
        REQUIRE(guard_ship_copy == nullptr);
        guard_ship_copy = pirate_repo.read("4");
        REQUIRE(guard_ship_copy->get_ID() == "4");
        std::vector<std::unique_ptr<IShip>> all_ships_copy = pirate_repo.read_all();
        REQUIRE((all_ships_copy[1])->get_ID() == "5");

        pirate_repo.clear();
        REQUIRE(pirate_repo.count() == 0);
    }
}

TEST_CASE("Service") {
    SECTION("CargoService") {
        PirateBase pb;
        pb.trigger_distance = 5.0;
        pb.ship_count = 2;
        pb.is_activated = false;
        pb.is_defeated = false;
        std::vector<PirateBase> p_bases;
        for (size_t i = 0; i < 3; ++i) {
            pb.position.x = (i + 1) * 2.0;
            pb.position.y = (i + 1) * 1.5;
            p_bases.push_back(pb);
        }
        Mission mission("mission_1", Military("Барсуков", "Майор"), 100000.0, 1000.0, 50.0, 5, 5, Vector(), Vector(25.0, 25.0), 3.0, p_bases);

        ShipRepository ship_repo;
        ShipFactoryManager manager;
        std::unique_ptr<IShip> guard_ship = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 200.0, 200.0, 1000.0, true, std::nullopt, Vector()); // I
        std::unique_ptr<IShip> war_ship = manager.create_ship("war", "Титаник", Military("Барсуков", "Майор"), 150.0, 150.0, 1000.0, true, 100.0, Vector(1.0, 1.0)); // J
        std::unique_ptr<IShip> transport_ship = manager.create_ship("transport", "Титаник", Military("Барсуков", "Майор"), 200.0, 200.0, 1000.0, true, 250.0, Vector(-1.0, -1.0)); // K
        ship_repo.create(std::move(guard_ship));
        ship_repo.create(std::move(war_ship));
        ship_repo.create(std::move(transport_ship));
        
        CargoInfoVisitor visitor;
        CargoService cargo_service(mission, ship_repo);
        REQUIRE(!cargo_service.load_cargo(ship_repo.get_ship_ptr("I"), 100.0));
        IShip* w_ship = ship_repo.get_ship_ptr("J");
        REQUIRE(cargo_service.load_cargo(w_ship, 100.0));
        w_ship->accept(&visitor);
        REQUIRE(std::abs(visitor.get_current_cargo() - 100.0) < EPS); 

        REQUIRE(!cargo_service.unload_cargo(ship_repo.get_ship_ptr("I"), 100.0));
        w_ship = ship_repo.get_ship_ptr("J");
        REQUIRE(cargo_service.unload_cargo(w_ship, 100.0));
        w_ship->accept(&visitor);
        REQUIRE(std::abs(visitor.get_current_cargo()) < EPS);

        REQUIRE(!cargo_service.auto_distribute_cargo(400.0));
        REQUIRE(cargo_service.auto_distribute_cargo(200.0));

        IShip* t_ship = ship_repo.get_ship_ptr("K");
        REQUIRE(cargo_service.unload_cargo(t_ship, 200.0));
        REQUIRE(!cargo_service.distribute_evenly(400.0));
        REQUIRE(cargo_service.distribute_evenly(300.0));

        REQUIRE((cargo_service.get_total_cargo_capacity() - 350.0) < EPS);
        REQUIRE((cargo_service.get_current_cargo() - 300.0) < EPS);
        REQUIRE((cargo_service.get_available_cargo() - 50.0) < EPS);
        REQUIRE((cargo_service.calculate_optimal_speed_for_ship(t_ship, 50.0) - 185.0) < EPS);
        REQUIRE((cargo_service.calculate_convoy_speed_with_current_load() - 127.5) < EPS);
        REQUIRE(cargo_service.can_ship_carry_cargo(t_ship, 50));
        REQUIRE(!cargo_service.can_ship_carry_cargo(t_ship, 150));
        REQUIRE((cargo_service.get_ship_max_cargo(t_ship) - 250.0) < EPS);
        REQUIRE((cargo_service.get_ship_current_cargo(t_ship) - 200.0) < EPS);
        REQUIRE((cargo_service.get_ship_available_cargo(t_ship) - 50.0) < EPS);
    }

    SECTION("ID service") {
        std::string c_12 = ShipIDGenerator::generate_convoy_id();
        std::string c_13 = ShipIDGenerator::generate_convoy_id();
        std::string c_14 = ShipIDGenerator::generate_convoy_id();
        std::string c_15 = ShipIDGenerator::generate_convoy_id();
        std::string c_16 = ShipIDGenerator::generate_convoy_id();
        std::string c_17 = ShipIDGenerator::generate_convoy_id();
        std::string c_18 = ShipIDGenerator::generate_convoy_id();
        std::string c_19 = ShipIDGenerator::generate_convoy_id();
        std::string c_20 = ShipIDGenerator::generate_convoy_id();
        std::string c_21 = ShipIDGenerator::generate_convoy_id();
        std::string c_22 = ShipIDGenerator::generate_convoy_id();
        std::string c_23 = ShipIDGenerator::generate_convoy_id();
        std::string c_24 = ShipIDGenerator::generate_convoy_id();
        std::string c_25 = ShipIDGenerator::generate_convoy_id();
        std::string c_26 = ShipIDGenerator::generate_convoy_id();
        std::string c_27 = ShipIDGenerator::generate_convoy_id();
        std::string p_7 = ShipIDGenerator::generate_pirate_id();
        REQUIRE(ShipIDGenerator::is_convoy_id("AC"));
        REQUIRE(!ShipIDGenerator::is_convoy_id("A1"));
        REQUIRE(!ShipIDGenerator::is_pirate_id("2C"));
        REQUIRE(ShipIDGenerator::is_pirate_id("21"));

        REQUIRE(ShipIDGenerator::get_convoy_counter() == 27);
        REQUIRE(ShipIDGenerator::get_pirate_counter() == 7);
        ShipIDGenerator::reset_convoy();
        ShipIDGenerator::reset_pirate();
        ShipIDGenerator::reset();
        REQUIRE(ShipIDGenerator::get_convoy_counter() == 0);
        REQUIRE(ShipIDGenerator::get_pirate_counter() == 0);
    }

    SECTION("Movement service") {
        PirateBase pb;
        pb.trigger_distance = 5.0;
        pb.ship_count = 2;
        pb.is_activated = false;
        pb.is_defeated = false;
        std::vector<PirateBase> p_bases;
        for (size_t i = 0; i < 3; ++i) {
            pb.position.x = (i + 1) * 2.0;
            pb.position.y = (i + 1) * 1.5;
            p_bases.push_back(pb);
        }
        Mission mission("mission_1", Military("Барсуков", "Майор"), 100000.0, 1000.0, 50.0, 5, 5, Vector(), Vector(25.0, 25.0), 3.0, p_bases);

        ShipRepository ship_repo;
        PirateRepository pirate_repo;
        ShipFactoryManager manager;
        std::unique_ptr<IShip> guard_ship = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 200.0, 200.0, 1000.0, true, std::nullopt, Vector());
        std::unique_ptr<IShip> war_ship = manager.create_ship("war", "Титаник", Military("Барсуков", "Майор"), 150.0, 150.0, 1000.0, true, 100.0, Vector(1.0, 1.0));
        std::unique_ptr<IShip> transport_ship = manager.create_ship("transport", "Титаник", Military("Барсуков", "Майор"), 200.0, 200.0, 1000.0, true, 250.0, Vector(-1.0, -1.0));
        std::unique_ptr<IShip> guard_ship_0 = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 100.0, 100.0, 1000.0, false, std::nullopt, Vector());
        std::unique_ptr<IShip> guard_ship_1 = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 150.0, 150.0, 1000.0, false, std::nullopt, Vector(1.0, 1.0));
        std::unique_ptr<IShip> guard_ship_2 = manager.create_ship("guard", "Титаник", Military("Барсуков", "Майор"), 200.0, 200.0, 1000.0, false, std::nullopt, Vector(-1.0, -1.0));
        ship_repo.create(std::move(guard_ship));
        ship_repo.create(std::move(war_ship));
        ship_repo.create(std::move(transport_ship));
        pirate_repo.create(std::move(guard_ship_0));
        pirate_repo.create(std::move(guard_ship_1));
        pirate_repo.create(std::move(guard_ship_2));

        MovementService move_service(mission, ship_repo, pirate_repo);
        move_service.start_movement();
        for (size_t i = 0; i < 10; ++i) move_service.update(0.1);
        REQUIRE(move_service.is_moving());
        REQUIRE(std::abs(move_service.get_convoy_speed() - 150.0) < EPS);
        REQUIRE(std::abs(move_service.get_distance_to_base_B() - 100.0) < 3.0);
        REQUIRE(!move_service.has_reached_base_B());
        move_service.stop_movement();
        REQUIRE(move_service.get_convoy_target_position() == Vector(25.0, 25.0));
        move_service.reset();
    }

    SECTION("Pirate spawn service") {
        std::vector<PirateBase> p_bases;
        PirateBase pb1, pb2;
        pb1.position.x = 15.0;
        pb1.position.y = -9.0;
        pb1.trigger_distance = 10.0;
        pb1.ship_count = 2;
        pb1.is_activated = false;
        pb1.is_defeated = false;
        pb2.position.x = 35.0;
        pb2.position.y = 4.0;
        pb2.trigger_distance = 5.0;
        pb2.ship_count = 3;
        pb2.is_activated = false;
        pb2.is_defeated = false;
        p_bases.push_back(pb1); p_bases.push_back(pb2);
        Mission mission("mission_1", Military("Барсуков", "Майор"), 100000.0, 1000.0, 50.0, 5, 5, Vector(), Vector(50.0, 0.0), 5.0, p_bases);

        ShipIDGenerator::reset();
        PirateRepository pirate_repo;
        std::unique_ptr<ShipFactoryManager> factory = std::make_unique<ShipFactoryManager>();
        ShipCatalog ship_catalog(std::move(factory));
        std::unique_ptr<WeaponFactoryManager> w_factory = std::make_unique<WeaponFactoryManager>();
        WeaponCatalog weapon_catalog(std::move(w_factory));
        PirateSpawnService spawn_service(mission, pirate_repo, ship_catalog, weapon_catalog, Level::MEDIUM);
        spawn_service.update(Vector(15.0, 0.0));
        REQUIRE(pirate_repo.count_alive() == 2);
        REQUIRE(spawn_service.get_active_base_count() == 1);
        REQUIRE(spawn_service.get_defeated_base_count() == 0);
        REQUIRE(spawn_service.get_total_pirates_spawned() == 2);
        REQUIRE(!spawn_service.are_all_bases_defeated());
        spawn_service.clear_bases();
    }

    SECTION("Purchase service") {
        std::vector<PirateBase> p_bases;
        PirateBase pb1, pb2;
        pb1.position.x = 15.0;
        pb1.position.y = -9.0;
        pb1.trigger_distance = 10.0;
        pb1.ship_count = 2;
        pb1.is_activated = false;
        pb1.is_defeated = false;
        pb2.position.x = 35.0;
        pb2.position.y = 4.0;
        pb2.trigger_distance = 5.0;
        pb2.ship_count = 3;
        pb2.is_activated = false;
        pb2.is_defeated = false;
        p_bases.push_back(pb1); p_bases.push_back(pb2);
        Mission mission("mission_1", Military("Барсуков", "Майор"), 100000.0, 1000.0, 50.0, 5, 5, Vector(), Vector(50.0, 0.0), 5.0, p_bases);

        ShipIDGenerator::reset();
        PirateRepository pirate_repo;
        ShipRepository ship_repo;
        std::unique_ptr<ShipFactoryManager> factory = std::make_unique<ShipFactoryManager>();
        ShipCatalog ship_catalog(std::move(factory));
        std::unique_ptr<WeaponFactoryManager> w_factory = std::make_unique<WeaponFactoryManager>();
        WeaponCatalog weapon_catalog(std::move(w_factory));
        PurchaseService purchase_service(mission, ship_repo, pirate_repo, ship_catalog, weapon_catalog);

        purchase_service.buy_ship("transport_large", true, Vector());
        REQUIRE(std::abs(mission.get_current_budget() - 70000.0) < EPS);
        purchase_service.buy_ship("guard_fast", true, Vector(0.0, -3.0));
        REQUIRE(std::abs(mission.get_current_budget() - 55000.0) < EPS);
        purchase_service.buy_ship("guard_fast", true, Vector(0.0, 3.0));
        REQUIRE(std::abs(mission.get_current_budget() - 40000.0) < EPS);
        purchase_service.buy_ship("guard_heavy", true, Vector(3.0, 0.0));
        REQUIRE(std::abs(mission.get_current_budget() - 0.0) < EPS);
        purchase_service.sell_ship("B");
        REQUIRE(std::abs(mission.get_current_budget() - 15000.0) < EPS);

        std::unique_ptr<IWeapon> gun_light_1 = purchase_service.buy_weapon("gun_light");
        REQUIRE(std::abs(mission.get_current_budget() - 12000.0) < EPS);
        std::unique_ptr<IWeapon> gun_light_2 = purchase_service.buy_weapon("gun_light");
        REQUIRE(std::abs(mission.get_current_budget() - 9000.0) < EPS);
        std::unique_ptr<IWeapon> gun_light_3 = purchase_service.buy_weapon("gun_light");
        REQUIRE(std::abs(mission.get_current_budget() - 6000.0) < EPS);
        std::unique_ptr<IWeapon> rocket_light_1 = purchase_service.buy_weapon("rocket_light");
        REQUIRE(std::abs(mission.get_current_budget() - 0.0) < EPS);

        REQUIRE(purchase_service.install_weapon("C", PlaceForWeapon::stern, std::move(gun_light_1)));
        REQUIRE(purchase_service.install_weapon("C", PlaceForWeapon::bow, std::move(gun_light_2)));
        REQUIRE(purchase_service.install_weapon("D", PlaceForWeapon::bow, std::move(gun_light_3)));
        REQUIRE(purchase_service.install_weapon("D", PlaceForWeapon::stern, std::move(rocket_light_1)));

        REQUIRE((purchase_service.sell_weapon("C", PlaceForWeapon::bow) - 3000.0) < EPS);
        REQUIRE(std::abs(mission.get_current_budget() - 3000.0) < EPS);

        std::vector<ShipTemplate> ship_templates = purchase_service.get_available_ships();
        REQUIRE(ship_templates.size() == 8);
        std::vector<WeaponTemplate> weapon_templates = purchase_service.get_available_weapons();
        REQUIRE(weapon_templates.size() == 5);
        std::vector<ShipTemplate> ship_affordable_templates = purchase_service.get_affordable_ships();
        REQUIRE(ship_affordable_templates.size() == 0);
        std::vector<WeaponTemplate> weapon_affordable_templates = purchase_service.get_affordable_weapons();
        REQUIRE(weapon_affordable_templates.size() == 1);

        REQUIRE(!purchase_service.can_spend(5000));
        REQUIRE(std::abs(purchase_service.get_current_budget() - 3000.0) < EPS);
        REQUIRE(std::abs(purchase_service.get_initial_budget() - 100000.0) < EPS);
        REQUIRE(!purchase_service.validate_ship_purchase("transport_light"));
        REQUIRE(purchase_service.validate_weapon_purchase("gun_light"));

        REQUIRE(purchase_service.install_weapon("C", PlaceForWeapon::bow, "gun_medium"));
        REQUIRE(std::abs(mission.get_current_budget() - 3000.0) < EPS);
    } 
}

TEST_CASE("All work") {
    SECTION("") {
        {
            ShipIDGenerator::reset();
            double dt = 0.1;
            Loader loader;
            size_t convoy_count = 4, pirate_count = 4;
            auto presenter = loader.create_presenter_test(convoy_count, pirate_count);
            for (size_t i = 0; i < convoy_count; ++i) {
                presenter->purchase_ship("war_light");
            }
            presenter->auto_distribute_cargo();

            std::vector<ShipDTO> shoot_ships = presenter->get_attack_ships();
            for (size_t i = 0; i < shoot_ships.size(); ++i) {
                presenter->install_weapon(shoot_ships[i].id, PlaceForWeapon::bow, "rocket_heavy");
                presenter->install_weapon(shoot_ships[i].id, PlaceForWeapon::stern, "gun_medium");
            }

            presenter->set_pirate_strategy("closest");
            presenter->set_convoy_strategy("closest");

            presenter->start_convoy();

            std::vector<ShipDTO> convoy_ships = presenter->get_convoy_ships();
            for (size_t i = 0; i < convoy_ships.size(); ++i) {
                REQUIRE(std::abs(convoy_ships[i].current_speed - 23.8) < EPS);
                REQUIRE(std::abs(convoy_ships[i].current_health - 200.0) < EPS);
                REQUIRE(std::abs(convoy_ships[i].current_cargo - 500.0) < EPS);
            }
            REQUIRE(std::abs(convoy_ships[0].position.x) < 3);
            REQUIRE(std::abs(convoy_ships[1].position.x) < 3);
            REQUIRE(std::abs(convoy_ships[2].position.x) < 3);
            REQUIRE(std::abs(convoy_ships[3].position.x) < 3);
            REQUIRE(std::abs(convoy_ships[0].position.y) < 3);
            REQUIRE(std::abs(convoy_ships[1].position.y) < 3);
            REQUIRE(std::abs(convoy_ships[2].position.y) < 3);
            REQUIRE(std::abs(convoy_ships[3].position.y) < 3);


            while (!presenter->has_reached_destination()) {
                convoy_ships = presenter->get_convoy_ships();
                std::vector<Vector> positions_before(convoy_ships.size());
                for (size_t i = 0; i < convoy_ships.size(); ++i) {
                    positions_before[i] = convoy_ships[i].position;
                }

                presenter->move_convoy(dt);

                for (size_t i = 0; i < convoy_ships.size(); ++i) {
                    Vector temp(positions_before[i]);
                    Vector dir(1.0, 0.0);
                    temp.x += presenter->get_convoy_speed() * dt * dir.x;
                    temp.y += presenter->get_convoy_speed() * dt * dir.y;
                    REQUIRE(convoy_ships[i].position == temp);
                }
                
                size_t base_index = presenter->has_activated_base();
                if (base_index != -1) {
                    presenter->stop_convoy();

                    convoy_ships = presenter->get_convoy_ships();
                    for (size_t i = 0; i < convoy_ships.size(); ++i) {
                        REQUIRE(std::abs(convoy_ships[i].current_speed) < EPS);
                    }

                    presenter->start_pirates();

                    std::vector<ShipDTO> pirates = presenter->get_pirate_ships();
                    for (size_t i = 0; i < convoy_ships.size(); ++i) {
                        REQUIRE(std::abs(pirates[i].current_speed - 35.0) < EPS);
                    }
                    presenter->move_pirates(dt);
                    presenter->stop_pirates();

                    pirates = presenter->get_pirate_ships();
                    for (size_t i = 0; i < convoy_ships.size(); ++i) {
                        REQUIRE(std::abs(pirates[i].current_speed) < EPS);
                    }

                    while (presenter->count_alive_convoy_ships() != 0 && presenter->count_alive_pirate_ships() != 0) {
                        presenter->auto_combat_sequential();
                    }

                    if (presenter->count_alive_convoy_ships() == 0) break;
                    else {
                        presenter->update_base_status(base_index);
                    }
                }
                presenter->start_convoy();
            }
            REQUIRE(std::abs(presenter->get_convoy_center().x - 50.0) < 3.0);
            REQUIRE(std::abs(presenter->get_convoy_center().y) < 3.0);
        }

        {
            ShipIDGenerator::reset();
            double dt = 0.1;
            Loader loader;
            size_t convoy_count = 4, pirate_count = 4;
            auto presenter = loader.create_presenter_test(convoy_count, pirate_count);
            for (size_t i = 0; i < convoy_count; ++i) {
                presenter->purchase_ship("war_light");
            }
            presenter->auto_distribute_cargo();

            std::vector<ShipDTO> shoot_ships = presenter->get_attack_ships();
            for (size_t i = 0; i < shoot_ships.size(); ++i) {
                presenter->install_weapon(shoot_ships[i].id, PlaceForWeapon::bow, "rocket_heavy");
                presenter->install_weapon(shoot_ships[i].id, PlaceForWeapon::stern, "gun_medium");
            }

            presenter->set_pirate_strategy("closest");
            presenter->set_convoy_strategy("closest");

            presenter->start_convoy();

            std::vector<ShipDTO> convoy_ships = presenter->get_convoy_ships();
            for (size_t i = 0; i < convoy_ships.size(); ++i) {
                REQUIRE(std::abs(convoy_ships[i].current_speed - 23.8) < EPS);
                REQUIRE(std::abs(convoy_ships[i].current_health - 200.0) < EPS);
                REQUIRE(std::abs(convoy_ships[i].current_cargo - 500.0) < EPS);
            }
            REQUIRE(std::abs(convoy_ships[0].position.x) < 3);
            REQUIRE(std::abs(convoy_ships[1].position.x) < 3);
            REQUIRE(std::abs(convoy_ships[2].position.x) < 3);
            REQUIRE(std::abs(convoy_ships[3].position.x) < 3);
            REQUIRE(std::abs(convoy_ships[0].position.y) < 3);
            REQUIRE(std::abs(convoy_ships[1].position.y) < 3);
            REQUIRE(std::abs(convoy_ships[2].position.y) < 3);
            REQUIRE(std::abs(convoy_ships[3].position.y) < 3);

            while (!presenter->has_reached_destination()) {
                convoy_ships = presenter->get_convoy_ships();
                std::vector<Vector> positions_before(convoy_ships.size());
                for (size_t i = 0; i < convoy_ships.size(); ++i) {
                    positions_before[i] = convoy_ships[i].position;
                }

                presenter->move_convoy(dt);

                for (size_t i = 0; i < convoy_ships.size(); ++i) {
                    Vector temp(positions_before[i]);
                    Vector dir(1.0, 0.0);
                    temp.x += presenter->get_convoy_speed() * dt * dir.x;
                    temp.y += presenter->get_convoy_speed() * dt * dir.y;
                    REQUIRE(convoy_ships[i].position == temp);
                }

                size_t base_index = presenter->has_activated_base();
                if (base_index != -1) {
                    presenter->stop_convoy();
                    presenter->start_pirates();
                    presenter->move_pirates(dt);
                    presenter->stop_pirates();
                    
                    while (presenter->count_alive_convoy_ships() != 0 && presenter->count_alive_pirate_ships() != 0) {
                        presenter->auto_combat_parallel();
                        std::cout << "\n";
                    }

                    if (presenter->count_alive_convoy_ships() == 0) break;
                    else {
                        presenter->update_base_status(base_index);
                    }
                }
                presenter->start_convoy();
            }
            REQUIRE(std::abs(presenter->get_convoy_center().x - 50.0) < 3.0);
            REQUIRE(std::abs(presenter->get_convoy_center().y) < 3.0);
        }
    }
}