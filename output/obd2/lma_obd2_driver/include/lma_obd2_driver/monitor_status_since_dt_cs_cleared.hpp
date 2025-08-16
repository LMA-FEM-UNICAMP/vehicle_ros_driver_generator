#pragma once

#include <lma_obd2_driver/Byte.hpp>
#include <iostream>

class MonitorStatusSinceDtCsCleared {
public:
    static const uint32_t ID = 0x1;
    MonitorStatusSinceDtCsCleared();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    bool mil_on_off_;
    int dtc_count_;
    bool reserved_;
    bool no_name_;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 4, 'is_signed_var': False, 'len': 1, 'name': 'mil_on_off', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool milonoff();

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 7, 'name': 'dtc_count', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int dtccount();

  // config detail: {'bit': 15, 'is_signed_var': False, 'len': 1, 'name': 'reserved', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool reserved();

  // config detail: {'bit': 11, 'is_signed_var': False, 'len': 1, 'name': 'no_name', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool noname();
};



