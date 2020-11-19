
// clang-format off
#include <ux/base/std_base.h>
#include <ux/api.h>
#include "platform.h"
// clang-format on

/**
 * @fn create_object
 * @brief
 */
extern "C" tui_ncurses_t *create_object(int _argc, char **_argv) {
  auto obj = new tui_ncurses_t();
  obj->initialize(_argc, _argv);
  return obj;
}

/**
 * @fn destroy_object
 * @brief
 */
extern "C" void destroy_object(tui_ncurses_t *object) {
  object->finalize();
  delete object;
}

/**
 * @fn tui_window_t
 * @brief initialize the ncurses library.
 * ncurses is the low level console for linux.
 */
int tui_ncurses_t::initialize(int _argc, char **_argv) {
  initscr();
  cbreak();
  noecho();

  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  if (has_colors())
    start_color();
  return EXIT_SUCCESS;
}

/**
 * @fn finalize
 * @brief
 */
int tui_ncurses_t::finalize() {
  endwin();
  return EXIT_SUCCESS;
}

/**
 * @fn clear
 * @brief blank screen
 */
int tui_ncurses_t::clear() {
  erase();
  return EXIT_SUCCESS;
}

/**
 * @fn clip()
 * @brief locate cursor row and column.
 */
int tui_ncurses_t::clip(const u_int16_t &_w, const u_int16_t &_h) {
  return EXIT_SUCCESS;
}

/**
 * @fn append_c_ctr
 * @brief adds to the out buffer. flush puts the info on the screen.
 */
int tui_ncurses_t::append_c_ctr(const char *sz) {
  const char *ptr=sz;
  while (*ptr)
    addch(*ptr++);
  refresh();
  return EXIT_SUCCESS;
}


/**
 * @fn wait_for_close
 * @brief the message process loop, wait on a key and dispatch to handler.
 * getch is setup to wait for a complete keystroke key and return it. This
 * includes the KEY_[NAME..] values as well as the regular printable
 * character keys.
 */
int tui_ncurses_t::wait_for_exit(void) {
  while (!bdone) {
    int k = getch();
    dispatch(getch());
  }
  return EXIT_SUCCESS;
}

/**
 * @fn terminate
 * @brief
 */
int tui_ncurses_t::terminate(void) {
  bdone = true;
  return EXIT_SUCCESS;
}

/**
 * @fn dispatcher_hash_key
 * @brief provides summary of event and pertinent details.
 * The pertinent details might be detected by non zero values or other
 * settings within the structure. For example, keypress event set within the
 * type. Or a narrowed keypress detection by allowing the hash to include
 * o.key.code
 */
std::size_t tui_ncurses_t::dispatcher_hash_key(const event_t &o) {
  std::size_t value = static_cast<std::size_t>(o);
  return value;
}
