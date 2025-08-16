#include <lma_obd2_driver/calculated_engine_load.hpp>


CalculatedEngineLoad::CalculatedEngineLoad() {}

void CalculatedEngineLoad::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void CalculatedEngineLoad::Parse() {
  engine_load_ = engineload();
}


// config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'engine_load', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.392, 'type': 'double'}
double CalculatedEngineLoad::engineload() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.392000;
  return ret;
}

