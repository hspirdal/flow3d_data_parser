#ifndef FLOWDATACONTAINER_H
#define FLOWDATACONTAINER_H

#include "RowData.h"
#include <vector>

class FlowDataContainer
{
public:
  FlowDataContainer(unsigned int expectedNumRows = 1000);
  ~FlowDataContainer();

  void parseFlowData(const std::string& filename);
  void appendDataRow(RowData* row) { rowData_.push_back(row); }

  const std::vector<RowData*>& rowData() const { return rowData_; }
  int xdim() const { return xdim_; }
  int ydim() const { return ydim_; }
  int zdim() const { return zdim_; }
  float minPressure() const { return minPressure_; }
  float maxPressure() const { return maxPressure_; }
  float minTemp() const { return minTemp_; }
  float maxTemp() const { return maxTemp_; }

  void setMinPressure(float min) { minPressure_ = min; }
  void setMaxPressure(float max) { maxPressure_ = max; }
  void setMinTemp(float min) { minTemp_ = min; }
  void setMaxTemp(float max) { maxTemp_ = max; }

  void setNumDimensions(int xdim, int ydim, int zdim)  { xdim_ = xdim; ydim_ = ydim; zdim_ = zdim; }
  void setNumDimensions(GMlib::Vector<int, 3> numDim) { xdim_ = numDim[0]; ydim_ = numDim[1]; zdim_ = numDim[2]; }

private:
  std::vector<RowData*> rowData_;
  float minPressure_;
  float maxPressure_;
  float minTemp_;
  float maxTemp_;
  int xdim_; int ydim_; int zdim_;

  /* helpers */
  GMlib::Vector<int, 3> extractHeaderData(const std::vector<std::string>& fields);
  int startIndex(const std::string& field);

};

#endif // FLOWDATACONTAINER_H
