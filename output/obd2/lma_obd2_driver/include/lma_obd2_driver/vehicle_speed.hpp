#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class VehicleSpeed {
public:
    static const uint32_t ID = 0xD;
    VehicleSpeed();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int vehicle_speed_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vehicle_speed', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'kph', 'precision': 1.0, 'type': 'int'}
  int vehiclespeed();
};



