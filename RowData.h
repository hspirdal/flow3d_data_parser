#ifndef ROWDATA_H
#define ROWDATA_H

#include <gmCoreModule>

struct RowData
{
  GMlib::Vector<float, 3> pos_;
  GMlib::Vector<float, 3> vel_;
  float pressure_;
  float temp_;

  RowData(float x, float y, float z, float pressure, float temp, float u, float v, float w)
  {
    pos_[0] = x; pos_[1] = y; pos_[2] = z;
    vel_[0] = u; vel_[1] = v; vel_[2] = w;
    pressure_ = pressure; temp_ = temp;
  }

  RowData(GMlib::Vector<float, 3> pos, float pressure, float temp, GMlib::Vector<float, 3> velocity)
  {
    pos_ = pos;
    pressure_ = pressure;
    temp_ = temp;
    vel_ = velocity;
  }

  const GMlib::Vector<float, 3>& getPos() const { return pos_; }
  const GMlib::Vector<float, 3>& getVelocity() const { return vel_; }
  float getPressure() const { return pressure_; }
  float getTemp() const { return temp_; }



};

#endif // ROWDATA_H
