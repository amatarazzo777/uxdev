#ifndef BASE_WINDOW_INTERFACE_H
#define BASE_WINDOW_INTERFACE_H

namespace uxdev {

/**
 * @class platform_driver_interface_t
 * @brief platform drivers implement this interface within the shared library.
 * The library exposes a create_object and destroy_object which accepts the
 * command line parameters from main.
 */
class platform_driver_interface_t {
public:
  typedef element_object_t child_t;
  typedef std::string index_t;
  typedef event_t event_t;

  platform_driver_interface_t() {}
  ~platform_driver_interface_t(){};

  virtual int initialize(int argc, char **argv) = 0;
  virtual int finalize() = 0;

  virtual int draw_text(char *sztext) = 0;


  /**
   * @fn clear
   * @brief
   */
  virtual int clear() = 0;
  /**
   * @fn clear
   * @brief
   */
  virtual int locate(const u_int16_t &_row, const u_int16_t &_col) = 0;
  virtual int clip(const u_int16_t &_w, const u_int16_t &_h) = 0;

  /**
   * @fn wait_for_close
   * @brief the message process loop, wait on a key and dispatch to handler.
   * getch is setup to wait for a complete keystroke key and return it. This
   * includes the KEY_[NAME..] values as well as the regular printable
   * character keys.
   */
  virtual int wait_for_exit(void) = 0;

  virtual int terminate(void) = 0;
  virtual int dispatch(const T &) = 0;
};

} // namespace uxdev
#endif