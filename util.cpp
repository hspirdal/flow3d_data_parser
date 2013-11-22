#include "util.h"

#include <fstream>
#include <iterator>

Util::Util()
{
}
float Util::floatval(unsigned int index, const std::vector<std::string> vec)
{
  return index < vec.size() ? toFloat(vec.at(index)) : 0.0f;
}

std::string Util::getFileContents(const std::string& filename)
{
  std::ifstream in(filename.c_str());
  return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

void Util::split(std::string str, std::vector<std::string> &vec, const std::string &delim)
{
  size_t pos = 0;
  while ((pos = str.find(delim)) != std::string::npos)
  {
      vec.push_back(str.substr(0, pos));
      str.erase(0, pos + delim.length());
  }
  vec.push_back(str);
}
