#include <lma_obd2_driver/relative_throttle_position.hpp>


RelativeThrottlePosition::RelativeThrottlePosition() {}

void RelativeThrottlePosition::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void RelativeThrottlePosition::Parse() {
  rel_throttle_position_ = relthrottleposition();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'rel_throttle_position', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.392, 'type': 'double'}
double RelativeThrottlePosition::relthrottleposition() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.392000;
  return ret;
}

