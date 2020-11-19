#include "platform.h"

uxdev::gui_TEMPLATE___t::~gui_TEMPLATE___t() {}

uxdev::gui_TEMPLATE___t::gui_TEMPLATE___t(int _argc, char **_argv,
                                          std::stringstream &_out,
                                          const std::list<u_int16_t> &coords,
                                          const std::string &title)
    : argc(_argc), argv(_argv), out(_out) {}

int uxdev::gui_TEMPLATE___t::clear() { return EXIT_SUCCESS; }
int uxdev::gui_TEMPLATE___t::locate(const u_int16_t &_row,
                                    const u_int16_t &_col) {
  return EXIT_SUCCESS;
}
int uxdev::gui_TEMPLATE___t::clip(const u_int16_t &_w, const u_int16_t &_h) {
  return EXIT_SUCCESS;
}
int uxdev::gui_TEMPLATE___t::flush() { return EXIT_SUCCESS; }
int uxdev::gui_TEMPLATE___t::wait_for_exit(void) { return EXIT_SUCCESS; }
int uxdev::gui_TEMPLATE___t::terminate(void) { return EXIT_SUCCESS; }

// events are the same class or type as the interface base
// this provides programming using the coverage and event system of the
// base. The syntax provides explicit nature of usage within the platform
// interface base and technology. After compilation, with the use of
// exported functions within the executable, it is hoped that upstream and
// downstream operation is possible. event translation between the system
// will be necessary,
std::size_t uxdev::gui_TEMPLATE___t::dispatcher_hash_key(const event_t &o) {
  return 0;
}
