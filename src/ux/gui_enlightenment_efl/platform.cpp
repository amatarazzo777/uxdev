// clang-format off
#include <ux/base/std_base.h>
#include <ux/api.h>
// clang-format on
#include "platform.h"

uxdev::gui_enlightenment_efl_t::~gui_enlightenment_efl_t() {}

uxdev::gui_enlightenment_efl_t::gui_enlightenment_efl_t(
    int _argc, char **_argv, std::stringstream &_out,
    const std::list<u_int16_t> &coords, const std::string &title)
    : argc(_argc), argv(_argv), out(_out) {}

int uxdev::gui_enlightenment_efl_t::clear() { return EXIT_SUCCESS; }
int uxdev::gui_enlightenment_efl_t::locate(const u_int16_t &_row,
                                           const u_int16_t &_col) {
  return EXIT_SUCCESS;
}
int uxdev::gui_enlightenment_efl_t::clip(const u_int16_t &_w,
                                         const u_int16_t &_h) {
  return EXIT_SUCCESS;
}
int uxdev::gui_enlightenment_efl_t::flush() { return EXIT_SUCCESS; }
int uxdev::gui_enlightenment_efl_t::wait_for_exit(void) { return EXIT_SUCCESS; }
int uxdev::gui_enlightenment_efl_t::terminate(void) { return EXIT_SUCCESS; }
std::size_t
uxdev::gui_enlightenment_efl_t::dispatcher_hash_key(const event_t &o) {
  return 0;
}
