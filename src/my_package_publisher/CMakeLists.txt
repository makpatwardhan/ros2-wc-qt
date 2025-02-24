cmake_minimum_required(VERSION 3.8)
project(my_package_publisher)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
# Find ROS2 packages
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
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)

# rosidl_generate_interfaces(${PROJECT_NAME}
#   "msg/String.msg"
# )
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(publisher
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET publisher APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(publisher SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(publisher
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_directories(publisher PUBLIC "/opt/ros/rolling/lib")

target_link_libraries(publisher PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(publisher PRIVATE
  rclcpp
  rosidl_typesupport_cpp
  std_msgs::std_msgs__rosidl_typesupport_c
  std_msgs::std_msgs__rosidl_typesupport_cpp
  rcl
  tracetools  # Add this line
  rmw
  rcutils
)

# Specify include directories for ROS2 and Qt6
target_include_directories(publisher PUBLIC
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
target_include_directories(publisher PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(publisher PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS publisher
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

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(publisher)
endif()


ament_package()
