#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class MafAirFlowRate {
public:
    static const uint32_t ID = 0x10;
    MafAirFlowRate();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int maf_a_;
    double maf_b_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'maf_a', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int mafa();

  // config detail: {'bit': 7, 'is_signed_var': True, 'len': 32, 'name': 'maf_b', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|655.35]', 'physical_unit': 'g/s', 'precision': 1.0, 'type': 'double'}
  double mafb();
};



