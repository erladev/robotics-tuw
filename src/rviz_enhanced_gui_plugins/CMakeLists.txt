cmake_minimum_required(VERSION 3.10)
project(rviz_enhanced_gui_plugins)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wnon-virtual-dtor -Woverloaded-virtual -Wno-undef)
endif()

# find dependencies
find_package(ament_cmake_ros REQUIRED)

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

find_package(rviz_common REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)

find_package(Qt5 REQUIRED COMPONENTS Widgets Test)

find_package(geometry_msgs REQUIRED)

#find_package(gz_math_vendor REQUIRED)
#find_package(gz-math REQUIRED)

find_package(image_transport REQUIRED)
find_package(interactive_markers REQUIRED)
find_package(laser_geometry REQUIRED)
find_package(map_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(pluginlib REQUIRED)
# find_package(point_cloud_transport REQUIRED)
find_package(rclcpp REQUIRED)
find_package(resource_retriever REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(urdf REQUIRED)
find_package(visualization_msgs REQUIRED)

set(rviz_enhanced_gui_plugins_headers_to_moc
  include/rviz_enhanced_gui_plugins/rts_pose_tool/rts_pose_tool.hpp
)

foreach(header "${rviz_enhanced_gui_plugins_headers_to_moc}")
  qt5_wrap_cpp(rviz_enhanced_gui_plugins_moc_files "${header}")
endforeach()

set(rviz_enhanced_gui_plugins_source_files
  src/rviz_enhanced_gui_plugins/rts_pose_tool/rts_pose_tool.cpp
)

add_library(rviz_enhanced_gui_plugins
  ${rviz_enhanced_gui_plugins_moc_files}
  ${rviz_enhanced_gui_plugins_source_files}
)

target_include_directories(rviz_enhanced_gui_plugins PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
  ${Qt5Widgets_INCLUDE_DIRS}
)

target_link_libraries(rviz_enhanced_gui_plugins PUBLIC
  ${geometry_msgs_TARGETS}
  image_transport::image_transport
  interactive_markers::interactive_markers
  laser_geometry::laser_geometry
  ${map_msgs_TARGETS}
  ${nav_msgs_TARGETS}
  rclcpp::rclcpp
  rviz_common::rviz_common
  rviz_ogre_vendor::OgreMain
  rviz_ogre_vendor::OgreOverlay
  rviz_rendering::rviz_rendering
  ${sensor_msgs_TARGETS}
  tf2::tf2
  ${tf2_geometry_msgs_TARGETS}
  tf2_ros::tf2_ros
  urdf::urdf
  ${visualization_msgs_TARGETS}
)
target_compile_definitions(rviz_enhanced_gui_plugins PRIVATE "RVIZ_ENHANCED_GUI_PLUGINS_BUILDING_LIBRARY")

pluginlib_export_plugin_description_file(rviz_enhanced_gui_plugins plugins_description.xml)

ament_export_include_directories("include/${PROJECT_NAME}")
ament_export_libraries(rviz_enhanced_gui_plugins)

ament_export_dependencies(
  geometry_msgs
  image_transport
  interactive_markers
  laser_geometry
  map_msgs
  nav_msgs
  # point_cloud_transport
  rclcpp
  rviz_common
  rviz_ogre_vendor
  rviz_rendering
  sensor_msgs
  tf2
  tf2_geometry_msgs
  tf2_ros
  urdf
  visualization_msgs
  pluginlib
)

install(
  TARGETS rviz_enhanced_gui_plugins
  EXPORT rviz_enhanced_gui_plugins
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(FILES plugins_description.xml
        DESTINATION share/${PROJECT_NAME}
)

pluginlib_export_plugin_description_file(rviz_common plugins_description.xml)


ament_package()
