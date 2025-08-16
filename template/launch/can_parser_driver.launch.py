import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

receiver_parser =   Node(
                        package='lma_obd2_driver',
                        executable='lma_obd2_driver_report_parser_node',
                        name='can_receiver_parser',
                        output='both',
                        remappings=[
                                    ('/input/can_rx', '/from_can_bus')
                        ]
                    )

sender_parser =     Node(
                        package='lma_obd2_driver',
                        executable='lma_obd2_driver_control_command_node',
                        name='can_sender_parser',
                        output='both',
                        remappings=[
                                    ('/from_can_bus', '/input/can_tx')
                        ]
                    )

def generate_launch_description():
    return LaunchDescription([
        receiver_parser,
        # sender_parser        
    ])
