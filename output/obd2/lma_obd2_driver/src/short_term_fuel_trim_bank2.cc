#include <lma_obd2_driver/short_term_fuel_trim_bank2.hpp>


ShortTermFuelTrimBank2::ShortTermFuelTrimBank2() {}

void ShortTermFuelTrimBank2::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void ShortTermFuelTrimBank2::Parse() {
  instant_fuel_trim_bank2_ = instantfueltrimbank2();
}


// config detail: {'bit': 0, 'is_signed_var': True, 'len': 8, 'name': 'instant_fuel_trim_bank2', 'offset': -100.0, 'order': 'intel', 'physical_range': '[-100|99.2]', 'physical_unit': '%', 'precision': 0.781, 'type': 'double'}
double ShortTermFuelTrimBank2::instantfueltrimbank2() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  double ret = x * 0.781000 + -100.000000;
  return ret;
}

