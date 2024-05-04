#include "debug_window.hpp"

#include "player/logging.hpp"

void DTU::debug_window::create(GLFWwindow *window) noexcept {
  log_info("Initializing debug window");
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  /* ImGuiIO &io =  ImGui::GetIO();
  (void)io;
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
  */

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, false);
  ImGui_ImplOpenGL3_Init("#version 460");
}

void DTU::debug_window::destroy() noexcept {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void DTU::debug_window::draw(bool &show, GLFWwindow *window, const tdb_t &tdb, state &state_a,
                             state &state_b) noexcept {
  if (show) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    main_window(window, tdb, state_a, state_b);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
}

static void tdb_window(bool *open, const DTU::tdb_t &tdb) noexcept {
  if (!ImGui::Begin("Texture Database", open, 0)) {
    // Early out if the window is collapsed, as an optimization.
    ImGui::End();
    return;
  }

  constexpr ImGuiTableFlags flags{ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersV
                                  | ImGuiTableFlags_BordersH
                                  | ImGuiTableFlags_HighlightHoveredColumn};

  if (ImGui::BeginTable("tdb_table", 4, flags)) {
    const auto &ids{tdb.get_ids()};
    const auto &handles{tdb.get_handles()};
    const auto &hashes{tdb.get_hashes()};

    ImGui::TableSetupColumn("Element");
    ImGui::TableSetupColumn("Id");
    ImGui::TableSetupColumn("Handle");
    ImGui::TableSetupColumn("Hash");
    ImGui::TableHeadersRow();

    for (surge::usize i = 0; i < tdb.size(); i++) {
      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      ImGui::Text("%lu", i);
      ImGui::TableNextColumn();

      ImGui::Text("%u", ids[i]);
      ImGui::TableNextColumn();

      ImGui::Text("%lu", handles[i]);
      ImGui::TableNextColumn();

      ImGui::Text("%lu", hashes[i]);
    }

    ImGui::EndTable();
  }

  ImGui::End();
}

static void stm_stats_window(bool *open, const DTU::state &state_a,
                             const DTU::state &state_b) noexcept {
  if (!ImGui::Begin("State Machine Status", open, 0)) {
    // Early out if the window is collapsed, as an optimization.
    ImGui::End();
    return;
  }

  constexpr ImGuiTableFlags flags{ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersV
                                  | ImGuiTableFlags_BordersH
                                  | ImGuiTableFlags_HighlightHoveredColumn};

  if (ImGui::BeginTable("stm_status_table", 3, flags)) {
    const auto a_name{DTU::state_to_str(state_a)};
    const auto b_name{DTU::state_to_str(state_b)};

    ImGui::TableSetupColumn("Slot");
    ImGui::TableSetupColumn("Id");
    ImGui::TableSetupColumn("Name");
    ImGui::TableHeadersRow();

    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGui::Text("A");
    ImGui::TableNextColumn();

    ImGui::Text("%u", state_a);
    ImGui::TableNextColumn();

    ImGui::Text("%s", a_name);
    ImGui::TableNextColumn();

    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGui::Text("B");
    ImGui::TableNextColumn();

    ImGui::Text("%u", state_b);
    ImGui::TableNextColumn();

    ImGui::Text("%s", b_name);
    ImGui::TableNextColumn();

    ImGui::EndTable();
  }

  ImGui::End();
}

static void stm_replace_window(bool *open, DTU::state &state_b) noexcept {
  using namespace DTU;

  if (!ImGui::Begin("State Machine Replace", open, 0)) {
    // Early out if the window is collapsed, as an optimization.
    ImGui::End();
    return;
  }

  constexpr ImGuiTableFlags flags{ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersV
                                  | ImGuiTableFlags_BordersH
                                  | ImGuiTableFlags_HighlightHoveredColumn};

  if (ImGui::BeginTable("state_select_table", 1, flags)) {
    ImGui::TableSetupColumn("State name");
    ImGui::TableHeadersRow();

    for (state_t i = 1; i < state::count; i++) {
      const auto s{static_cast<state>(i)};

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      if (ImGui::Button(state_to_str(s))) {
        state_b = s;
      }
      ImGui::TableNextRow();
    }

    ImGui::EndTable();
  }

  ImGui::End();
}

void DTU::debug_window::main_window(GLFWwindow *window, const tdb_t &tdb, state &state_a,
                                    state &state_b) noexcept {
  static bool tdb_window_open{false};
  static bool stm_stat_window_open{false};
  static bool stm_replace_window_open{false};

  if (ImGui::BeginMainMenuBar()) {
    // Memory menu
    if (ImGui::BeginMenu("GPU Data")) {
      if (ImGui::MenuItem("Texture Database")) {
        tdb_window_open = true;
      }

      if (ImGui::MenuItem("Sprite Database")) {
        // TODO
      }

      if (ImGui::MenuItem("Text buffer 0")) {
        // TODO
      }

      if (ImGui::MenuItem("Text buffer 1")) {
        // TODO
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("States")) {
      if (ImGui::MenuItem("Status")) {
        stm_stat_window_open = true;
      }

      if (ImGui::MenuItem("Reload")) {
        log_info("Reloading currently loaded state %s", state_to_str(state_a));
        state_b = state_a;
      }

      if (ImGui::MenuItem("Replace")) {
        stm_replace_window_open = true;
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Module")) {
      if (ImGui::MenuItem("Hot Reload")) {
        // TODO
      }

      if (ImGui::MenuItem("Quit")) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }

  if (tdb_window_open) {
    tdb_window(&tdb_window_open, tdb);
  }

  if (stm_stat_window_open) {
    stm_stats_window(&stm_stat_window_open, state_a, state_b);
  }

  if (stm_replace_window_open) {
    stm_replace_window(&stm_replace_window_open, state_b);
  }
}