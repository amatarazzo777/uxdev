
#include "ux/api.h"

using namespace uxdev;

int main(int argc, char **argv) {
  auto platform = platform_driver_t("gui_clutter", argc, argv);

  auto mw = platform.new_surface("GUI Clutter Window test");

  mw(10, 10) << "Hello \n World.";
  mw(200, 200) << "Program runs in multiple platforms.";

  mw(event_t::key_press, event_t::key_escape, [&](auto evt) {
    mw.finalize();
    platform.terminate();
    return true;
  });

  mw(event_t::key_press, [&](auto evt) {
    mw.content_clear();
    mw(50, 50) << evt.description;
    return true;
  });

  platform.wait_for_exit();
}
