#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class CalculatedEngineLoad {
public:
    static const uint32_t ID = 0x4;
    CalculatedEngineLoad();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double engine_load_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'engine_load', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.392, 'type': 'double'}
  double engineload();
};



