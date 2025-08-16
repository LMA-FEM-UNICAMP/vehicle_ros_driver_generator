#include <lma_obd2_driver/long_term_fuel_trim_bank1.hpp>


LongTermFuelTrimBank1::LongTermFuelTrimBank1() {}

void LongTermFuelTrimBank1::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void LongTermFuelTrimBank1::Parse() {
  long_term_fuel_trim_bank1_ = longtermfueltrimbank1();
}


// config detail: {'bit': 0, 'is_signed_var': True, 'len': 8, 'name': 'long_term_fuel_trim_bank1', 'offset': -100.0, 'order': 'intel', 'physical_range': '[-100|99.2]', 'physical_unit': '%', 'precision': 0.781, 'type': 'double'}
double LongTermFuelTrimBank1::longtermfueltrimbank1() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  double ret = x * 0.781000 + -100.000000;
  return ret;
}

