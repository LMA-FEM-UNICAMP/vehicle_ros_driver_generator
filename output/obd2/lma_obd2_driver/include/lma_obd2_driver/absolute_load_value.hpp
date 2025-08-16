#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class AbsoluteLoadValue {
public:
    static const uint32_t ID = 0x43;
    AbsoluteLoadValue();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double a_;
    double b_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'a', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|25700]', 'physical_unit': '%', 'precision': 100.352, 'type': 'double'}
  double a();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'b', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|25700]', 'physical_unit': '%', 'precision': 0.392, 'type': 'double'}
  double b();
};



