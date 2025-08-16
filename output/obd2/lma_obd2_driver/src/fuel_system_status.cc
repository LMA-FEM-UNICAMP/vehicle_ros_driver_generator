#include <lma_obd2_driver/fuel_system_status.hpp>


FuelSystemStatus::FuelSystemStatus() {}

void FuelSystemStatus::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void FuelSystemStatus::Parse() {
  fuel_system_1_ = fuelsystem1();
  fuel_system_2_ = fuelsystem2();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'fuel_system_1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|16]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int FuelSystemStatus::fuelsystem1() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'fuel_system_2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|16]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int FuelSystemStatus::fuelsystem2() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

