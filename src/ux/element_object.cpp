
#include <include/std_base.h>
#include <element_object.h>

element_object_t::element_object_t() {}

element_object_t::element_object_t(const std::string &_id) : id(_id) {}

element_object_t::element_object_t &
element_object_t::operator()(const u_int16_t _row, const u_int16_t _col) {
  return *this;
}

int element_object_t::dispatch(event_t &evt) {
  return event_dispatcher_t::dispatch(evt);
}
