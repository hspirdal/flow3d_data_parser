#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>

class Util
{
public:
  static float floatval(unsigned int index, const std::vector<std::string> vec);
  static std::string getFileContents(const std::string& filename);

  /* Helpers */
  static inline float toFloat(const std::string& str)
  {
    std::istringstream ss(str); float f = 0.0f; ss >> f; return f;
  }
  static inline int toInt(const std::string& str) { return atoi(str.c_str()); }
  static void split(std::string str, std::vector<std::string>& vec, const std::string& delim);

  // http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
  // trim from start
  static inline std::string &ltrim(std::string &s)
  {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
  }
  // trim from end
  static inline std::string &rtrim(std::string &s)
  {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
  }
  // trim from both ends
  static inline std::string &trim(std::string &s)
  {
    return ltrim(rtrim(s));
  }

private:
  Util();




};

#endif // UTIL_H
