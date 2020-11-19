#ifndef UXDEV_EVENT_H
#define UXDEV_EVENT_H

namespace uxdev {

class event_t {
public:
  u_int8_t type = {};
  char *detail = {};
  char *key = {};
  unsigned int x = {}, y = {}, h = {}, w = {};

  std::size_t hash_code() {
    std::size_t value = {};
    hash_combine(value, event_name);
    return value;
  }

  enum : u_int8_t {
    key_press,
    key_release,
    motion_notify,
    button_press,
    button_release,
    scroll,
    configure
  };
};

} // namespace uxdev
#endif