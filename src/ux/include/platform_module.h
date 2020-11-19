#ifndef BASE_PLATFORM_H
#define BASE_PLATFORM_H

namespace uxdev {
class platform_module_t : module_abstract_t {
public:
  platform_module_t() = delete;
  platform_module_t(const char *platform_driver, int _argc, char **_argv);
  ~platform_module_t();

  window_interface_t &new_surface(std::string title) {
    surface_objects.emplace_back(create());
    return surface_objects.emplace_back(create());
  }

  int draw_text(char *sz);
  int clear();
  int locate(const u_int16_t &_row, const u_int16_t &_col);
  int clip(const u_int16_t &_w, const u_int16_t &_h);
  int wait_for_exit(void);
  int terminate(void);
  int dispatch(const T &);

  std::list<std::shared_ptr<window_interface_t>> surface_objects = {};

private:
  void *handle = {};
  window_interface_t *driver_instance = {};
  window_interface_t *(*create)() = {};
  void (*destroy)(window_interface_t *) = {};
  int _argc = {};
  char **argv = {};
};

} // namespace uxdev
#endif