#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class RunSinceEngineStart {
public:
    static const uint32_t ID = 0x1F;
    RunSinceEngineStart();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double a_;
    int b_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'a', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'seconds', 'precision': 256.0, 'type': 'double'}
  double a();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'b', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'seconds', 'precision': 1.0, 'type': 'int'}
  int b();
};



