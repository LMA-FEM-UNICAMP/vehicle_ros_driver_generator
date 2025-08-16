#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class EngineRpm {
public:
    static const uint32_t ID = 0xC;
    EngineRpm();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int a_;
    int b_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'a', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|6000]', 'physical_unit': 'RPM', 'precision': 1.0, 'type': 'int'}
  int a();

  // config detail: {'bit': 15, 'is_signed_var': False, 'len': 8, 'name': 'b', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|6000]', 'physical_unit': 'RPM', 'precision': 1.0, 'type': 'int'}
  int b();
};



