cmake_minimum_required(VERSION 3.8)
project(my_package_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(service_msgs REQUIRED)
find_package(type_description_interfaces REQUIRED)
find_package(rcl REQUIRED)
find_package(tracetools REQUIRED)
find_package(rosidl_typesupport_cpp REQUIRED)  # Add this line
find_package(rmw REQUIRED)
find_package(rcutils REQUIRED)  # ✅ Explicitly find rcutils
find_package(statistics_msgs REQUIRED)  # Add this line to find statistics_msgs
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(subscriber src/subscriber.cpp)
target_include_directories(subscriber PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(subscriber PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

target_link_directories(subscriber PUBLIC "/opt/ros/rolling/lib")

# Link ROS 2 libraries
target_link_libraries(subscriber PRIVATE 
  rclcpp
  rosidl_typesupport_cpp
  std_msgs::std_msgs__rosidl_typesupport_c
  std_msgs::std_msgs__rosidl_typesupport_cpp
  rcl
  tracetools  # Add this line
  rmw
  rcutils
  libstatistics_collector
  statistics_msgs::statistics_msgs__rosidl_typesupport_cpp
  statistics_msgs::statistics_msgs__rosidl_typesupport_c
  )
  
target_include_directories(subscriber PRIVATE
  ${rclcpp_INCLUDE_DIRS}
  ${std_msgs_INCLUDE_DIRS}
  ${service_msgs_INCLUDE_DIRS}
  ${type_description_interfaces_INCLUDE_DIRS}
  ${rcl_INCLUDE_DIRS}  # Add this line
  ${tracetools_INCLUDE_DIRS}  # Add this line
  ${rosidl_typesupport_cpp_INCLUDE_DIRS}  # Add this line
  ${rmw_INCLUDE_DIRS}
  ${rcutils_INCLUDE_DIRS}
  )

install(TARGETS subscriber
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
