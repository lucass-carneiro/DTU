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
  create_info ci{};
  tdb.add(ci, "resources/maps/test/test.png");

  // Character
  ci.filtering = surge::renderer::texture_filtering::nearest;
  tdb.add(ci, "resources/maps/test/female.png");

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
  const auto handle_0{tdb.find("resources/maps/test/test.png").value_or(0)};
  const auto model_0{sprite::place(glm::vec2{0.0f}, glm::vec2{ww, wh}, 0.0f)};
  sdb.add(handle_0, model_0, 1.0f);

  // Character
  const auto handle_1{tdb.find("resources/maps/test/female.png").value_or(0)};
  const auto model_1{sprite::place(glm::vec2{ww / 2.0f - 100.0f, wh / 2.0f},
                                   4.0f * glm::vec2{18.0f, 70.0f}, 0.1f)};
  sdb.add(handle_1, model_1, 1.0f);

  const auto handle_2{tdb.find("resources/maps/test/female.png").value_or(0)};
  const auto model_2{sprite::place(glm::vec2{ww / 2.0f - 100.0f, wh / 3.0f},
                                   4.0f * glm::vec2{18.0f, 70.0f}, 0.05f)};
  sdb.add(handle_2, model_2, 1.0f);

  return {};
}