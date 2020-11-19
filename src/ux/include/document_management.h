#ifndef BASE_DOCUMENT_MANAGEMENT_H
#define BASE_DOCUMENT_MANAGEMENT_H
namespace uxdev {

class element_object_t;

class document_management_t {
public:
  typedef std::string attribute_index_t;
  typedef std::variant<u_int16_t, std::array<u_int16_t, 2>, std::string,
                       std::vector<std::string>>
      attribute_storage_t;
  typedef std::unordered_map<attribute_index_t, attribute_storage_t>
      attribute_t;

  typedef std::string index_t;
  typedef std::pair<element_object_t, attribute_t> child_storage_t;

  typedef std::map<index_t, child_storage_t> children_storage_t;

  children_storage_t children = {};

  document_management_t();

  child_storage_t &operator[](const std::string &_idx);

  int optimize_parser();

  int add(const std::stringstream &ss);

  int add(const std::filesystem::path &fp);

  int add(const std::string &s);
  /**
   * @overload
   * @fn add
   * @brief Adds the element objects defined in the "layout definition format"
   * to the window. The definition syntax provides naming an object id and
   * setting its attributes. The following form is used:
   *
   * :object_id_1:
   *   attribute-1 params ... ;
   *   attribute-2 params ... ;
   *   attribute-3 "Literal String";
   *
   * :object_id_2:
   *   attribute-1 params ... ;
   *   attribute-2 params ... ;
   *   attribute-3 "Literal String";
   *
   *   Object ids start with a ':' (colon) and end with a ':' (colon). The
   * object id can contain only alphanumeric characters [a-zA-Z0-9] with a few
   * extra like "_" (underscore) and "." (period). Any of these characters may
   * be in any position however.
   *
   *   Spaces or any other character cannot be within the middle of the name.
   * Spaces can be between the ':' colons of the object declaration. These are
   * ignored, trimming the object id string representation. So it is fine to
   * provide as input:
   *
   *  ': txtFirst_Name  :'
   *
   *   Using that as an object id, results in 'txtFirst_Name' without the spaces
   * as the indirect index. So when an element object is referenced using the
   * window_t[] operator, it is used precisely in trimmed and parsed form:
   * mw["txtFirst_Name"].
   *
   *   Attributes follow the :object_id:. That is, the :object_id: must be
   * first. Attributes are optional although at times of minimization, there
   * will be at least one. The attribute specifies important settings such as
   * what class the element is or what color. The class attribute is a base
   * attribute that all objects have. The value or setting is a generalized name
   * that provides broad noun domain longevity. The editor control connection or
   * connection with a text layout viewer is named for class. Specific
   * attributes for classes are not discussed here.
   *
   *   Attribute settings all end in a ';'. Along with the attribute name are
   * its parameters or values. Attribute values may be an integer number,
   * double, string, etc as they appear encoded in string form. When multiple
   * parameters appear within the attribute setting, each parameter must be
   * separated by a " " (space). For example:
   *
   * : status_line :
   *   location 25 0;
   *   color grey darkblue;
   *
   *   The object_id is status_line and can be referenced by that specific
   * string name within the window_t["status_line"] operator. Note that the
   * spaces between the token are omitted. The value "status line" will produce
   * a syntax error exception.
   *
   *   The "color" attribute sets the foreground and background color. While its
   * parameters are strings they do not appear in quotes because there are not
   * special characters within the value.
   *
   *   When literal strings span multiple lines or they must have special
   * characters within them, the literal string must have "'s (quotes) around it
   * within the window definition. Special characters are: " " (space), ";"
   * (semi-color), and " quote. When quotes are used to enclose the value,
   * special characters may be used. The attribute's value as a literal string
   * may have several quotes, even unmatched, within.
   *
   *   Numeric attribute values are that, numeric. A numeric can be described as
   * an integer or as a fraction. negative with the prefix '-' (minus) but not
   * with '+' plus. No commas may be used. double precision attribute
   * values may also be described by including one '.' (decimal point) between
   * the whole and fractional part. Note, check with the attribute documentation
   * for other possible numeric formats.
   *
   *   When window definitions are in-lined, the c++ raw string literal provides
   * a useful mechanism for it to be declared, formatted and maintained.
   * Declared formally as const char *, the raw string literal may encompass
   * several lines. It may include binary raw information such as tab
   * characters. As well, it can even accept low value and non printable
   * information. The treatment of the text in its multiple lines, quotes and
   * special characters is similar to the encompassing language semantics. That
   * is, it makes the form seem natural.
   *
   */

  int add(const char *sz);
};

} // namespace uxdev
#endif