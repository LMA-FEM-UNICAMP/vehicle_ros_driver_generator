#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class IntakeManifoldAbsolutePressure {
public:
    static const uint32_t ID = 0xB;
    IntakeManifoldAbsolutePressure();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int imap_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'imap', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'kPa', 'precision': 1.0, 'type': 'int'}
  int imap();
};



