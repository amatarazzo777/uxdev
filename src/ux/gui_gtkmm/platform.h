#ifndef GUI_GTKMM_PLATFORM_H
#define GUI_GTKMM_PLATFORM_H

// clang-format off
#include <ux/base/std_base.h>
#include <ux/base/window_interface.h>
// clang-format on

//#include <gtkmm.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/fixed.h>

namespace uxdev {

class text_area_t : public Gtk::DrawingArea {
public:
  text_area_t() {}
  virtual ~text_area_t() {}

  // move
  text_area_t(const text_area_t &&other) noexcept;
  text_area_t &operator=(const text_area_t &&other);

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

private:
  void draw_rectangle(const Cairo::RefPtr<Cairo::Context> &cr);
  void draw_text(const Cairo::RefPtr<Cairo::Context> &cr);

public:
  double x = {};
  double y = {};
  double w = {};
  double h = {};
  bool fontInitialized = {};
  Glib::ustring text_string = {};
  Pango::FontDescription font = Pango::FontDescription{};
  Glib::RefPtr<Pango::Layout> layout = {};
};
/**
 * @class gui_sfml_t
 * @brief
 */
class gui_gtkmm_t : public platform_driver_interface_t, public Gtk::Window {
public:
  using window_interface_t::child_t;
  using window_interface_t::event_t;
  using window_interface_t::index_t;

  // gui_gtkmm_t() = delete;
  ~gui_gtkmm_t();

  gui_gtkmm_t(int _argc, char **_argv, std::stringstream &_out,
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
  Gtk::Fixed *container_fixed = {};

  bool bdone = {};

  float cur_x = {};
  float cur_y = {};
  float cur_clip_w = 800;
  float cur_clip_h = 800;

  int status = {};

protected:
  bool window_key_release(GdkEventKey *event);
  bool window_key_press(GdkEventKey *event);
};

} // namespace uxdev
#endif