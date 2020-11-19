#ifndef TUI_PLATFORM_H
#define TUI_PLATFORM_H

// clang-format off
#include <ux/base/std_base.h>
#include <ux/base/platform_driver_interface.h>
// clang-format on

#include <curses.h>


namespace uxdev {

/**
 * @class
 * @brief tui_ncurses_t
 */
class tui_ncurses_t : public platform_driver_interface_t {
public:
  using platform_driver_interface_t::child_t;
  using platform_driver_interface_t::event_t;
  using platform_driver_interface_t::index_t;


  virtual int initialize(int _argc, char **_argv);
  virtual int finalize();

  virtual int clear();


  virtual int locate(const u_int16_t &_row, const u_int16_t &_col);

  virtual int clip(const u_int16_t &_w, const u_int16_t &_h);

  virtual int draw_text(const char *sz);


  /**
   * @fn wait_for_close
   * @brief the message process loop, wait on a key and dispatch to handler.
   * getch is setup to wait for a complete keystroke key and return it. This
   * includes the KEY_[NAME..] values as well as the regular printable
   * character keys.
   */
  virtual int wait_for_exit(void);

  virtual int terminate(void);

  virtual std::size_t dispatcher_hash_key(const event_t &o);

  int argc = {};
  char **argv = {};
  std::stringstream out;
  bool bdone = {};
};

} // namespace uxdev

#endif