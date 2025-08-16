#include <lma_obd2_driver/throttle_position.hpp>


ThrottlePosition::ThrottlePosition() {}

void ThrottlePosition::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void ThrottlePosition::Parse() {
  throttle_position_ = throttleposition();
}


// config detail: {'bit': 0, 'is_signed_var': True, 'len': 8, 'name': 'throttle_position', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.392, 'type': 'double'}
double ThrottlePosition::throttleposition() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  double ret = x * 0.392000;
  return ret;
}

