#include <lma_obd2_driver/engine_rpm.hpp>


EngineRpm::EngineRpm() {}

void EngineRpm::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void EngineRpm::Parse() {
  a_ = a();
  b_ = b();
}


// config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'a', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|6000]', 'physical_unit': 'RPM', 'precision': 1.0, 'type': 'int'}
int EngineRpm::a() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 15, 'is_signed_var': False, 'len': 8, 'name': 'b', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|6000]', 'physical_unit': 'RPM', 'precision': 1.0, 'type': 'int'}
int EngineRpm::b() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

