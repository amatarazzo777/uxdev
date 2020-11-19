#ifndef BASE_ELEMENET_OBJECT_H
#define BASE_ELEMENET_OBJECT_H

namespace uxdev {

/**
 * @class object_t
 * @brief the base object which uses a curses pad type. The object provides
 * several operator overloads for placing text within the pad rectangle.
 */
class element_object_t : 
                         public event_dispatcher_t,
                         public data_layer_t,
                         public document_management_t {
public:


  using data_layer_t::operator=;
  using data_layer_t::operator<<;
  using data_layer_t::operator+=;
  using document_management_t::operator[];

  element_object_t() {}

  element_object_t(const std::string &_id) : id(_id) {}

  element_object_t &operator()(const u_int16_t _row, const u_int16_t _col) {
    return *this;
  }

  int dispatch(event_t &evt) {
    return event_dispatcher_t::dispatch(evt);
  }

  // @brief public data members
  std::string id = {};
};

} // namespace uxdev
#endif
