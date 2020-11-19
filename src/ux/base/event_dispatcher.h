#ifndef BASE_EVENT_DISPATCHER_H
#define BASE_EVENT_DISPATCHER_H

namespace uxdev {

class event_t {
public:
  u_int8_t type = {};
  char *detail = {};
  char *key = {};
  unsigned int x = {}, y = {}, h = {}, w = {};

  std::size_t hash_code() {
    std::size_t value = {};
    hash_combine(value, event_name);
    return value;
  }

  const u_int8_t key_press = 1;
  const u_int8_t key_release = 2;
  const u_int8_t motion_notify = 3;
  const u_int8_t button_press = 4;
  const u_int8_t button_release = 5;
  const u_int8_t scroll = 6;
  const u_int8_t configure = 7;

}

/**
 * @typedef fn_listen_t
 * @brief The listener type. Every function added through the event() must be
 * of this type. The function returns a bool for bubbling events and has as a
 * parameter an event_t object. The event_t object is used to represent all
 * events. Within the event handler, you should utilize the appropriate
 * parameters.
 */
  typedef std::function<bool(const event_t &)> fn_listen_t;
  
class event_dispatcher_t {
public:

  // @brief listener map
  typedef std::unordered_map<std::size_t, std::list<fn_listen_t>>
      event_listener_umap_t;

  event_dispatcher_t() {}

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
  void listen(const std::string &evt, const fn_listen_t &_fn = {}) {
    std::size_t value = {};
    hash_combine(value, evt);

    if (!_fn)
      event_listener_umap.erase(value);
    else
      event_listener_umap[value].push_back(_fn);
  }

  void listen(const std::string &evt, const std::string &detail,
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
  int dispatch(const event_t &evt) {
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

  event_listener_umap_t event_listener_umap = {};
};

} // namespace uxdev
#endif