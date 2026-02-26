#include "MissionMapper.hpp"
#include "../../pirate_base/FromDTO/PirateBaseMapper.hpp"

std::unique_ptr<Mission> MissionMapper::transform(const MissionDTO& mission_dto) {
    std::vector<PirateBase> pirate_bases;
    PirateBaseMapper pirate_mapper;
    for (const auto& base : mission_dto.pirate_bases) {
        pirate_bases.push_back(pirate_mapper.transform(base));
    }

    std::unique_ptr<Mission> mission = std::make_unique<Mission>(
        mission_dto.id,
        mission_dto.commander,
        mission_dto.total_budget,
        mission_dto.total_cargo,
        mission_dto.required_cargo_percentage,
        mission_dto.max_convoy_ships,
        mission_dto.max_pirate_ships,
        mission_dto.base_a,
        mission_dto.base_b,
        mission_dto.base_size,
        pirate_bases
    );
    mission->set_current_budget(mission_dto.current_budget);
    mission->set_current_cargo(mission_dto.current_cargo);
    mission->set_is_completed(mission_dto.is_completed);
    mission->set_is_successful(mission_dto.is_successful);

    return mission;
}