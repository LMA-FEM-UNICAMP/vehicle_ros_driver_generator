#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class EngineCoolantTemperature {
public:
    static const uint32_t ID = 0x5;
    EngineCoolantTemperature();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int engine_coolant_temp_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': True, 'len': 8, 'name': 'engine_coolant_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': 'deg C', 'precision': 1.0, 'type': 'int'}
  int enginecoolanttemp();
};



