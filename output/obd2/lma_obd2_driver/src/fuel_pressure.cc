#include <lma_obd2_driver/fuel_pressure.hpp>


FuelPressure::FuelPressure() {}

void FuelPressure::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void FuelPressure::Parse() {
  fuel_pressure_ = fuelpressure();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'fuel_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|765]', 'physical_unit': 'kPa', 'precision': 3.0, 'type': 'double'}
double FuelPressure::fuelpressure() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 3.000000;
  return ret;
}

