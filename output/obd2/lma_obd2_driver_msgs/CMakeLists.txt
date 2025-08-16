cmake_minimum_required(VERSION 3.5)
project(lma_obd2_driver_msgs)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

set(msg_files
		"msg/MonitorStatusSinceDtCsCleared.msg"
	"msg/MafAirFlowRate.msg"
	"msg/ThrottlePosition.msg"
	"msg/RunSinceEngineStart.msg"
	"msg/FuelSystemStatus.msg"
	"msg/CalculatedEngineLoad.msg"
	"msg/AbsoluteLoadValue.msg"
	"msg/RelativeThrottlePosition.msg"
	"msg/EngineCoolantTemperature.msg"
	"msg/ShortTermFuelTrimBank1.msg"
	"msg/LongTermFuelTrimBank1.msg"
	"msg/ShortTermFuelTrimBank2.msg"
	"msg/LongTermFuelTrimBank2.msg"
	"msg/FuelPressure.msg"
	"msg/IntakeManifoldAbsolutePressure.msg"
	"msg/EngineRpm.msg"
	"msg/VehicleSpeed.msg"
	"msg/SparkTimingAdvance.msg"
	"msg/IntakeAirTemperature.msg"

)

set(msg_dependencies
	std_msgs
  builtin_interfaces)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES ${msg_dependencies}
  ADD_LINTER_TESTS)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()