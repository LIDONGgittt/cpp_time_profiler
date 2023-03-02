cmake_minimum_required(VERSION 2.8.3)
project(speedo)

# Find catkin.
# find_package(catkin REQUIRED)

# Find Boost.
find_package(Boost REQUIRED 
  COMPONENTS 
    system 
    chrono 
    filesystem
    date_time
)

# Generate catkin config file so other packages can find Speedo.
# catkin_package(
#  INCLUDE_DIRS include
#  DEPENDS Boost
#)

# Specify locations of header files.
include_directories(include)

# Declare the test executable.
add_executable(speedo_test src/speedo_test.cpp)

# Specify libraries to link the executable against.
target_link_libraries(speedo_test ${Boost_LIBRARIES})
