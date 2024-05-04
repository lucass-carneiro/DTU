#ifndef SURGE_MODULE_DTU_DEBUG_WINDOW_HPP
#define SURGE_MODULE_DTU_DEBUG_WINDOW_HPP

// clang-format off
#include "type_aliases.hpp"
#include "state_machine.hpp"

#include "player/window.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// clang-format on

namespace DTU::debug_window {

void create(GLFWwindow *window) noexcept;
void destroy() noexcept;

void main_window(GLFWwindow *window, const tdb_t &tdb, const sdb_t &sdb, state &state_a,
                 state &state_b) noexcept;

void draw(bool &show, GLFWwindow *window, const tdb_t &tdb, const sdb_t &sdb, state &state_a,
          state &state_b) noexcept;

} // namespace DTU::debug_window

#endif // SURGE_MODULE_DTU_DEBUG_WINDOW_HPP