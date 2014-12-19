cmake_minimum_required(VERSION 2.8.3)
project(youbot_control)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  sensor_msgs
  cv_bridge
  roscpp
  std_msgs
  image_transport
  brics_actuator
  trajectory_msgs
  control_msgs
  pr2_controller_interface
  #youbot_trajectory_action_server
)

find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp sensor_msgs cv_bridge std_msgs image_transport brics_actuator trajectory_msgs control_msgs pr2_controller_interface youbot_trajectory_action_server
)

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_executable(ba_jointposition_listener src/ba_jointposition_listener.cpp)

#youbot universal controller: joint space position control, joint velocity control, joint torque control
#add_library(youbot_universal_control src/youbot_universal_control.cpp src/joint_state_observer_gazebo.cpp)
#target_link_libraries(youbot_universal_control youbot_trajectory_action_server)

target_link_libraries(ba_jointposition_listener
  ${catkin_LIBRARIES}
)

install(DIRECTORY config/ DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config)
install(DIRECTORY launch/ DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch)