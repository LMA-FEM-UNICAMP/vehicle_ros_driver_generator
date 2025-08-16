#ifndef lma_HOOKE_DRIVER__REPORT_PARSER_HPP_
#define lma_HOOKE_DRIVER__REPORT_PARSER_HPP_

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/header.hpp>

#include <can_msgs/msg/frame.hpp>


// include- msgs header file
// Example: #include "lma_driver_msgs/BrakeCommand.h"
// #include lma_driver_msgs/protocols["name"].h
#include <lma_obd2_driver_msgs/msg/monitor_status_since_dt_cs_cleared.hpp>
#include <lma_obd2_driver_msgs/msg/maf_air_flow_rate.hpp>
#include <lma_obd2_driver_msgs/msg/throttle_position.hpp>
#include <lma_obd2_driver_msgs/msg/run_since_engine_start.hpp>
#include <lma_obd2_driver_msgs/msg/fuel_system_status.hpp>
#include <lma_obd2_driver_msgs/msg/calculated_engine_load.hpp>
#include <lma_obd2_driver_msgs/msg/absolute_load_value.hpp>
#include <lma_obd2_driver_msgs/msg/relative_throttle_position.hpp>
#include <lma_obd2_driver_msgs/msg/engine_coolant_temperature.hpp>
#include <lma_obd2_driver_msgs/msg/short_term_fuel_trim_bank1.hpp>
#include <lma_obd2_driver_msgs/msg/long_term_fuel_trim_bank1.hpp>
#include <lma_obd2_driver_msgs/msg/short_term_fuel_trim_bank2.hpp>
#include <lma_obd2_driver_msgs/msg/long_term_fuel_trim_bank2.hpp>
#include <lma_obd2_driver_msgs/msg/fuel_pressure.hpp>
#include <lma_obd2_driver_msgs/msg/intake_manifold_absolute_pressure.hpp>
#include <lma_obd2_driver_msgs/msg/engine_rpm.hpp>
#include <lma_obd2_driver_msgs/msg/vehicle_speed.hpp>
#include <lma_obd2_driver_msgs/msg/spark_timing_advance.hpp>
#include <lma_obd2_driver_msgs/msg/intake_air_temperature.hpp>



// include- Parse header file
// Example: #include "brake_command_101.hpp"
// #include protocols["name"].cpp
#include <lma_obd2_driver/monitor_status_since_dt_cs_cleared.hpp>
#include <lma_obd2_driver/maf_air_flow_rate.hpp>
#include <lma_obd2_driver/throttle_position.hpp>
#include <lma_obd2_driver/run_since_engine_start.hpp>
#include <lma_obd2_driver/fuel_system_status.hpp>
#include <lma_obd2_driver/calculated_engine_load.hpp>
#include <lma_obd2_driver/absolute_load_value.hpp>
#include <lma_obd2_driver/relative_throttle_position.hpp>
#include <lma_obd2_driver/engine_coolant_temperature.hpp>
#include <lma_obd2_driver/short_term_fuel_trim_bank1.hpp>
#include <lma_obd2_driver/long_term_fuel_trim_bank1.hpp>
#include <lma_obd2_driver/short_term_fuel_trim_bank2.hpp>
#include <lma_obd2_driver/long_term_fuel_trim_bank2.hpp>
#include <lma_obd2_driver/fuel_pressure.hpp>
#include <lma_obd2_driver/intake_manifold_absolute_pressure.hpp>
#include <lma_obd2_driver/engine_rpm.hpp>
#include <lma_obd2_driver/vehicle_speed.hpp>
#include <lma_obd2_driver/spark_timing_advance.hpp>
#include <lma_obd2_driver/intake_air_temperature.hpp>


namespace lma_obd2_driver
{
namespace report_parser
{

/**
 * @brief param structure of report parser node
 * @param base_frame_id frame id of vehicle
 * @param loop_rate loop rate of publishers in hz
 * @param report_timeout_ms timeout threshold of report can Frame msg from canbus driver
 */
struct Param
{
  std::string base_frame_id;
  double loop_rate;
  int report_timeout_ms;
};

class ReportParser : public rclcpp::Node
{
private:
  // parameters of node
  Param param_;

  // is publish subscrber
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr is_publish_sub_;
  bool is_publish_;

  // subscribers from socketcan interface
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;

  // publishers
  /** example
  rclcpp::Publisher<V2aBrakeStaFb>::SharedPtr brake_sta_fb_pub_;
  **/
  rclcpp::Publisher<lma_obd2_driver_msgs::msg::MonitorStatusSinceDtCsCleared>::SharedPtr monitor_status_since_dt_cs_cleared_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::MafAirFlowRate>::SharedPtr maf_air_flow_rate_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::ThrottlePosition>::SharedPtr throttle_position_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::RunSinceEngineStart>::SharedPtr run_since_engine_start_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::FuelSystemStatus>::SharedPtr fuel_system_status_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::CalculatedEngineLoad>::SharedPtr calculated_engine_load_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::AbsoluteLoadValue>::SharedPtr absolute_load_value_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::RelativeThrottlePosition>::SharedPtr relative_throttle_position_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::EngineCoolantTemperature>::SharedPtr engine_coolant_temperature_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank1>::SharedPtr short_term_fuel_trim_bank1_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::LongTermFuelTrimBank1>::SharedPtr long_term_fuel_trim_bank1_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank2>::SharedPtr short_term_fuel_trim_bank2_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::LongTermFuelTrimBank2>::SharedPtr long_term_fuel_trim_bank2_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::FuelPressure>::SharedPtr fuel_pressure_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::IntakeManifoldAbsolutePressure>::SharedPtr intake_manifold_absolute_pressure_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::EngineRpm>::SharedPtr engine_rpm_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::VehicleSpeed>::SharedPtr vehicle_speed_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::SparkTimingAdvance>::SharedPtr spark_timing_advance_pub_;
rclcpp::Publisher<lma_obd2_driver_msgs::msg::IntakeAirTemperature>::SharedPtr intake_air_temperature_pub_;


  // publish msgs
  /** example
  V2aBrakeStaFb::ConstSharedPtr brake_sta_fb_ptr_;
  **/
  lma_obd2_driver_msgs::msg::MonitorStatusSinceDtCsCleared::ConstSharedPtr monitor_status_since_dt_cs_cleared_ptr_;
lma_obd2_driver_msgs::msg::MafAirFlowRate::ConstSharedPtr maf_air_flow_rate_ptr_;
lma_obd2_driver_msgs::msg::ThrottlePosition::ConstSharedPtr throttle_position_ptr_;
lma_obd2_driver_msgs::msg::RunSinceEngineStart::ConstSharedPtr run_since_engine_start_ptr_;
lma_obd2_driver_msgs::msg::FuelSystemStatus::ConstSharedPtr fuel_system_status_ptr_;
lma_obd2_driver_msgs::msg::CalculatedEngineLoad::ConstSharedPtr calculated_engine_load_ptr_;
lma_obd2_driver_msgs::msg::AbsoluteLoadValue::ConstSharedPtr absolute_load_value_ptr_;
lma_obd2_driver_msgs::msg::RelativeThrottlePosition::ConstSharedPtr relative_throttle_position_ptr_;
lma_obd2_driver_msgs::msg::EngineCoolantTemperature::ConstSharedPtr engine_coolant_temperature_ptr_;
lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank1::ConstSharedPtr short_term_fuel_trim_bank1_ptr_;
lma_obd2_driver_msgs::msg::LongTermFuelTrimBank1::ConstSharedPtr long_term_fuel_trim_bank1_ptr_;
lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank2::ConstSharedPtr short_term_fuel_trim_bank2_ptr_;
lma_obd2_driver_msgs::msg::LongTermFuelTrimBank2::ConstSharedPtr long_term_fuel_trim_bank2_ptr_;
lma_obd2_driver_msgs::msg::FuelPressure::ConstSharedPtr fuel_pressure_ptr_;
lma_obd2_driver_msgs::msg::IntakeManifoldAbsolutePressure::ConstSharedPtr intake_manifold_absolute_pressure_ptr_;
lma_obd2_driver_msgs::msg::EngineRpm::ConstSharedPtr engine_rpm_ptr_;
lma_obd2_driver_msgs::msg::VehicleSpeed::ConstSharedPtr vehicle_speed_ptr_;
lma_obd2_driver_msgs::msg::SparkTimingAdvance::ConstSharedPtr spark_timing_advance_ptr_;
lma_obd2_driver_msgs::msg::IntakeAirTemperature::ConstSharedPtr intake_air_temperature_ptr_;


  // can frame entities
  /** example
  V2adrivestafb530  v2a_drivestafb_530_entity_;
  **/
  MonitorStatusSinceDtCsCleared monitor_status_since_dt_cs_cleared_entity_;
MafAirFlowRate maf_air_flow_rate_entity_;
ThrottlePosition throttle_position_entity_;
RunSinceEngineStart run_since_engine_start_entity_;
FuelSystemStatus fuel_system_status_entity_;
CalculatedEngineLoad calculated_engine_load_entity_;
AbsoluteLoadValue absolute_load_value_entity_;
RelativeThrottlePosition relative_throttle_position_entity_;
EngineCoolantTemperature engine_coolant_temperature_entity_;
ShortTermFuelTrimBank1 short_term_fuel_trim_bank1_entity_;
LongTermFuelTrimBank1 long_term_fuel_trim_bank1_entity_;
ShortTermFuelTrimBank2 short_term_fuel_trim_bank2_entity_;
LongTermFuelTrimBank2 long_term_fuel_trim_bank2_entity_;
FuelPressure fuel_pressure_entity_;
IntakeManifoldAbsolutePressure intake_manifold_absolute_pressure_entity_;
EngineRpm engine_rpm_entity_;
VehicleSpeed vehicle_speed_entity_;
SparkTimingAdvance spark_timing_advance_entity_;
IntakeAirTemperature intake_air_temperature_entity_;


  // msg reveived time
  /** example
  rclcpp::Time brake_sta_fb_received_time_;
  **/
  rclcpp::Time monitor_status_since_dt_cs_cleared_received_time_;
rclcpp::Time maf_air_flow_rate_received_time_;
rclcpp::Time throttle_position_received_time_;
rclcpp::Time run_since_engine_start_received_time_;
rclcpp::Time fuel_system_status_received_time_;
rclcpp::Time calculated_engine_load_received_time_;
rclcpp::Time absolute_load_value_received_time_;
rclcpp::Time relative_throttle_position_received_time_;
rclcpp::Time engine_coolant_temperature_received_time_;
rclcpp::Time short_term_fuel_trim_bank1_received_time_;
rclcpp::Time long_term_fuel_trim_bank1_received_time_;
rclcpp::Time short_term_fuel_trim_bank2_received_time_;
rclcpp::Time long_term_fuel_trim_bank2_received_time_;
rclcpp::Time fuel_pressure_received_time_;
rclcpp::Time intake_manifold_absolute_pressure_received_time_;
rclcpp::Time engine_rpm_received_time_;
rclcpp::Time vehicle_speed_received_time_;
rclcpp::Time spark_timing_advance_received_time_;
rclcpp::Time intake_air_temperature_received_time_;


  // timer
  rclcpp::TimerBase::SharedPtr timer_;

public:
  ReportParser();
  // callback
  /**
   * @brief callback function of can Frame msgs, to store the data to member variable
   * 
   * @param msg 
   */
  void callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg);
  /**
   * @brief callback function of Bool msg, to store the data to member variable, decide publish report msgs or not
   * 
   * @param msg 
   */
  void callbackIsPublish(const std_msgs::msg::Bool::ConstSharedPtr & msg);
  /**
   * @brief parser can frames, convert can frames to lma_driver_msgs
   * 
   */
  void timerCallback();
};
} // report_parser
} // lma_obd2_driver
#endif // lma_HOOKE_DRIVER__REPORT_PARSER_HPP_