#include <lma_obd2_driver/run_since_engine_start.hpp>


RunSinceEngineStart::RunSinceEngineStart() {}

void RunSinceEngineStart::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void RunSinceEngineStart::Parse() {
  a_ = a();
  b_ = b();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'a', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'seconds', 'precision': 256.0, 'type': 'double'}
double RunSinceEngineStart::a() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 256.000000;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'b', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'seconds', 'precision': 1.0, 'type': 'int'}
int RunSinceEngineStart::b() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

