#pragma once

namespace uxdev {
class window_t : public data_layer_t, public document_management_t {
public:
  using data_layer_t::operator=;
  using data_layer_t::operator<<;
  using data_layer_t::operator+=;
  using document_management_t::operator[];
  using typename document_management_t::index_t;

  template <typename T> window_t &operator<<(const T &a) {
    data_layer_t::operator<<(a);
    if (driver_instance->draw_text(out.str().data()) == EXIT_SUCCESS)
      out.str(std::string());

    return *this;
  }

  template <typename T> window_t &operator<<(const char *sz) {
    data_layer_t::operator<<(sz);
    if (driver_instance->draw_text(out.str().data()) == EXIT_SUCCESS)
      out.str(std::string());

    return *this;
  }

  /**
   * @fn operator()
   * @brief locate cursor row and column.
   */

  window_t &operator()(const u_int16_t &_row, const u_int16_t &_col);

  window_t &operator()(const u_int16_t &_row, const u_int16_t &_col,
                       const u_int16_t &_w, const u_int16_t &_h);

  window_t &operator()(const std::string &operation);

  window_t &operator()(const std::string &event_name,
                       fn_listen_t &evt_handle);

  window_t &operator()(const std::string &event_name, const std::string &detail,
                       fn_listen_t &evt_handle);

  window_t &operator()(const std::list<std::string, fn_listen_t> events);

private:
  int dispatch(const event_t &evt) {
    return event_dispatcher_t<typename T::event_t>::dispatch(evt);
  }
  std::size_t dispatcher_hash_key(const typename T::event_t &o) {
    return driver_instance->dispatcher_hash_key(o);
  }

  u_int16_t line_offset = {};
  u_int16_t cur_x = {};
  u_int16_t cur_y = {};
  u_int16_t row = {};
  u_int16_t col = {};
  std::list<index_t> field_tab_order = {};

  bool bdone = {};
  platform_driver_t *driver_instance = {};
};
} // namespace uxdev
