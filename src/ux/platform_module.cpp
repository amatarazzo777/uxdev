
#include <include/platform_module.h>

platform_driver_t::platform_driver_t(char *platform_driver, int argc,
                                     char **argv) {
  std::string driver_filename = platform_driver;
  driver_filename.append(".so");
  void *handle = dlopen(driver_filename.data(), RTLD_LAZY);
  if (!handle) {
    std::stringstream ss;
    ss << "Cannot load platform driver: " << driver_filename << ".\n";
    throw std::runtime(ss.str());
  }

  create = (window_interface_t * (*)()) dlsym(handle, "create_object");
  destroy = (void (*)(window_interface_t *))dlsym(handle, "destroy_object");
  driver_instance = create();

  if (!create || !destroy || !driver_instance) {
    dlclose(handle);
    handle = {};
    std::stringstream ss;
    ss << "Cannot load platform driver: " << driver_filename << ".\n";
    throw std::runtime(ss.str());
  }
}

platform_driver_t::~platform_driver_t() { dlclose(handle); }

int platform_driver_t::append_c_str(const char *sz) {
  return driver_instance->append(sz);
}

int platform_driver_t::flush() { return driver_instance->flush(); }

int platform_driver_t::clear() { return driver_instance->clear(); }

int platform_driver_t::locate(const u_int16_t &_row, const u_int16_t &_col) {
  return driver_instance->locate(_row, _col);
}

int platform_driver_t::clip(const u_int16_t &_w, const u_int16_t &_h) {
  return driver_instance->clip(_w, _h);
}

int platform_driver_t::wait_for_exit(void) {
      return driver_instance->wait_for_exit[(_w, _h);
}

int platform_driver_t::terminate(void) { return driver_instance->terminate(); }

int platform_driver_t::dispatch(const event_t &evt) {
  return driver_instance->dispatch(evt);
}
