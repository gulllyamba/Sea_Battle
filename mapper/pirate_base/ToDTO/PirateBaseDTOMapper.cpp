#include "PirateBaseDTOMapper.hpp"

PirateBaseDTO PirateBaseDTOMapper::transform(const PirateBase& base) {
    PirateBaseDTO base_dto;
    base_dto.position = base.position;
    base_dto.trigger_distance = base.trigger_distance;
    base_dto.ship_count = base.ship_count;
    base_dto.spawned_pirate_ids = base.spawned_pirate_ids;
    base_dto.is_activated = base.is_activated;
    base_dto.is_defeated = base.is_defeated;

    return base_dto;
}