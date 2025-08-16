#include <lma_obd2_driver/maf_air_flow_rate.hpp>


MafAirFlowRate::MafAirFlowRate() {}

void MafAirFlowRate::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void MafAirFlowRate::Parse() {
  maf_a_ = mafa();
  maf_b_ = mafb();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'maf_a', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int MafAirFlowRate::mafa() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 7, 'is_signed_var': True, 'len': 32, 'name': 'maf_b', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|655.35]', 'physical_unit': 'g/s', 'precision': 1.0, 'type': 'double'}
double MafAirFlowRate::mafb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 1));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t2(*(bytes + 2));
  t = t2.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t3(*(bytes + 3));
  t = t3.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 0;
  x >>= 0;

  double ret = x;
  return ret;
}

