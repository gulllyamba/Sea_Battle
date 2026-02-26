#include "PirateBaseMapper.hpp"

PirateBase PirateBaseMapper::transform(const PirateBaseDTO& base_dto) {
    PirateBase base;
    base.position = base_dto.position;
    base.trigger_distance = base_dto.trigger_distance;
    base.ship_count = base_dto.ship_count;
    base.spawned_pirate_ids = base_dto.spawned_pirate_ids;
    base.is_activated = base_dto.is_activated;
    base.is_defeated = base_dto.is_defeated;

    return base;
}