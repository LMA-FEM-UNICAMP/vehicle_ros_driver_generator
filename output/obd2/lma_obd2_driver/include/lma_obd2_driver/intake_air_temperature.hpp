#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class IntakeAirTemperature {
public:
    static const uint32_t ID = 0xF;
    IntakeAirTemperature();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int intake_air_temp_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': True, 'len': 8, 'name': 'intake_air_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': 'deg C', 'precision': 1.0, 'type': 'int'}
  int intakeairtemp();
};



