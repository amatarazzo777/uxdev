#pragma once

// clang-format off
#include <ux/base/std_base.h>
#include <ux/base/window_interface.h>
// clang-format on

namespace uxdev {

/**
 * @class gui_gdkmm_t
 * @brief
 */
class gui_TEMPLATE___t : public window_interface_t<std::size_t> {
public:
  using window_interface_t::child_t;
  using window_interface_t::event_t;
  using window_interface_t::index_t;

  // gui_gtkmm_t() = delete;
  ~gui_TEMPLATE___t();

  gui_TEMPLATE___t(int _argc, char **_argv, std::stringstream &_out,
                   const std::list<u_int16_t> &coords,
                   const std::string &title);

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

  int status = {};
};

} // namespace uxdev
