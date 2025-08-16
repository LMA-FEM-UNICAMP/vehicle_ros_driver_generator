#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class RelativeThrottlePosition {
public:
    static const uint32_t ID = 0x45;
    RelativeThrottlePosition();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double rel_throttle_position_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'rel_throttle_position', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.392, 'type': 'double'}
  double relthrottleposition();
};



