#ifndef SURGE_DTU_STATE_MACHINE_HPP
#define SURGE_DTU_STATE_MACHINE_HPP

#include "player/integer_types.hpp"

namespace DTU {

using state_t = surge::u32;
enum state : surge::u32 { no_state, main_menu, new_game, test_state, count };

auto state_to_str(state s) noexcept -> const char *;

} // namespace DTU

#endif // SURGE_DTU_STATE_MACHINE_HPP