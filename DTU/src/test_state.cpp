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

  tdb.reset();
  sdb.reinit();

  const auto [ww, wh] = window::get_dims(window);

  // Background
  create_info ci{};
  tdb.add(ci, "resources/maps/test/background.png");
  tdb.add_openEXR(ci, "resources/maps/test/background_depth.exr");
  const auto bckg_handle{tdb.find("resources/maps/test/background.png").value_or(0)};
  const auto depth_handle{tdb.find("resources/maps/test/background_depth.exr").value_or(0)};
  const auto bckg_model{sprite::place(glm::vec2{0.0f}, glm::vec2{ww, wh}, 0.0f)};
  sdb.add_depth(bckg_handle, depth_handle, bckg_model);

  // Character
  ci.filtering = texture_filtering::nearest;
  tdb.add(ci, "resources/maps/test/female.png");
  const auto char_handle{tdb.find("resources/maps/test/female.png").value_or(0)};
  const auto char_model{
      sprite::place(glm::vec2{479.0f, 345.0f}, 2.0f * glm::vec2{18.0f, 70.0f}, 0.0f)};
  sdb.add(char_handle, char_model, 1.0f);

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

auto DTU::state_impl::test_state::update(GLFWwindow *window, double dt, sdb_t &sdb) noexcept
    -> std::optional<surge::error> {
#if defined(SURGE_BUILD_TYPE_Profile) && defined(SURGE_ENABLE_TRACY)
  ZoneScopedN("DTU::state_impl::test_state::update");
#endif
  using namespace surge::atom;

  const auto dtf{static_cast<float>(dt)};

  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    sdb.translate(0, dtf * glm::vec3{2.5f, 0.0f, 0.0f});
  } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    sdb.translate(0, dtf * glm::vec3{-2.5f, 0.0f, 0.0f});
  } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    sdb.translate(0, dtf * glm::vec3{0.0f, -1.0f, 0.0f});
  } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    sdb.translate(0, dtf * glm::vec3{0.0f, 1.0f, 0.0f});
  }

  // TODO: Draft
  const auto pos{sdb.get_pos(0)};

  const auto y0{226.0f};
  const auto z0{0.0f};
  const auto yf{768.0f - 32.0f};
  const auto zf{1.0f};

  auto z = [=](double y) { return z0 + (y - y0) * (z0 - zf) / (y0 - yf); };

  const auto z_feet{z(pos[1] + 140.0f)};

  const auto dz{z_feet - pos[2]};
  if (abs(dz) > 1.0e-5f) {
    sdb.translate(0, glm::vec3{0.0f, 0.0f, dz});
  }

  return {};
}

void DTU::state_impl::test_state::draw(sdb_t &sdb) noexcept { sdb.draw(); }