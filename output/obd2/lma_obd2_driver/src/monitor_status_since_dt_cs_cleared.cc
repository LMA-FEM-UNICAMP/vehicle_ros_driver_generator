#include <lma_obd2_driver/monitor_status_since_dt_cs_cleared.hpp>


MonitorStatusSinceDtCsCleared::MonitorStatusSinceDtCsCleared() {}

void MonitorStatusSinceDtCsCleared::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void MonitorStatusSinceDtCsCleared::Parse() {
  mil_on_off_ = milonoff();
  dtc_count_ = dtccount();
  reserved_ = reserved();
  no_name_ = noname();
}


// config detail: {'bit': 4, 'is_signed_var': False, 'len': 1, 'name': 'mil_on_off', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool MonitorStatusSinceDtCsCleared::milonoff() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 7, 'name': 'dtc_count', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int MonitorStatusSinceDtCsCleared::dtccount() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 7);

  int ret = x;
  return ret;
}

// config detail: {'bit': 15, 'is_signed_var': False, 'len': 1, 'name': 'reserved', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool MonitorStatusSinceDtCsCleared::reserved() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(7, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 11, 'is_signed_var': False, 'len': 1, 'name': 'no_name', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool MonitorStatusSinceDtCsCleared::noname() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(3, 1);

  bool ret = x;
  return ret;
}

