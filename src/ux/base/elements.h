#ifndef BASE_ELEMENTS_H
#define BASE_ELEMENTS_H

namespace uxdev {
class text_entry_field_t : public element_object_t {
  using element_object_t::operator=;
  using element_object_t::operator<<;
  using element_object_t::operator+=;
};
} // namespace uxdev
#endif