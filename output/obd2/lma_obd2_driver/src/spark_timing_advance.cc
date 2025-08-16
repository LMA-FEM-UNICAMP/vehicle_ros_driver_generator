#include <lma_obd2_driver/spark_timing_advance.hpp>


SparkTimingAdvance::SparkTimingAdvance() {}

void SparkTimingAdvance::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void SparkTimingAdvance::Parse() {
  spark_timing_advance_ = sparktimingadvance();
}


// config detail: {'bit': 0, 'is_signed_var': True, 'len': 8, 'name': 'spark_timing_advance', 'offset': -64.0, 'order': 'intel', 'physical_range': '[-64|63.5]', 'physical_unit': 'deg before TDC', 'precision': 0.5, 'type': 'double'}
double SparkTimingAdvance::sparktimingadvance() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  double ret = x * 0.500000 + -64.000000;
  return ret;
}

