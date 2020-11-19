#ifndef GUI_CLUTTER_PLATFORM_H
#define GUI_CLUTTER_PLATFORM_H

// clang-format off
#include <ux/base/std_base.h>
#include <ux/base/window_interface.h>
// clang-format on

#include <clutter/clutter.h>

namespace uxdev {

/**
 * @class gui_clutter_t
 * @brief
 */
class gui_clutter_t : public platform_driver_interface_t {
public:
  using platform_driver_interface_t::child_t;
  using platform_driver_interface_t::event_t;
  using platform_driver_interface_t::index_t;

  ~gui_clutter_t();

  gui_clutter_t(int _argc, char **_argv, std::stringstream &_out,
                const std::list<u_int16_t> &coords, const std::string &title);

  int clear();
  int locate(const u_int16_t &_row, const u_int16_t &_col);
  int clip(const u_int16_t &_w, const u_int16_t &_h);
  int flush();
  int wait_for_exit(void);
  int terminate(void);
  std::size_t dispatcher_hash_key(const event_t &o);

  int argc = {};
  char **argv = {};
  std::stringstream &out;

  bool bdone = {};

  float cur_x = {};
  float cur_y = {};
  float cur_clip_w = 800;
  float cur_clip_h = 800;

  ClutterColor stage_color = {255, 255, 255, 255};
  ClutterActor *stage = {};
  std::list<ClutterActor *> elements = {};
  ClutterColor *text_color = {};
  int status = {};

private:
  static gboolean on_key_press(ClutterActor *stage, ClutterEvent *event,
                               gui_clutter_t *self);
};

} // namespace uxdev
#endif