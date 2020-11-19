#ifndef BASE_DATA_LAYER_H
#define BASE_DATA_LAYER_H
namespace uxdev {
class data_layer_t {
public:
  template <typename T> data_layer_t &operator=(const T &s) {
    out.str(std::string());
    buffer.str(std::string());
    return operator<<(s);
  }

  /**
   * @overload
   * @fn operator=
   * @param const std::filesystem::path &fpath - the file location
   * @@brief read a file and place into object view.
   */
  data_layer_t &operator=(const std::filesystem::path &fpath) {
    out.str(std::string());
    buffer.str(std::string());
    return operator<<(fpath);
  }

  /**
   * @overload
   * @fn operator<<
   * @param const std::string &s
   * @brief Adds a stream to the output.
   */
  template <typename T> data_layer_t &operator<<(const T &a) {
    out << a;
    buffer << a;
    return *this;
  }

  /**
   * @overload
   * @fn operator<<
   * @param const std::string &s
   * @brief Adds a stream to the output.
   */
  template <typename T>
  data_layer_t &operator<<(const std::filesystem::path &f) {
    return operator<<(read_file(f));
  }

  template <typename T> data_layer_t &operator<<(const char *sz) {
    out << sz;
    buffer << sz;
    return *this;
  }

  /**
   * @overload
   * @fn operator+=
   * @brief appends data, same as operator<<;
   */
  template <typename T> data_layer_t &operator+=(const T &s) {
    return operator<<(s);
  }

  std::string data(void) { return buffer.str(); }

  std::stringstream read_file(const std::filesystem::path &filename);

  std::stringstream out = {};
  std::stringstream buffer;
}; // namespace ptui

} // namespace uxdev
#endif