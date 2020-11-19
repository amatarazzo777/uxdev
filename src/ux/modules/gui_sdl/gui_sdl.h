#ifndef GUI_SDL_PLATFORM_H
#define GUI_SDL_PLATFORM_H
// clang-format off
#include <ux/base/std_base.h>
#include <ux/base/window_interface.h>
// clang-format on

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class widget_t {
public:
  double x = {};
  double y = {};
  double w = {};
  double h = {};

  virtual bool on_draw(SDL_Renderer *renderer) { return true; }
};

class text_area_t : public widget_t {
public:
  text_area_t();
  virtual ~text_area_t();

  // move
  text_area_t(const text_area_t &&other) noexcept;
  text_area_t &operator=(const text_area_t &&other);

  bool on_draw(SDL_Renderer *renderer) override;

public:
  double ink_width = {};
  double ink_height = {};
  bool bfast = false;
  bool fontInitialized = {};
  std::string text_string = {};
  TTF_Font *font = {};
  SDL_Texture *texture = {};
};

namespace uxdev {

/**
 * @class gui_gdkmm_t
 * @brief
 */
class gui_sdl_t : public platform_driver_interface_t, public widget_t {
public:
  using platform_driver_interface_t::child_t;
  using platform_driver_interface_t::event_t;
  using platform_driver_interface_t::index_t;

  ~gui_sdl_t();

  gui_sdl_t(int _argc, char **_argv, std::stringstream &_out,
            const std::list<u_int16_t> &coords, const std::string &title);

  int clear();
  int locate(const u_int16_t &_row, const u_int16_t &_col);
  int clip(const u_int16_t &_w, const u_int16_t &_h);
  int flush();
  int wait_for_exit(void);
  int terminate(void);
  std::size_t dispatcher_hash_key(const event_t &o);

  int argc = {};
  char **argv = {};
  std::stringstream &out;

  bool bdone = {};

  float cur_x = {};
  float cur_y = {};
  float cur_clip_w = 800;
  float cur_clip_h = 800;

  int status = {};

  SDL_Window *window = {};
  SDL_Surface *screenSurface = {};
  SDL_Renderer *renderer = {};
  std::list<std::shared_ptr<widget_t>> elements = {};
};

} // namespace uxdev
#endif