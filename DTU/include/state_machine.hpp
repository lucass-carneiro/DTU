#ifndef SURGE_DTU_STATE_MACHINE_HPP
#define SURGE_DTU_STATE_MACHINE_HPP

// clang-format off
#include "type_aliases.hpp"

#include "player/error_types.hpp"

#include <optional>
// clang-format on

namespace DTU {

using state_t = surge::u32;
enum state : surge::u32 { no_state, main_menu, new_game, test_state, count };

auto state_to_str(state s) noexcept -> const char *;

struct state_machine {

private:
  state state_a{no_state};
  state state_b{no_state};

  auto load_a(tdb_t &tdb) noexcept -> std::optional<surge::error>;
  auto unload_a(tdb_t &tdb) noexcept -> std::optional<surge::error>;

public:
  void push(state s) noexcept;
  auto transition(tdb_t &tdb) noexcept -> std::optional<surge::error>;
  auto destroy(tdb_t &tdb) noexcept -> std::optional<surge::error>;

  auto update(GLFWwindow *window, double dt, tdb_t &tdb, sdb_t &sdb, txd_t &txd) noexcept
      -> std::optional<surge::error>;

#ifdef SURGE_BUILD_TYPE_Debug
  [[nodiscard]] inline auto get_a() const noexcept -> state { return state_a; }
  [[nodiscard]] inline auto get_b() const noexcept -> state { return state_b; }
#endif
};

} // namespace DTU

#endif // SURGE_DTU_STATE_MACHINE_HPP