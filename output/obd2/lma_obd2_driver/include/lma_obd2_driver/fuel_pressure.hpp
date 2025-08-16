#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class FuelPressure {
public:
    static const uint32_t ID = 0xA;
    FuelPressure();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double fuel_pressure_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'fuel_pressure', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|765]', 'physical_unit': 'kPa', 'precision': 3.0, 'type': 'double'}
  double fuelpressure();
};



