#include "test_state.hpp"

#include "player/window.hpp"

#if defined(SURGE_BUILD_TYPE_Profile) && defined(SURGE_ENABLE_TRACY)
#  include <tracy/Tracy.hpp>
#  include <tracy/TracyOpenGL.hpp>
#endif

auto DTU::state_impl::test_state::load(tdb_t &tdb) noexcept -> std::optional<surge::error> {
  using surge::atom::texture::create_info;
  using surge::renderer::texture_filtering;
  using surge::renderer::texture_wrap;
  using namespace surge::atom;

  log_info("Loading test_state state");

  // Background texture
  create_info ci{texture_filtering::nearest, texture_wrap::clamp_to_edge, 1, true};
  tdb.add(ci, "resources/maps/test/color0000.png");

  return {};
}
auto DTU::state_impl::test_state::unload(tdb_t &tdb) noexcept -> std::optional<surge::error> {
  log_info("Unloading test_state state");

  tdb.reset();

  return {};
}

auto DTU::state_impl::test_state::update(GLFWwindow *window, tdb_t &tdb, sdb_t &sdb) noexcept
    -> std::optional<surge::error> {
#if defined(SURGE_BUILD_TYPE_Profile) && defined(SURGE_ENABLE_TRACY)
  ZoneScopedN("DTU::main_menu::update_background_parallax()");
#endif

  using namespace surge;
  using namespace surge::atom;

  const auto [ww, wh] = window::get_dims(window);

  // Background texture
  const auto handle_0{tdb.find("resources/maps/test/color0000.png").value_or(0)};
  const auto model_0{sprite::place(glm::vec2{0.0f}, glm::vec2{ww, wh}, 0.0f)};
  sdb.add(handle_0, model_0, 1.0f);

  return {};
}