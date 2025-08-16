#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class FuelSystemStatus {
public:
    static const uint32_t ID = 0x3;
    FuelSystemStatus();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int fuel_system_1_;
    int fuel_system_2_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'fuel_system_1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|16]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int fuelsystem1();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'fuel_system_2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|16]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int fuelsystem2();
};



