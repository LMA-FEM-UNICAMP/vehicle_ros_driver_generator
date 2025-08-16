#include <lma_obd2_driver/absolute_load_value.hpp>


AbsoluteLoadValue::AbsoluteLoadValue() {}

void AbsoluteLoadValue::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void AbsoluteLoadValue::Parse() {
  a_ = a();
  b_ = b();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'a', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|25700]', 'physical_unit': '%', 'precision': 100.352, 'type': 'double'}
double AbsoluteLoadValue::a() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 100.352000;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'b', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|25700]', 'physical_unit': '%', 'precision': 0.392, 'type': 'double'}
double AbsoluteLoadValue::b() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.392000;
  return ret;
}

