// clang-format off
#include <ux/base/std_base.h>
#include <ux/api.h>
// clang-format on
#include <ux/gui_clutter/platform.h>

uxdev::gui_clutter_t::~gui_clutter_t() {}

uxdev::gui_clutter_t::gui_clutter_t(int _argc, char **_argv,
                                    std::stringstream &_out,
                                    const std::list<u_int16_t> &coords,
                                    const std::string &title)
    : argc(_argc), argv(_argv), out(_out) {
  auto ret = clutter_init(&argc, &argv);
  if (ret != CLUTTER_INIT_SUCCESS) {
    std::stringstream ss;
    ss << "could not initialize clutter: " << ret << "\n";
    throw std::runtime_error(ss.str());
  }
  stage = clutter_stage_new();

  clutter_actor_set_size(stage, 512, 512);
  clutter_actor_set_background_color(stage, &stage_color);
  clutter_stage_set_title((ClutterStage *)stage, title.data());
  clutter_stage_set_user_resizable(CLUTTER_STAGE(stage), true);
  clutter_actor_show(stage);
  text_color = clutter_color_new(0, 0, 0, 255);

  g_signal_connect(stage, "destroy", G_CALLBACK(clutter_main_quit), NULL);
  g_signal_connect(stage, "key-press-event", G_CALLBACK(on_key_press), this);
}

/**
 * @fn on_key_press
 * @brief keystroke
 */
gboolean uxdev::gui_clutter_t::on_key_press(ClutterActor *stage,
                                            ClutterEvent *event,
                                            gui_clutter_t *self) {
  self->dispatch(*event);

  return CLUTTER_EVENT_PROPAGATE;
}

int uxdev::gui_clutter_t::clear() { return EXIT_SUCCESS; }

int uxdev::gui_clutter_t::locate(const u_int16_t &_row, const u_int16_t &_col) {
  cur_x = static_cast<float>(_row);
  cur_y = static_cast<float>(_col);
  return EXIT_SUCCESS;
}
int uxdev::gui_clutter_t::clip(const u_int16_t &_w, const u_int16_t &_h) {
  cur_clip_w = static_cast<float>(_w);
  cur_clip_h = static_cast<float>(_h);
  return EXIT_SUCCESS;
}
int uxdev::gui_clutter_t::flush() {
  std::string s = out.str();
  auto ptr = elements.emplace_back(
      clutter_text_new_full("20px", s.data(), text_color));
  clutter_actor_set_position(ptr, cur_x, cur_y);
  clutter_actor_set_opacity(ptr, 0);

  clutter_actor_set_reactive(ptr, true);

  clutter_actor_add_child(stage, ptr);
  clutter_actor_show(ptr);

  gfloat ink_w{}, ink_h{};
  clutter_actor_get_size(ptr, &ink_w, &ink_h);
  cur_x += ink_w;

  clutter_actor_save_easing_state(ptr);
  clutter_actor_set_easing_mode(ptr, CLUTTER_EASE_OUT_BOUNCE);
  clutter_actor_set_easing_duration(ptr, 500);

  clutter_actor_set_opacity(ptr, 255);
  clutter_actor_restore_easing_state(ptr);

  return EXIT_SUCCESS;
}

int uxdev::gui_clutter_t::wait_for_exit(void) {
  clutter_main();
  return EXIT_SUCCESS;
}

int uxdev::gui_clutter_t::terminate(void) {
  clutter_color_free(text_color);
  clutter_main_quit();
  return EXIT_SUCCESS;
}

std::size_t uxdev::gui_clutter_t::dispatcher_hash_key(const event_t &o) {
  return static_cast<std::size_t>(o.type);
}
