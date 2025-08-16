#include <lma_obd2_driver/report_parser.hpp>

namespace lma_obd2_driver
{
    namespace report_parser
    {
        ReportParser::ReportParser() : Node("report_parser")
        {
            // ros params
            param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
            param_.report_timeout_ms = declare_parameter("report_timeout_ms", 1000);
            param_.loop_rate = declare_parameter("loop_rate", 50.0);

            // // initialize msg received time
            /** example
            brake_command_received_time_ = this->now();
            **/
            monitor_status_since_dt_cs_cleared_received_time_ = this->now();
            maf_air_flow_rate_received_time_ = this->now();
            throttle_position_received_time_ = this->now();
            run_since_engine_start_received_time_ = this->now();
            fuel_system_status_received_time_ = this->now();
            calculated_engine_load_received_time_ = this->now();
            absolute_load_value_received_time_ = this->now();
            relative_throttle_position_received_time_ = this->now();
            engine_coolant_temperature_received_time_ = this->now();
            short_term_fuel_trim_bank1_received_time_ = this->now();
            long_term_fuel_trim_bank1_received_time_ = this->now();
            short_term_fuel_trim_bank2_received_time_ = this->now();
            long_term_fuel_trim_bank2_received_time_ = this->now();
            fuel_pressure_received_time_ = this->now();
            intake_manifold_absolute_pressure_received_time_ = this->now();
            engine_rpm_received_time_ = this->now();
            vehicle_speed_received_time_ = this->now();
            spark_timing_advance_received_time_ = this->now();
            intake_air_temperature_received_time_ = this->now();

            is_publish_ = true;

            using std::placeholders::_1;

            /* subscriber */
            {
                // from pix driver autoware interface
                can_frame_sub_ = create_subscription<can_msgs::msg::Frame>(
                    "input/can_rx", 1, std::bind(&ReportParser::callbackCan, this, _1));
                // is publish
                is_publish_sub_ = create_subscription<std_msgs::msg::Bool>(
                    "input/is_publish", 1, std::bind(&ReportParser::callbackIsPublish, this, _1));
            }

            /* publisher */
            {
                /** example
                brake_sta_fb_pub_ =
                  create_publisher<V2aBrakeStaFb>("/lma_hooke/v2a_brakestafb", rclcpp::QoS{1});
                **/
                monitor_status_since_dt_cs_cleared_pub_ = create_publisher<lma_obd2_driver_msgs::msg::MonitorStatusSinceDtCsCleared>("/lma_obd2/monitor_status_since_dt_cs_cleared", rclcpp::QoS{1});
                maf_air_flow_rate_pub_ = create_publisher<lma_obd2_driver_msgs::msg::MafAirFlowRate>("/lma_obd2/maf_air_flow_rate", rclcpp::QoS{1});
                throttle_position_pub_ = create_publisher<lma_obd2_driver_msgs::msg::ThrottlePosition>("/lma_obd2/throttle_position", rclcpp::QoS{1});
                run_since_engine_start_pub_ = create_publisher<lma_obd2_driver_msgs::msg::RunSinceEngineStart>("/lma_obd2/run_since_engine_start", rclcpp::QoS{1});
                fuel_system_status_pub_ = create_publisher<lma_obd2_driver_msgs::msg::FuelSystemStatus>("/lma_obd2/fuel_system_status", rclcpp::QoS{1});
                calculated_engine_load_pub_ = create_publisher<lma_obd2_driver_msgs::msg::CalculatedEngineLoad>("/lma_obd2/calculated_engine_load", rclcpp::QoS{1});
                absolute_load_value_pub_ = create_publisher<lma_obd2_driver_msgs::msg::AbsoluteLoadValue>("/lma_obd2/absolute_load_value", rclcpp::QoS{1});
                relative_throttle_position_pub_ = create_publisher<lma_obd2_driver_msgs::msg::RelativeThrottlePosition>("/lma_obd2/relative_throttle_position", rclcpp::QoS{1});
                engine_coolant_temperature_pub_ = create_publisher<lma_obd2_driver_msgs::msg::EngineCoolantTemperature>("/lma_obd2/engine_coolant_temperature", rclcpp::QoS{1});
                short_term_fuel_trim_bank1_pub_ = create_publisher<lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank1>("/lma_obd2/short_term_fuel_trim_bank1", rclcpp::QoS{1});
                long_term_fuel_trim_bank1_pub_ = create_publisher<lma_obd2_driver_msgs::msg::LongTermFuelTrimBank1>("/lma_obd2/long_term_fuel_trim_bank1", rclcpp::QoS{1});
                short_term_fuel_trim_bank2_pub_ = create_publisher<lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank2>("/lma_obd2/short_term_fuel_trim_bank2", rclcpp::QoS{1});
                long_term_fuel_trim_bank2_pub_ = create_publisher<lma_obd2_driver_msgs::msg::LongTermFuelTrimBank2>("/lma_obd2/long_term_fuel_trim_bank2", rclcpp::QoS{1});
                fuel_pressure_pub_ = create_publisher<lma_obd2_driver_msgs::msg::FuelPressure>("/lma_obd2/fuel_pressure", rclcpp::QoS{1});
                intake_manifold_absolute_pressure_pub_ = create_publisher<lma_obd2_driver_msgs::msg::IntakeManifoldAbsolutePressure>("/lma_obd2/intake_manifold_absolute_pressure", rclcpp::QoS{1});
                engine_rpm_pub_ = create_publisher<lma_obd2_driver_msgs::msg::EngineRpm>("/lma_obd2/engine_rpm", rclcpp::QoS{1});
                vehicle_speed_pub_ = create_publisher<lma_obd2_driver_msgs::msg::VehicleSpeed>("/lma_obd2/vehicle_speed", rclcpp::QoS{1});
                spark_timing_advance_pub_ = create_publisher<lma_obd2_driver_msgs::msg::SparkTimingAdvance>("/lma_obd2/spark_timing_advance", rclcpp::QoS{1});
                intake_air_temperature_pub_ = create_publisher<lma_obd2_driver_msgs::msg::IntakeAirTemperature>("/lma_obd2/intake_air_temperature", rclcpp::QoS{1});
            }
            {
                // timer
                timer_ = rclcpp::create_timer(
                    this, get_clock(), rclcpp::Rate(param_.loop_rate).period(),
                    std::bind(&ReportParser::timerCallback, this));
            }
        }

        // calback is publish
        void ReportParser::callbackIsPublish(const std_msgs::msg::Bool::ConstSharedPtr &msg)
        {
            is_publish_ = msg->data;
        }

        // callback can
        void ReportParser::callbackCan(const can_msgs::msg::Frame::ConstSharedPtr &msg)
        {

            //* DEBUG
            RCLCPP_INFO(this->get_logger(), "**** CAN RECEIVED ****");

            std_msgs::msg::Header header;
            header.frame_id = param_.base_frame_id;
            header.stamp = msg->header.stamp;

            /** example
            V2aBrakeStaFb brake_sta_fb_msg;
            **/
            lma_obd2_driver_msgs::msg::MonitorStatusSinceDtCsCleared monitor_status_since_dt_cs_cleared_msg;
            lma_obd2_driver_msgs::msg::MafAirFlowRate maf_air_flow_rate_msg;
            lma_obd2_driver_msgs::msg::ThrottlePosition throttle_position_msg;
            lma_obd2_driver_msgs::msg::RunSinceEngineStart run_since_engine_start_msg;
            lma_obd2_driver_msgs::msg::FuelSystemStatus fuel_system_status_msg;
            lma_obd2_driver_msgs::msg::CalculatedEngineLoad calculated_engine_load_msg;
            lma_obd2_driver_msgs::msg::AbsoluteLoadValue absolute_load_value_msg;
            lma_obd2_driver_msgs::msg::RelativeThrottlePosition relative_throttle_position_msg;
            lma_obd2_driver_msgs::msg::EngineCoolantTemperature engine_coolant_temperature_msg;
            lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank1 short_term_fuel_trim_bank1_msg;
            lma_obd2_driver_msgs::msg::LongTermFuelTrimBank1 long_term_fuel_trim_bank1_msg;
            lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank2 short_term_fuel_trim_bank2_msg;
            lma_obd2_driver_msgs::msg::LongTermFuelTrimBank2 long_term_fuel_trim_bank2_msg;
            lma_obd2_driver_msgs::msg::FuelPressure fuel_pressure_msg;
            lma_obd2_driver_msgs::msg::IntakeManifoldAbsolutePressure intake_manifold_absolute_pressure_msg;
            lma_obd2_driver_msgs::msg::EngineRpm engine_rpm_msg;
            lma_obd2_driver_msgs::msg::VehicleSpeed vehicle_speed_msg;
            lma_obd2_driver_msgs::msg::SparkTimingAdvance spark_timing_advance_msg;
            lma_obd2_driver_msgs::msg::IntakeAirTemperature intake_air_temperature_msg;

            uint8_t byte_temp[8];
            switch (msg->id)
            {
                /** example
                case V2adrivestafb530::ID:
                  drive_sta_fb_received_time_ = this->now();

                  for(uint i=0;i<8;i++)
                  {
                  byte_temp[i] = msg->data[i];
                  }
                  v2a_drivestafb_530_entity_.update_bytes(byte_temp);
                  v2a_drivestafb_530_entity_.Parse();

                  drive_sta_fb_msg.header = header;
                  drive_sta_fb_msg.vcu_chassis_driver_en_sta =
                    v2a_drivestafb_530_entity_.vcu_chassisdriverensta;
                  drive_sta_fb_msg.vcu_chassis_diver_slopover =
                    v2a_drivestafb_530_entity_.vcu_chassisdiverslopover;
                  drive_sta_fb_msg.vcu_chassis_driver_mode_sta =
                    v2a_drivestafb_530_entity_.vcu_chassisdrivermodesta;
                  drive_sta_fb_msg.vcu_chassis_gear_fb = v2a_drivestafb_530_entity_.vcu_chassisgearfb;
                  drive_sta_fb_msg.vcu_chassis_speed_fb = v2a_drivestafb_530_entity_.vcu_chassisspeedfb;
                  drive_sta_fb_msg.vcu_chassis_throttle_padl_fb =
                    v2a_drivestafb_530_entity_.vcu_chassisthrottlepaldfb;
                  drive_sta_fb_msg.vcu_chassis_accceleration_fb =
                    v2a_drivestafb_530_entity_.vcu_chassisaccelerationfb;
                  drive_sta_fb_ptr_ = std::make_shared<V2aDriveStaFb>(drive_sta_fb_msg);
                  break;
                **/

            case MonitorStatusSinceDtCsCleared::ID:
                monitor_status_since_dt_cs_cleared_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                monitor_status_since_dt_cs_cleared_entity_.update_bytes(byte_temp);
                monitor_status_since_dt_cs_cleared_entity_.Parse();

                monitor_status_since_dt_cs_cleared_msg.header = header;
                monitor_status_since_dt_cs_cleared_msg.mil_on_off = monitor_status_since_dt_cs_cleared_entity_.mil_on_off_;
                monitor_status_since_dt_cs_cleared_msg.dtc_count = monitor_status_since_dt_cs_cleared_entity_.dtc_count_;
                monitor_status_since_dt_cs_cleared_msg.reserved = monitor_status_since_dt_cs_cleared_entity_.reserved_;
                monitor_status_since_dt_cs_cleared_msg.no_name = monitor_status_since_dt_cs_cleared_entity_.no_name_;

                monitor_status_since_dt_cs_cleared_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::MonitorStatusSinceDtCsCleared>(monitor_status_since_dt_cs_cleared_msg);
                break;

            case MafAirFlowRate::ID:
                maf_air_flow_rate_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                maf_air_flow_rate_entity_.update_bytes(byte_temp);
                maf_air_flow_rate_entity_.Parse();

                maf_air_flow_rate_msg.header = header;
                maf_air_flow_rate_msg.maf_a = maf_air_flow_rate_entity_.maf_a_;
                maf_air_flow_rate_msg.maf_b = maf_air_flow_rate_entity_.maf_b_;

                maf_air_flow_rate_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::MafAirFlowRate>(maf_air_flow_rate_msg);
                break;

            case ThrottlePosition::ID:
                throttle_position_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                throttle_position_entity_.update_bytes(byte_temp);
                throttle_position_entity_.Parse();

                throttle_position_msg.header = header;
                throttle_position_msg.throttle_position = throttle_position_entity_.throttle_position_;

                throttle_position_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::ThrottlePosition>(throttle_position_msg);
                break;

            case RunSinceEngineStart::ID:
                run_since_engine_start_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                run_since_engine_start_entity_.update_bytes(byte_temp);
                run_since_engine_start_entity_.Parse();

                run_since_engine_start_msg.header = header;
                run_since_engine_start_msg.a = run_since_engine_start_entity_.a_;
                run_since_engine_start_msg.b = run_since_engine_start_entity_.b_;

                run_since_engine_start_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::RunSinceEngineStart>(run_since_engine_start_msg);
                break;

            case FuelSystemStatus::ID:
                fuel_system_status_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                fuel_system_status_entity_.update_bytes(byte_temp);
                fuel_system_status_entity_.Parse();

                fuel_system_status_msg.header = header;
                fuel_system_status_msg.fuel_system_1 = fuel_system_status_entity_.fuel_system_1_;
                fuel_system_status_msg.fuel_system_2 = fuel_system_status_entity_.fuel_system_2_;

                fuel_system_status_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::FuelSystemStatus>(fuel_system_status_msg);
                break;

            case CalculatedEngineLoad::ID:
                calculated_engine_load_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                calculated_engine_load_entity_.update_bytes(byte_temp);
                calculated_engine_load_entity_.Parse();

                calculated_engine_load_msg.header = header;
                calculated_engine_load_msg.engine_load = calculated_engine_load_entity_.engine_load_;

                calculated_engine_load_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::CalculatedEngineLoad>(calculated_engine_load_msg);
                break;

            case AbsoluteLoadValue::ID:
                absolute_load_value_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                absolute_load_value_entity_.update_bytes(byte_temp);
                absolute_load_value_entity_.Parse();

                absolute_load_value_msg.header = header;
                absolute_load_value_msg.a = absolute_load_value_entity_.a_;
                absolute_load_value_msg.b = absolute_load_value_entity_.b_;

                absolute_load_value_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::AbsoluteLoadValue>(absolute_load_value_msg);
                break;

            case RelativeThrottlePosition::ID:
                relative_throttle_position_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                relative_throttle_position_entity_.update_bytes(byte_temp);
                relative_throttle_position_entity_.Parse();

                relative_throttle_position_msg.header = header;
                relative_throttle_position_msg.rel_throttle_position = relative_throttle_position_entity_.rel_throttle_position_;

                relative_throttle_position_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::RelativeThrottlePosition>(relative_throttle_position_msg);
                break;

            case EngineCoolantTemperature::ID:
                engine_coolant_temperature_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                engine_coolant_temperature_entity_.update_bytes(byte_temp);
                engine_coolant_temperature_entity_.Parse();

                engine_coolant_temperature_msg.header = header;
                engine_coolant_temperature_msg.engine_coolant_temp = engine_coolant_temperature_entity_.engine_coolant_temp_;

                engine_coolant_temperature_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::EngineCoolantTemperature>(engine_coolant_temperature_msg);
                break;

            case ShortTermFuelTrimBank1::ID:
                short_term_fuel_trim_bank1_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                short_term_fuel_trim_bank1_entity_.update_bytes(byte_temp);
                short_term_fuel_trim_bank1_entity_.Parse();

                short_term_fuel_trim_bank1_msg.header = header;
                short_term_fuel_trim_bank1_msg.instant_fuel_trim_bank1 = short_term_fuel_trim_bank1_entity_.instant_fuel_trim_bank1_;

                short_term_fuel_trim_bank1_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank1>(short_term_fuel_trim_bank1_msg);
                break;

            case LongTermFuelTrimBank1::ID:
                long_term_fuel_trim_bank1_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                long_term_fuel_trim_bank1_entity_.update_bytes(byte_temp);
                long_term_fuel_trim_bank1_entity_.Parse();

                long_term_fuel_trim_bank1_msg.header = header;
                long_term_fuel_trim_bank1_msg.long_term_fuel_trim_bank1 = long_term_fuel_trim_bank1_entity_.long_term_fuel_trim_bank1_;

                long_term_fuel_trim_bank1_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::LongTermFuelTrimBank1>(long_term_fuel_trim_bank1_msg);
                break;

            case ShortTermFuelTrimBank2::ID:
                short_term_fuel_trim_bank2_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                short_term_fuel_trim_bank2_entity_.update_bytes(byte_temp);
                short_term_fuel_trim_bank2_entity_.Parse();

                short_term_fuel_trim_bank2_msg.header = header;
                short_term_fuel_trim_bank2_msg.instant_fuel_trim_bank2 = short_term_fuel_trim_bank2_entity_.instant_fuel_trim_bank2_;

                short_term_fuel_trim_bank2_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::ShortTermFuelTrimBank2>(short_term_fuel_trim_bank2_msg);
                break;

            case LongTermFuelTrimBank2::ID:
                long_term_fuel_trim_bank2_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                long_term_fuel_trim_bank2_entity_.update_bytes(byte_temp);
                long_term_fuel_trim_bank2_entity_.Parse();

                long_term_fuel_trim_bank2_msg.header = header;
                long_term_fuel_trim_bank2_msg.long_term_fuel_trim_bank2 = long_term_fuel_trim_bank2_entity_.long_term_fuel_trim_bank2_;

                long_term_fuel_trim_bank2_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::LongTermFuelTrimBank2>(long_term_fuel_trim_bank2_msg);
                break;

            case FuelPressure::ID:
                fuel_pressure_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                fuel_pressure_entity_.update_bytes(byte_temp);
                fuel_pressure_entity_.Parse();

                fuel_pressure_msg.header = header;
                fuel_pressure_msg.fuel_pressure = fuel_pressure_entity_.fuel_pressure_;

                fuel_pressure_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::FuelPressure>(fuel_pressure_msg);
                break;

            case IntakeManifoldAbsolutePressure::ID:
                intake_manifold_absolute_pressure_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                intake_manifold_absolute_pressure_entity_.update_bytes(byte_temp);
                intake_manifold_absolute_pressure_entity_.Parse();

                intake_manifold_absolute_pressure_msg.header = header;
                intake_manifold_absolute_pressure_msg.imap = intake_manifold_absolute_pressure_entity_.imap_;

                intake_manifold_absolute_pressure_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::IntakeManifoldAbsolutePressure>(intake_manifold_absolute_pressure_msg);
                break;

            case EngineRpm::ID:
                engine_rpm_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                engine_rpm_entity_.update_bytes(byte_temp);
                engine_rpm_entity_.Parse();

                engine_rpm_msg.header = header;
                engine_rpm_msg.a = engine_rpm_entity_.a_;
                engine_rpm_msg.b = engine_rpm_entity_.b_;

                engine_rpm_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::EngineRpm>(engine_rpm_msg);
                break;

            case VehicleSpeed::ID:
                vehicle_speed_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                vehicle_speed_entity_.update_bytes(byte_temp);
                vehicle_speed_entity_.Parse();

                vehicle_speed_msg.header = header;
                vehicle_speed_msg.vehicle_speed = vehicle_speed_entity_.vehicle_speed_;

                vehicle_speed_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::VehicleSpeed>(vehicle_speed_msg);
                break;

            case SparkTimingAdvance::ID:
                spark_timing_advance_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                spark_timing_advance_entity_.update_bytes(byte_temp);
                spark_timing_advance_entity_.Parse();

                spark_timing_advance_msg.header = header;
                spark_timing_advance_msg.spark_timing_advance = spark_timing_advance_entity_.spark_timing_advance_;

                spark_timing_advance_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::SparkTimingAdvance>(spark_timing_advance_msg);
                break;

            case IntakeAirTemperature::ID:
                intake_air_temperature_received_time_ = this->now();

                for (uint i = 0; i < 8; i++)
                {
                    byte_temp[i] = msg->data[i];
                }
                intake_air_temperature_entity_.update_bytes(byte_temp);
                intake_air_temperature_entity_.Parse();

                intake_air_temperature_msg.header = header;
                intake_air_temperature_msg.intake_air_temp = intake_air_temperature_entity_.intake_air_temp_;

                intake_air_temperature_ptr_ = std::make_shared<lma_obd2_driver_msgs::msg::IntakeAirTemperature>(intake_air_temperature_msg);
                break;

            default:
                break;
            }
        }

        void ReportParser::timerCallback()
        {
            if (!is_publish_)
                return;

            const rclcpp::Time current_time = this->now();

            /** example
            // drive sta fb report
            const double drive_sta_fb_report_delta_time_ms =
              (current_time - drive_sta_fb_received_time_).seconds() * 1000.0;
            if(drive_sta_fb_report_delta_time_ms>param_.report_timeout_ms || drive_sta_fb_ptr_==nullptr)
            {
              RCLCPP_ERROR_THROTTLE(
                get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                "drive stat fb report timeout = %f ms.", drive_sta_fb_report_delta_time_ms);
            }else{
              drive_sta_fb_pub_->publish(*drive_sta_fb_ptr_);
            }
            **/

            const double monitor_status_since_dt_cs_cleared_report_delta_time_ms =
                (current_time - monitor_status_since_dt_cs_cleared_received_time_).seconds() * 1000.0;
            if (monitor_status_since_dt_cs_cleared_report_delta_time_ms > param_.report_timeout_ms || monitor_status_since_dt_cs_cleared_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "monitor_status_since_dt_cs_cleared report timeout = %f ms.", monitor_status_since_dt_cs_cleared_report_delta_time_ms);
            }
            else
            {
                monitor_status_since_dt_cs_cleared_pub_->publish(*monitor_status_since_dt_cs_cleared_ptr_);
            }

            const double maf_air_flow_rate_report_delta_time_ms =
                (current_time - maf_air_flow_rate_received_time_).seconds() * 1000.0;
            if (maf_air_flow_rate_report_delta_time_ms > param_.report_timeout_ms || maf_air_flow_rate_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "maf_air_flow_rate report timeout = %f ms.", maf_air_flow_rate_report_delta_time_ms);
            }
            else
            {
                maf_air_flow_rate_pub_->publish(*maf_air_flow_rate_ptr_);
            }

            const double throttle_position_report_delta_time_ms =
                (current_time - throttle_position_received_time_).seconds() * 1000.0;
            if (throttle_position_report_delta_time_ms > param_.report_timeout_ms || throttle_position_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "throttle_position report timeout = %f ms.", throttle_position_report_delta_time_ms);
            }
            else
            {
                throttle_position_pub_->publish(*throttle_position_ptr_);
            }

            const double run_since_engine_start_report_delta_time_ms =
                (current_time - run_since_engine_start_received_time_).seconds() * 1000.0;
            if (run_since_engine_start_report_delta_time_ms > param_.report_timeout_ms || run_since_engine_start_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "run_since_engine_start report timeout = %f ms.", run_since_engine_start_report_delta_time_ms);
            }
            else
            {
                run_since_engine_start_pub_->publish(*run_since_engine_start_ptr_);
            }

            const double fuel_system_status_report_delta_time_ms =
                (current_time - fuel_system_status_received_time_).seconds() * 1000.0;
            if (fuel_system_status_report_delta_time_ms > param_.report_timeout_ms || fuel_system_status_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "fuel_system_status report timeout = %f ms.", fuel_system_status_report_delta_time_ms);
            }
            else
            {
                fuel_system_status_pub_->publish(*fuel_system_status_ptr_);
            }

            const double calculated_engine_load_report_delta_time_ms =
                (current_time - calculated_engine_load_received_time_).seconds() * 1000.0;
            if (calculated_engine_load_report_delta_time_ms > param_.report_timeout_ms || calculated_engine_load_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "calculated_engine_load report timeout = %f ms.", calculated_engine_load_report_delta_time_ms);
            }
            else
            {
                calculated_engine_load_pub_->publish(*calculated_engine_load_ptr_);
            }

            const double absolute_load_value_report_delta_time_ms =
                (current_time - absolute_load_value_received_time_).seconds() * 1000.0;
            if (absolute_load_value_report_delta_time_ms > param_.report_timeout_ms || absolute_load_value_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "absolute_load_value report timeout = %f ms.", absolute_load_value_report_delta_time_ms);
            }
            else
            {
                absolute_load_value_pub_->publish(*absolute_load_value_ptr_);
            }

            const double relative_throttle_position_report_delta_time_ms =
                (current_time - relative_throttle_position_received_time_).seconds() * 1000.0;
            if (relative_throttle_position_report_delta_time_ms > param_.report_timeout_ms || relative_throttle_position_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "relative_throttle_position report timeout = %f ms.", relative_throttle_position_report_delta_time_ms);
            }
            else
            {
                relative_throttle_position_pub_->publish(*relative_throttle_position_ptr_);
            }

            const double engine_coolant_temperature_report_delta_time_ms =
                (current_time - engine_coolant_temperature_received_time_).seconds() * 1000.0;
            if (engine_coolant_temperature_report_delta_time_ms > param_.report_timeout_ms || engine_coolant_temperature_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "engine_coolant_temperature report timeout = %f ms.", engine_coolant_temperature_report_delta_time_ms);
            }
            else
            {
                engine_coolant_temperature_pub_->publish(*engine_coolant_temperature_ptr_);
            }

            const double short_term_fuel_trim_bank1_report_delta_time_ms =
                (current_time - short_term_fuel_trim_bank1_received_time_).seconds() * 1000.0;
            if (short_term_fuel_trim_bank1_report_delta_time_ms > param_.report_timeout_ms || short_term_fuel_trim_bank1_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "short_term_fuel_trim_bank1 report timeout = %f ms.", short_term_fuel_trim_bank1_report_delta_time_ms);
            }
            else
            {
                short_term_fuel_trim_bank1_pub_->publish(*short_term_fuel_trim_bank1_ptr_);
            }

            const double long_term_fuel_trim_bank1_report_delta_time_ms =
                (current_time - long_term_fuel_trim_bank1_received_time_).seconds() * 1000.0;
            if (long_term_fuel_trim_bank1_report_delta_time_ms > param_.report_timeout_ms || long_term_fuel_trim_bank1_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "long_term_fuel_trim_bank1 report timeout = %f ms.", long_term_fuel_trim_bank1_report_delta_time_ms);
            }
            else
            {
                long_term_fuel_trim_bank1_pub_->publish(*long_term_fuel_trim_bank1_ptr_);
            }

            const double short_term_fuel_trim_bank2_report_delta_time_ms =
                (current_time - short_term_fuel_trim_bank2_received_time_).seconds() * 1000.0;
            if (short_term_fuel_trim_bank2_report_delta_time_ms > param_.report_timeout_ms || short_term_fuel_trim_bank2_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "short_term_fuel_trim_bank2 report timeout = %f ms.", short_term_fuel_trim_bank2_report_delta_time_ms);
            }
            else
            {
                short_term_fuel_trim_bank2_pub_->publish(*short_term_fuel_trim_bank2_ptr_);
            }

            const double long_term_fuel_trim_bank2_report_delta_time_ms =
                (current_time - long_term_fuel_trim_bank2_received_time_).seconds() * 1000.0;
            if (long_term_fuel_trim_bank2_report_delta_time_ms > param_.report_timeout_ms || long_term_fuel_trim_bank2_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "long_term_fuel_trim_bank2 report timeout = %f ms.", long_term_fuel_trim_bank2_report_delta_time_ms);
            }
            else
            {
                long_term_fuel_trim_bank2_pub_->publish(*long_term_fuel_trim_bank2_ptr_);
            }

            const double fuel_pressure_report_delta_time_ms =
                (current_time - fuel_pressure_received_time_).seconds() * 1000.0;
            if (fuel_pressure_report_delta_time_ms > param_.report_timeout_ms || fuel_pressure_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "fuel_pressure report timeout = %f ms.", fuel_pressure_report_delta_time_ms);
            }
            else
            {
                fuel_pressure_pub_->publish(*fuel_pressure_ptr_);
            }

            const double intake_manifold_absolute_pressure_report_delta_time_ms =
                (current_time - intake_manifold_absolute_pressure_received_time_).seconds() * 1000.0;
            if (intake_manifold_absolute_pressure_report_delta_time_ms > param_.report_timeout_ms || intake_manifold_absolute_pressure_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "intake_manifold_absolute_pressure report timeout = %f ms.", intake_manifold_absolute_pressure_report_delta_time_ms);
            }
            else
            {
                intake_manifold_absolute_pressure_pub_->publish(*intake_manifold_absolute_pressure_ptr_);
            }

            const double engine_rpm_report_delta_time_ms =
                (current_time - engine_rpm_received_time_).seconds() * 1000.0;
            if (engine_rpm_report_delta_time_ms > param_.report_timeout_ms || engine_rpm_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "engine_rpm report timeout = %f ms.", engine_rpm_report_delta_time_ms);
            }
            else
            {
                engine_rpm_pub_->publish(*engine_rpm_ptr_);
            }

            const double vehicle_speed_report_delta_time_ms =
                (current_time - vehicle_speed_received_time_).seconds() * 1000.0;
            if (vehicle_speed_report_delta_time_ms > param_.report_timeout_ms || vehicle_speed_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "vehicle_speed report timeout = %f ms.", vehicle_speed_report_delta_time_ms);
            }
            else
            {
                vehicle_speed_pub_->publish(*vehicle_speed_ptr_);
            }

            const double spark_timing_advance_report_delta_time_ms =
                (current_time - spark_timing_advance_received_time_).seconds() * 1000.0;
            if (spark_timing_advance_report_delta_time_ms > param_.report_timeout_ms || spark_timing_advance_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "spark_timing_advance report timeout = %f ms.", spark_timing_advance_report_delta_time_ms);
            }
            else
            {
                spark_timing_advance_pub_->publish(*spark_timing_advance_ptr_);
            }

            const double intake_air_temperature_report_delta_time_ms =
                (current_time - intake_air_temperature_received_time_).seconds() * 1000.0;
            if (intake_air_temperature_report_delta_time_ms > param_.report_timeout_ms || intake_air_temperature_ptr_ == nullptr)
            {
                RCLCPP_ERROR_THROTTLE(
                    get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
                    "intake_air_temperature report timeout = %f ms.", intake_air_temperature_report_delta_time_ms);
            }
            else
            {
                intake_air_temperature_pub_->publish(*intake_air_temperature_ptr_);
            }
        }

    } // namespace report_parser
} // namespace lma_obd2_driver
