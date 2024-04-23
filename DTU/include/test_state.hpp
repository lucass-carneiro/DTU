#ifndef DTU_STATE_TEST_STATE_HPP
#define DTU_STATE_TEST_STATE_HPP

// clang-format off
#include "type_aliases.hpp"

#include "player/error_types.hpp"

#include <optional>
// clang-format on

namespace DTU::state_impl::test_state {

auto load(tdb_t &tdb) noexcept -> std::optional<surge::error>;
auto unload(tdb_t &tdb) noexcept -> std::optional<surge::error>;

auto update(GLFWwindow *window, tdb_t &tdb, sdb_t &sdb) noexcept -> std::optional<surge::error>;

} // namespace DTU::state_impl::test_state

#endif // DTU_STATE_TEST_STATE_HPP