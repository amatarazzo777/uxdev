#ifndef GUI_SFML_PLATFORM_H
#define GUI_SFML_PLATFORM_H

// clang-format off
#include <ux/base/std_base.h>
#include <ux/base/window_interface.h>
// clang-format on

#include <SFML/Graphics.hpp>

namespace uxdev {

/**
 * @class gui_sfml_t
 * @brief
 */
class gui_sfml_t : public platform_driver_interface_t,
                   public sf::RenderWindow {
public:
  using platform_driver_interface_t::child_t;
  using platform_driver_interface_t::event_t;
  using platform_driver_interface_t::index_t;

  gui_sfml_t() = delete;

  /**
   * @fn gui_sfml_t
   * @brief
   */
  gui_sfml_t(int _argc, char **_argv, std::stringstream &_out,
             const std::list<u_int16_t> &coords, const std::string &title);

  int clear();

  int locate(const u_int16_t &_row, const u_int16_t &_col);

  int clip(const u_int16_t &_w, const u_int16_t &_h);

  /**
   * @fn flush
   * @brief writes the output buffer to the screen.
   */
  int flush();

  int wait_for_exit(void);

  int terminate(void);

  std::size_t dispatcher_hash_key(const event_t &o);

  int argc = {};
  char **argv = {};
  std::stringstream &out;

  bool bdone = {};
  sf::Font font = {};
  float cur_x = {};
  float cur_y = {};
  std::list<sf::Text *> text_objects = {};
};

} // namespace uxdev
#endif