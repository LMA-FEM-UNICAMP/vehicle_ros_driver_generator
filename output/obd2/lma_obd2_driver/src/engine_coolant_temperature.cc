#include <lma_obd2_driver/engine_coolant_temperature.hpp>


EngineCoolantTemperature::EngineCoolantTemperature() {}

void EngineCoolantTemperature::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void EngineCoolantTemperature::Parse() {
  engine_coolant_temp_ = enginecoolanttemp();
}


// config detail: {'bit': 0, 'is_signed_var': True, 'len': 8, 'name': 'engine_coolant_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': 'deg C', 'precision': 1.0, 'type': 'int'}
int EngineCoolantTemperature::enginecoolanttemp() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  int ret = x + -40.000000;
  return ret;
}

