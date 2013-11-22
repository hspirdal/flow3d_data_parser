#include "FlowDataContainer.h"

#include "util.h"
#include <limits>

FlowDataContainer::FlowDataContainer(unsigned int expectedNumRows)
  : xdim_(0), ydim_(0), zdim_(0), minPressure_(0.0f), maxPressure_(0.0f), minTemp_(0.0f), maxTemp_(0.0f)
{
  rowData_.reserve(expectedNumRows);
}

FlowDataContainer::~FlowDataContainer()
{
  for(int i = 0; i < rowData_.size(); i++)
    delete rowData_.at(i);

  rowData_.clear();
}

void FlowDataContainer::parseFlowData(const std::string &filename)
{
  const std::string delim = "  ";
  float minPressure = std::numeric_limits<float>::max();
  float maxPressure = 0.0f;
  float minTemp = std::numeric_limits<float>::max();
  float maxTemp = 0.0f;

  std::stringstream ss(Util::getFileContents(filename));
  std::string line = "";

  unsigned int lineno = 0;
  std::vector<std::string> fields;
  fields.reserve(8);
  while(std::getline(ss, line))
  {
    // Parse Header Data
    if(lineno == 8)
    {
      line = Util::trim(line);
      fields.clear();
      Util::split(line, fields, delim);
      setNumDimensions(extractHeaderData(fields));
    }

    if(++lineno < 12)
      continue;

    line = Util::trim(line);
    fields.clear();
    Util::split(line, fields, delim);

    float pressure = Util::floatval(3, fields);
    minPressure = std::min(minPressure, pressure);
    maxPressure = std::max(maxPressure, pressure);
    float temp = Util::floatval(4, fields);
    minTemp = std::min(minTemp, temp);
    maxTemp = std::max(maxTemp, temp);

    RowData* data = new RowData( Util::floatval(0, fields),  Util::floatval(1, fields), Util::floatval(2, fields),
                  pressure,  Util::floatval(4, fields),
                  Util::floatval(5, fields),  Util::floatval(6, fields), Util::floatval(7, fields));
    appendDataRow(data);
  }
  setMinPressure(minPressure);
  setMaxPressure(maxPressure);
  setMinTemp(minTemp);
  setMaxTemp(maxTemp);
}

GMlib::Vector<int, 3> FlowDataContainer::extractHeaderData(const std::vector<std::string> &fields)
{
  const int sx = startIndex(fields.at(4));
  const int sy = startIndex(fields.at(6));
  const int sz = startIndex(fields.at(8));

  GMlib::Vector<int, 3> numDimensions;
  numDimensions[0] = Util::toInt(fields.at(5))-sx;
  numDimensions[1] = Util::toInt(fields.at(7))-sy;
  numDimensions[2] = Util::toInt(fields.at(9))-sz;
  return numDimensions;
}

int FlowDataContainer::startIndex(const std::string& field)
{
  // For speed purposes, we trust that the format of the data is exactly in the form [chars=uint]. Ex: ix=3
  std::string str = field;
  Util::trim(str);
  int numStartIndex = str.find('=')+1;
  int numEndIndex = str.find(' ');
  std::string num = "";
  for(int i = numStartIndex; i < numEndIndex; ++i)
    num += str[i];

  return Util::toInt(num);
}
