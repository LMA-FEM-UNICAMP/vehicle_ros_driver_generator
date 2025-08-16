#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class SparkTimingAdvance {
public:
    static const uint32_t ID = 0xE;
    SparkTimingAdvance();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double spark_timing_advance_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': True, 'len': 8, 'name': 'spark_timing_advance', 'offset': -64.0, 'order': 'intel', 'physical_range': '[-64|63.5]', 'physical_unit': 'deg before TDC', 'precision': 0.5, 'type': 'double'}
  double sparktimingadvance();
};



