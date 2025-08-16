#include <lma_obd2_driver/vehicle_speed.hpp>


VehicleSpeed::VehicleSpeed() {}

void VehicleSpeed::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VehicleSpeed::Parse() {
  vehicle_speed_ = vehiclespeed();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vehicle_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'kph', 'precision': 1.0, 'type': 'int'}
int VehicleSpeed::vehiclespeed() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

