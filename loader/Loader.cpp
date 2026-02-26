#include "Loader.hpp"
#include "../visitor/cargo/CargoInfoVisitor.hpp"

std::unique_ptr<Mission> Loader::create_mission_test(size_t convoy_count, size_t pirate_count) {
    Military commander{"Иванов", "Полковник"};
    Vector base_a{0, 0};
    Vector base_b{50, 0};
    
    PirateBase pb;
    pb.position.x = 15.0;
    pb.position.y = -9.0;
    pb.trigger_distance = 12.0;
    pb.ship_count = pirate_count;
    pb.is_activated = false;
    pb.is_defeated = false;
    std::vector<PirateBase> pirate_bases;
    pirate_bases.push_back(pb);

    
    return std::make_unique<Mission>(
        "mission_001",
        commander,
        std::numeric_limits<double>::max(),
        2000.0, 
        75.0,
        convoy_count,
        pirate_count,
        base_a,
        base_b,
        3.0,
        pirate_bases
    );
}

std::unique_ptr<Presenter> Loader::create_presenter_test(size_t convoy_count, size_t pirate_count) {
    mission_ = create_mission_test(convoy_count, pirate_count);
    convoy_repo_ = std::make_unique<ShipRepository>();
    pirate_repo_ = std::make_unique<PirateRepository>();

    ship_catalog_ = std::make_unique<ShipCatalog>(std::make_unique<ShipFactoryManager>());
    weapon_catalog_ = std::make_unique<WeaponCatalog>(std::make_unique<WeaponFactoryManager>());
    
    movement_service_ = std::make_unique<MovementService>(*mission_, *convoy_repo_, *pirate_repo_);
    damage_service_ = std::make_unique<DamageService>();
    combat_service_ = std::make_unique<CombatService>(*mission_, *convoy_repo_, *pirate_repo_, *damage_service_);
    purchase_service_ = std::make_unique<PurchaseService>(*mission_, *convoy_repo_, *pirate_repo_, *ship_catalog_, *weapon_catalog_);
    
    cargo_service_ = std::make_unique<CargoService>(*mission_, *convoy_repo_);
    pirate_spawn_service_ = std::make_unique<PirateSpawnService>(*mission_, *pirate_repo_, *ship_catalog_, *weapon_catalog_, Level::EAZY);
    
    // устанавливаем seed, чтобы позиции кораблей были одинаковыми при повторе миссии
    pirate_spawn_service_->set_seed(12345);

    mission_dto_mapper_ = std::make_unique<MissionDTOMapper>();
    mission_mapper_ = std::make_unique<MissionMapper>();
    ship_dto_mapper_manager_ = std::make_unique<ShipDTOMapperManager>();
    ship_mapper_manager_ = std::make_unique<ShipMapperManager>();
    pirate_base_dto_mapper_ = std::make_unique<PirateBaseDTOMapper>();
    pirate_base_mapper_ = std::make_unique<PirateBaseMapper>();
    
    state_service_ = std::make_unique<YamlStateService>(
        *mission_,
        *convoy_repo_,
        *pirate_repo_,
        *mission_dto_mapper_,
        *mission_mapper_,
        *ship_dto_mapper_manager_,
        *ship_mapper_manager_
    );

    return std::make_unique<Presenter>(
        *mission_,
        *ship_catalog_,
        *weapon_catalog_,
        *cargo_service_,
        *combat_service_,
        *movement_service_,
        *pirate_spawn_service_,
        *purchase_service_,
        *state_service_,
        *mission_dto_mapper_,
        *ship_dto_mapper_manager_,
        *pirate_base_dto_mapper_
    );
}

std::unique_ptr<Presenter> Loader::create_default_presenter() {
    mission_ = std::make_unique<Mission>(
        "temp_id", 
        Military(), 
        0.0, 0.0, 0.0, 0, 0, 
        Vector(), Vector(), 
        0.0, 
        std::vector<PirateBase>()
    );
    convoy_repo_ = std::make_unique<ShipRepository>();
    pirate_repo_ = std::make_unique<PirateRepository>();

    mission_dto_mapper_ = std::make_unique<MissionDTOMapper>();
    mission_mapper_ = std::make_unique<MissionMapper>();
    ship_dto_mapper_manager_ = std::make_unique<ShipDTOMapperManager>();
    ship_mapper_manager_ = std::make_unique<ShipMapperManager>();
    pirate_base_dto_mapper_ = std::make_unique<PirateBaseDTOMapper>();
    pirate_base_mapper_ = std::make_unique<PirateBaseMapper>();
    
    state_service_ = std::make_unique<YamlStateService>(
        *mission_,
        *convoy_repo_,
        *pirate_repo_,
        *mission_dto_mapper_,
        *mission_mapper_,
        *ship_dto_mapper_manager_,
        *ship_mapper_manager_
    );
    state_service_->load_mission("mission.yaml");

    ship_catalog_ = std::make_unique<ShipCatalog>(std::make_unique<ShipFactoryManager>());
    weapon_catalog_ = std::make_unique<WeaponCatalog>(std::make_unique<WeaponFactoryManager>());
    
    movement_service_ = std::make_unique<MovementService>(*mission_, *convoy_repo_, *pirate_repo_);
    damage_service_ = std::make_unique<DamageService>();
    combat_service_ = std::make_unique<CombatService>(*mission_, *convoy_repo_, *pirate_repo_, *damage_service_);
    purchase_service_ = std::make_unique<PurchaseService>(*mission_, *convoy_repo_, *pirate_repo_, *ship_catalog_, *weapon_catalog_);
    
    cargo_service_ = std::make_unique<CargoService>(*mission_, *convoy_repo_);
    pirate_spawn_service_ = std::make_unique<PirateSpawnService>(*mission_, *pirate_repo_, *ship_catalog_, *weapon_catalog_, Level::EAZY);

    return std::make_unique<Presenter>(
        *mission_,
        *ship_catalog_,
        *weapon_catalog_,
        *cargo_service_,
        *combat_service_,
        *movement_service_,
        *pirate_spawn_service_,
        *purchase_service_,
        *state_service_,
        *mission_dto_mapper_,
        *ship_dto_mapper_manager_,
        *pirate_base_dto_mapper_
    );
}
