#include "test_state.hpp"

#include "player/window.hpp"

#if defined(SURGE_BUILD_TYPE_Profile) && defined(SURGE_ENABLE_TRACY)
#  include <tracy/Tracy.hpp>
#  include <tracy/TracyOpenGL.hpp>
#endif

auto DTU::state_impl::test_state::load(GLFWwindow *window, tdb_t &tdb, sdb_t &sdb) noexcept
    -> std::optional<surge::error> {
#if defined(SURGE_BUILD_TYPE_Profile) && defined(SURGE_ENABLE_TRACY)
  ZoneScopedN("DTU::state_impl::test_state::load");
#endif

  using surge::atom::texture::create_info;
  using surge::renderer::texture_filtering;
  using surge::renderer::texture_wrap;
  using namespace surge;
  using namespace surge::atom;

  log_info("Loading test_state state");

  renderer::disable(renderer::capability::blend);

  tdb.reset();
  sdb.reinit();

  const auto [ww, wh] = window::get_dims(window);

  // Background texture
  create_info ci{};
  tdb.add(ci, "resources/maps/test/test.png");
  const auto handle_0{tdb.find("resources/maps/test/test.png").value_or(0)};
  const auto model_0{sprite::place(glm::vec2{0.0f}, glm::vec2{ww, wh}, 0.0f)};
  sdb.add(handle_0, model_0, 1.0f);

  // Character
  // ci.filtering = texture_filtering::nearest;
  // tdb.add(ci, "resources/maps/test/female.png");

  return {};
}
auto DTU::state_impl::test_state::unload(tdb_t &tdb, sdb_t &sdb) noexcept
    -> std::optional<surge::error> {
#if defined(SURGE_BUILD_TYPE_Profile) && defined(SURGE_ENABLE_TRACY)
  ZoneScopedN("DTU::state_impl::test_state::unload");
#endif

  log_info("Unloading test_state state");

  tdb.reset();
  sdb.reinit();

  return {};
}

auto DTU::state_impl::test_state::update(tdb_t &, sdb_t &) noexcept -> std::optional<surge::error> {
#if defined(SURGE_BUILD_TYPE_Profile) && defined(SURGE_ENABLE_TRACY)
  ZoneScopedN("DTU::state_impl::test_state::update");
#endif
  using namespace surge::atom;

  return {};
}

void DTU::state_impl::test_state::draw(sdb_t &sdb, GLuint sprite_shader) noexcept {
  sdb.draw(sprite_shader);
}