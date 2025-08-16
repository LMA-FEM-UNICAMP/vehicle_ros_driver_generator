cmake_minimum_required(VERSION 3.5)
project(lma_obd2_driver)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(lma_obd2_driver_msgs)

# ament_auto_add_executable(${PROJECT_NAME}_control_command_node
  
#   src/Byte.cc
#   src/control_command.cpp
#   src/control_command_node.cpp
# )

ament_auto_add_executable(${PROJECT_NAME}_report_parser_node
  src/monitor_status_since_dt_cs_cleared.cc
src/maf_air_flow_rate.cc
src/throttle_position.cc
src/run_since_engine_start.cc
src/fuel_system_status.cc
src/calculated_engine_load.cc
src/absolute_load_value.cc
src/relative_throttle_position.cc
src/engine_coolant_temperature.cc
src/short_term_fuel_trim_bank1.cc
src/long_term_fuel_trim_bank1.cc
src/short_term_fuel_trim_bank2.cc
src/long_term_fuel_trim_bank2.cc
src/fuel_pressure.cc
src/intake_manifold_absolute_pressure.cc
src/engine_rpm.cc
src/vehicle_speed.cc
src/spark_timing_advance.cc
src/intake_air_temperature.cc

  src/Byte.cc
  src/report_parser.cpp
  src/report_parser_node.cpp
)

# install
ament_auto_package(
  INSTALL_TO_SHARE
  launch
  # config
)