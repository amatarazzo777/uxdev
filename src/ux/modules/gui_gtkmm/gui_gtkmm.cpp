
// clang-format off
#include <ux/base/std_base.h>
#include <ux/api.h>
#include "platform.h"
// clang-format on

uxdev::gui_gtkmm_t::~gui_gtkmm_t() {}

uxdev::gui_gtkmm_t::gui_gtkmm_t(int _argc, char **_argv,
                                std::stringstream &_out,
                                const std::list<u_int16_t> &coords,
                                const std::string &title)
    : argc(_argc), argv(_argv), out(_out) {

  u_int16_t w = {}, h{}, x{}, y{};
  auto it = coords.begin();

  if (coords.size() == 0 || (coords.size() != 2 && coords.size() != 4)) {
    w = 1300 * .6;
    h = 800 * .5;
    x = 1300 / 2 - w / 2;
    y = 800 / 2 - h / 2;

  } else if (coords.size() == 2) {
    auto it = coords.begin();
    w = *it++;
    h = *it++;
    x = 1300 / 2 - w / 2;
    y = 800 / 2 - h / 2;

  } else if (coords.size() == 2) {
    x = *it++;
    y = *it++;
    w = *it++;
    h = *it++;
  }

  this->move(x, y);
  this->set_default_size(w, h);
  this->set_title(title);
  this->activate();

  container_fixed = Gtk::manage(new Gtk::Fixed());
  add(*container_fixed);
  container_fixed->show();

  add_events(Gdk::KEY_PRESS_MASK);
  add_events(Gdk::KEY_RELEASE_MASK);

  signal_key_press_event().connect(
      sigc::mem_fun(*this, &gui_gtkmm_t::window_key_press));

  // Called after the default event signal handler.
  signal_key_release_event().connect(
      sigc::mem_fun(*this, &gui_gtkmm_t::window_key_release));
}

bool uxdev::gui_gtkmm_t::window_key_release(GdkEventKey *event) {
  dispatch(*event);
  return false;
}

bool uxdev::gui_gtkmm_t::window_key_press(GdkEventKey *event) {
  dispatch(*event);
  return false;
}

/**
 * @fn clear
 * @brief
 */
int uxdev::gui_gtkmm_t::clear() {
  this->clear();
  return EXIT_SUCCESS;
}

/**
 * @fn flush
 * @brief writes the output buffer to the screen.
 */
int uxdev::gui_gtkmm_t::flush() {
  auto text = Gtk::manage(new text_area_t{});

  text->text_string = out.str();
  text->x = cur_x;
  text->y = cur_y;

  text->set_size_request((int)cur_clip_w, (int)cur_clip_h);
  container_fixed->put(*text, cur_x, cur_y);
  text->show();

  return EXIT_SUCCESS;
}

/**
 * @fn locate
 * @brief
 */
int uxdev::gui_gtkmm_t::locate(const u_int16_t &_row, const u_int16_t &_col) {
  cur_x = static_cast<float>(_row);
  cur_y = static_cast<float>(_col);
  return EXIT_SUCCESS;
}

/**
 * @fn clip
 * @brief
 */
int uxdev::gui_gtkmm_t::clip(const u_int16_t &_w, const u_int16_t &_h) {
  cur_clip_w = static_cast<float>(_w);
  cur_clip_h = static_cast<float>(_h);
  return EXIT_SUCCESS;
}

/**
 * @fn wait_for_close()
 * @brief
 */
int uxdev::gui_gtkmm_t::wait_for_exit(void) { return EXIT_SUCCESS; }

/**
 * @fn terminate
 * @brief
 */
int uxdev::gui_gtkmm_t::terminate(void) {
  bdone = true;

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
std::size_t uxdev::gui_gtkmm_t::dispatcher_hash_key(const event_t &o) {
  std::size_t value = static_cast<std::size_t>(o.type);
  return value;
}

/**
 * @fn text_area_t
 * @brief move constructor
 */
uxdev::text_area_t::text_area_t(const text_area_t &&other) noexcept
    : fontInitialized(other.fontInitialized), text_string(other.text_string),
      font(other.font), layout(other.layout) {}

/**
 * @fn text_area_t
 * @brief move constructor
 */
uxdev::text_area_t &uxdev::text_area_t::operator=(const text_area_t &&other) {
  fontInitialized = other.fontInitialized;
  text_string = other.text_string;
  font = other.font;
  layout = other.layout;
  return *this;
}

/**
 * @fn text_area_t::on_draw
 * @details
 *
 */
bool uxdev::text_area_t::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
  // Draw a white rectangle
  cr->set_source_rgb(1.0, 1.0, 1.0);
  draw_rectangle(cr);

  cr->set_source_rgb(0.0, 0.0, 0.0);
  draw_text(cr);
  return true;
}

void uxdev::text_area_t::draw_rectangle(
    const Cairo::RefPtr<Cairo::Context> &cr) {
  Gtk::Allocation allocation = get_allocation();
  cr->rectangle(allocation.get_x(), allocation.get_y(), allocation.get_width(),
                allocation.get_height());
  cr->fill();
}

void uxdev::text_area_t::draw_text(const Cairo::RefPtr<Cairo::Context> &cr) {
  // Pango::FontDescription font;
  Gtk::Allocation allocation = get_allocation();

  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_BOLD);

  if (!layout)
    layout = Pango::Layout::create(cr);

  layout->set_font_description(font);
  layout->set_text(text_string);
  layout->set_width(allocation.get_width() * Pango::SCALE);
  layout->set_height(allocation.get_height() * Pango::SCALE);

  // get the text dimensions (it updates the variables -- by reference)
  // layout->get_pixel_size(text_width, text_height);

  // Position the text
  cr->move_to(allocation.get_x(), allocation.get_y());
  layout->show_in_cairo_context(cr);
}
