#include "state_machine.hpp"

auto DTU::state_to_str(DTU::state s) noexcept -> const char * {
  using DTU::state;

  switch (s) {
  case state::no_state:
    return "no state";

  case state::main_menu:
    return "main menu";

  case state::new_game:
    return "new game";

  case state::test_state:
    return "test state";

  case state::count:
    return "count";

  default:
    return "unknown state";
  }
}