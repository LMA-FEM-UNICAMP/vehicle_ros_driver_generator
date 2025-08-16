#include <lma_obd2_driver/intake_manifold_absolute_pressure.hpp>


IntakeManifoldAbsolutePressure::IntakeManifoldAbsolutePressure() {}

void IntakeManifoldAbsolutePressure::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void IntakeManifoldAbsolutePressure::Parse() {
  imap_ = imap();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'imap', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'kPa', 'precision': 1.0, 'type': 'int'}
int IntakeManifoldAbsolutePressure::imap() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

