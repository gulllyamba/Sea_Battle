#include "MissionDTOMapper.hpp"
#include "../../pirate_base/ToDTO/PirateBaseDTOMapper.hpp"
#include <iostream>

MissionDTO MissionDTOMapper::transform(const Mission* mission) {
    std::vector<PirateBaseDTO> pirate_bases;
    PirateBaseDTOMapper pirate_mapper;
    for (const auto& base : mission->get_pirate_bases()) {
        pirate_bases.push_back(pirate_mapper.transform(base));
    }

    MissionDTO mission_dto;
    mission_dto.id = mission->get_id();
    mission_dto.commander = mission->get_commander();
    mission_dto.total_budget = mission->get_total_budget();
    mission_dto.current_budget = mission->get_current_budget();
    mission_dto.total_cargo = mission->get_total_cargo();
    mission_dto.current_cargo = mission->get_current_cargo();
    mission_dto.required_cargo_percentage = mission->get_required_cargo() / mission->get_total_cargo() * 100;
    mission_dto.max_convoy_ships = mission->get_max_convoy_ships();
    mission_dto.max_pirate_ships = mission->get_max_pirate_ships();
    mission_dto.base_a = mission->get_base_a();
    mission_dto.base_b = mission->get_base_b();
    mission_dto.base_size = mission->get_base_size();
    mission_dto.pirate_bases = pirate_bases;
    mission_dto.is_completed = mission->is_completed();
    mission_dto.is_successful = mission->is_successful();

    return mission_dto;
}