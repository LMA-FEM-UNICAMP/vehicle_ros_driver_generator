#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class LongTermFuelTrimBank1 {
public:
    static const uint32_t ID = 0x7;
    LongTermFuelTrimBank1();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double long_term_fuel_trim_bank1_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': True, 'len': 8, 'name': 'long_term_fuel_trim_bank1', 'offset': -100.0, 'order': 'intel', 'physical_range': '[-100|99.2]', 'physical_unit': '%', 'precision': 0.781, 'type': 'double'}
  double longtermfueltrimbank1();
};



