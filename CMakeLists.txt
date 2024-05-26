cmake_minimum_required(VERSION 3.10)
project(DSS_protobuf_demo)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIR})
link_directories(${Protobuf_LIBRARIES})

find_package(absl REQUIRED)
include_directories(${absl_INCLUDE_DIRS})

# Custom command to generate Protobuf files
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/command_protocal.pb.cc ${CMAKE_CURRENT_SOURCE_DIR}/src/command_protocal.pb.h
    COMMAND ${Protobuf_PROTOC_EXECUTABLE} --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/src --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src/command_protocal.proto
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/command_protocal.proto
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add custom target to run the Protobuf compiler
add_custom_target(command_protocols DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/command_protocal.pb.cc ${CMAKE_CURRENT_SOURCE_DIR}/src/command_protocal.pb.h)

# Add executable targets
add_executable(sender src/sender.cc src/command_protocal.pb.cc)
add_executable(receiver src/receiver.cc src/command_protocal.pb.cc)

# Link Protobuf libraries

target_link_libraries(sender ${Protobuf_LIBRARIES} absl::base absl::strings absl::log_internal_check_op)
target_link_libraries(receiver ${Protobuf_LIBRARIES} absl::base absl::strings absl::log_internal_check_op)

# Add dependencies to ensure Protobuf files are generated before compiling
add_dependencies(sender command_protocols) 
add_dependencies(receiver command_protocols)

# Clean target
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/command_protocal.pb.*")
