// clang-format off
#include <ux/base/std_base.h>
#include <ux/base/window_interface.h>
// clang-format on

#include <SFML/Graphics.hpp>

namespace uxdev {

gui_sfml_t::gui_sfml_t(int _argc, char **_argv, std::stringstream &_out,
                       const std::list<u_int16_t> &coords,
                       const std::string &title)
    : argc(_argc), argv(_argv), out(_out) {
  font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeMono.ttf");
  u_int16_t w = {}, h{}, x{}, y{};
  auto it = coords.begin();

  if (coords.size() == 0 || (coords.size() != 2 && coords.size() != 4)) {
    w = sf::VideoMode::getDesktopMode().width * .6;
    h = sf::VideoMode::getDesktopMode().height * .5;
    x = sf::VideoMode::getDesktopMode().width / 2 - w / 2;
    y = sf::VideoMode::getDesktopMode().height / 2 - h / 2;

  } else if (coords.size() == 2) {
    auto it = coords.begin();
    w = *it++;
    h = *it++;
    x = sf::VideoMode::getDesktopMode().width / 2 - w / 2;
    y = sf::VideoMode::getDesktopMode().height / 2 - h / 2;

  } else if (coords.size() == 2) {
    x = *it++;
    y = *it++;
    w = *it++;
    h = *it++;
  }

  create(sf::VideoMode(w, h), title);
  setPosition({x, y});
  setVerticalSyncEnabled(true);
  setTitle(title);
  clear();
}

/**
 * @fn clear
 * @brief
 */
int gui_sfml_t::clear() {
  sf::RenderWindow::clear(sf::Color(255, 255, 255, 255));
  text_objects.clear();
  display();
  return EXIT_SUCCESS;
}

/**
 * @fn clear
 * @brief
 */
int gui_sfml_t::locate(const u_int16_t &_row, const u_int16_t &_col) {
  cur_x = static_cast<float>(_row);
  cur_y = static_cast<float>(_col);
  return EXIT_SUCCESS;
}

int gui_sfml_t::clip(const u_int16_t &_w, const u_int16_t &_h) {
  return EXIT_SUCCESS;
}

/**
 * @fn flush
 * @brief writes the output buffer to the screen.
 */
int gui_sfml_t::flush() {
  sf::String s = out.str();
  sf::Text *text = new sf::Text();
  text_objects.push_back(text);

  // select the font
  text->setFont(font); // font is a sf::Font

  // set the string to display
  text->setString(s);
  text->setPosition(cur_x, cur_y);
  text->setFillColor(sf::Color(0, 255, 0, 255));

  sf::RenderWindow::clear(sf::Color(255, 255, 255, 255));
  for (auto o : text_objects)
    draw(*o);
  display();

  auto v = text->findCharacterPos(s.getSize());
  cur_x = v.x;
  cur_y = v.y;

  return EXIT_SUCCESS;
}

/**
 * @fn wait_for_close()
 * @brief
 */
int gui_sfml_t::wait_for_exit(void) {
  while (isOpen()) {
    sf::Event event;
    while (waitEvent(event)) {
      if (event.type == sf::Event::Closed) {
        close();
      } else {
        dispatch(event);
      }
    }
  }

  return EXIT_SUCCESS;
}

/**
 * @fn terminate
 * @brief
 */
int gui_sfml_t::terminate(void) {
  bdone = true;
  close();
  return EXIT_SUCCESS;
}

/**
 * @fn dispatcher_hash_key
 * @brief provides summary of event and pertinent details.
 * The pertinent details might be detected by non zero values or other
 * settings within the structure. For example, keypress event set within the
 * type. Or a narrowed keypress detection by allowing the hash to include
 * o.key.code
 */
std::size_t gui_sfml_t::dispatcher_hash_key(const event_t &o) {
  std::size_t value = static_cast<std::size_t>(o.type);
  return value;
}
