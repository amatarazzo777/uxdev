#include <ux/base/std_base.h>
#include "window.h"

window_t &window_t::operator()(const u_int16_t &_row, const u_int16_t &_col) {
  row = _row;
  col = _col;
  cur_x = _row;
  cur_y = _col;
  driver_instance->locate(_row, _col);
  return *this;
}

window_t &window_t::operator()(const u_int16_t &_row, const u_int16_t &_col,
                               const u_int16_t &_w, const u_int16_t &_h) {
  row = _row;
  col = _col;
  cur_x = _row;
  cur_y = _col;
  driver_instance->locate(_row, _col);
  driver_instance->clip(_w, _h);
  return *this;
}

window_t &operator()(const std::string &operation) {
  std::list<std::string> params = {};

  return *this;
}

window_t &window_t::operator()(const std::string &event_description,
                               event_handler_t &evt_handler) {
  driver_instance->listen(event_description, evt_handler);
}

window_t &window_t::operator()(
    const std::list<std::pair<std::string, event_handler_t>> &events) {
  for (auto n : events)
    operator()(n.first, n.second);
  return *this;
}
