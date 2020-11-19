#ifndef BASE_EVENT_DISPATCHER_H
#define BASE_EVENT_DISPATCHER_H

namespace uxdev {

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

  event_dispatcher_t();

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
  void listen(const int &event_type, const fn_listen_t &_fn = {});

  void listen(const int &event_type, const int &detail,
              const fn_listen_t &_fn = {});

  int dispatch(const event_t &evt);

  event_listener_umap_t event_listener_umap = {};
};

} // namespace uxdev
#endif