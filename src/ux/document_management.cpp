#include <include/std_base.h>
#include <include/document_management.h>

document_management_t::document_management_t() {}

/**
 * @fn operator[]
 * @brief returns the child associated with the string
 */
child_storage_t &document_management_t::operator[](const std::string &_idx) {
  auto it = children.find(_idx);
  if (it == children.end()) {
    std::stringstream ss;
    ss << "Error in operator[], object_id  (" << _idx << ") not found.";
    throw std::runtime_error(ss.str());
  }

  return it->second;
}

int document_management_t::optimize_parser() { return EXIT_SUCCESS; }

/**
 * @overload*
 * @fn add
 * @param const std::stringstream &ss
 * @brief
 */
int document_management_t::add(const std::stringstream &ss) {
  return add(ss.str());
}

/**
 * @overload
 * @fn add
 * @param const std::filesystem::path &fp
 * @brief
 */
int document_management_t::add(const std::filesystem::path &fp) {
  std::stringstream data = {};
  std::ifstream finput(fp);
  data << finput.rdbuf();
  finput.close();
  return add(data);
}

/**
 * @overload
 * @fn add
 * @param const std::string &s
 * @brief
 */
int document_management_t::add(const std::string &s) { return add(s.data()); }

int document_management_t::add(const char *sz) { return EXIT_SUCCESS; }
