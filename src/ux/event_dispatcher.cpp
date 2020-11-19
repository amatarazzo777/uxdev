#include <include/std_base.h>
#include <include/event.h>
#include <include/event_dispatcher.h>

event_dispatcher_t::event_dispatcher_t() {}

/**
 * @fn event
 * @brief  adds or clears an event listener.
 *
 * Adds an event listener for the named event type or particular virtual key.
 * The fn parameter is the function that is called when the named type has
 * been received from input. There can be only one event handler per object
 * for the event combination.
 *
 *
 * @tparam T The event name.
 *
 * @details The function is saved
 * along at that index.
 *
 * Calling the function with the template parameter with the fn not set will
 * remove the listener. There can be only one listener per type per object.
 * Event listeners can be described in several ways. The system provides the
 * most consolidated syntax in that the the virtual key may be named. These
 * are the keys that text interfaces are most concerned with in capturing
 * within an interface prospective. The text editing portion (edit control)
 * provides the base operations such as delete, display, string modification.
 * All other control object derive from this.
 *
 */
void event_dispatcher_t::listen(const std::string &evt,
                                const fn_listen_t &_fn = {}) {
  std::size_t value = {};
  hash_combine(value, evt);

  if (!_fn)
    event_listener_umap.erase(value);
  else
    event_listener_umap[value].push_back(_fn);
}

void event_dispatcher_t::listen(const std::string &evt,
                                const std::string &detail,
                                const fn_listen_t &_fn = {}) {
  std::size_t value = {};
  hash_combine(value, evt, detail);

  if (!_fn)
    event_listener_umap.erase(value);
  else
    event_listener_umap[value].push_back(_fn);
}

/**
 * @fn dispatch
 * @param int evt - the KEY_[NAME...] of the integer event defined within
 * curses.h
 * @brief class the mapped function if one is assigned.
 */
int event_dispatcher_t::dispatch(const event_t &evt) {
  auto it = event_listener_umap.find(dispatcher_hash_key(evt.hash_code()));
  if (it != event_listener_umap.end()) {
    for (auto fn : it->second) {
      // not bubbling stops dispatch.
      if (!fn(evt))
        break;
    }
  }
  return EXIT_SUCCESS;
}
